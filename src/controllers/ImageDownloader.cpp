#include "ImageDownloader.h"
#include <QDebug>
#include <QStandardPaths>
#include <QFileInfo>

ImageDownloader::ImageDownloader(QObject *parent)
    : QObject(parent)
    , m_socket(new QTcpSocket(this))
    , m_fileTransfer(nullptr)
    , m_isProcessing(false)
    , m_nextRequestId(1)
{
    // 소켓 시그널 연결
    connect(m_socket, &QTcpSocket::connected, this, &ImageDownloader::onConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &ImageDownloader::onDisconnected);
    connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &ImageDownloader::onSocketError);

    // tmp 디렉토리 초기화
    initializeTmpDirectory();
}

ImageDownloader::~ImageDownloader()
{
    if (m_fileTransfer) {
        delete m_fileTransfer;
    }

    if (m_socket->state() != QAbstractSocket::UnconnectedState) {
        m_socket->disconnectFromHost();
    }
}

bool ImageDownloader::connectToServer(const QString &host, quint16 port)
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        qDebug() << "ImageDownloader: Already connected to file server";
        return true;
    }

    qDebug() << "ImageDownloader: Connecting to file server:" << host << ":" << port;
    m_socket->connectToHost(host, port);

    return m_socket->waitForConnected(5000);
}

void ImageDownloader::disconnectFromServer()
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        m_socket->disconnectFromHost();
    }
}

bool ImageDownloader::isConnected() const
{
    return m_socket->state() == QAbstractSocket::ConnectedState;
}

int ImageDownloader::requestImage(const QString &fileName)
{
    return requestImage(fileName, generateSavePath(fileName));
}

int ImageDownloader::requestImage(const QString &fileName, const QString &customSavePath)
{
    if (fileName.isEmpty()) {
        emit downloadFailed(-1, fileName, "Empty filename");
        return -1;
    }

    // 이미 파일이 존재하는지 확인
    QString savePath = customSavePath.isEmpty() ? generateSavePath(fileName) : customSavePath;
    if (QFileInfo::exists(savePath)) {
        qDebug() << "Image already exists:" << savePath;
        emit downloadCompleted(m_nextRequestId, fileName, savePath);
        return m_nextRequestId++;
    }

    ImageDownloadRequest request;
    request.fileName = fileName;
    request.savePath = savePath;
    request.requestId = m_nextRequestId++;

    m_downloadQueue.enqueue(request);
    qDebug() << "Image download requested:" << fileName << "Queue size:" << m_downloadQueue.size();

    // 처리 중이 아니면 즉시 시작
    if (!m_isProcessing && isConnected()) {
        QTimer::singleShot(10, this, &ImageDownloader::processNextDownload);
    }

    return request.requestId;
}

void ImageDownloader::setTmpDirectory(const QString &tmpPath)
{
    QDir dir(tmpPath);
    if (!dir.exists()) {
        if (dir.mkpath(tmpPath)) {
            m_tmpDirectory = dir.absolutePath();
            qDebug() << "ImageDownloader: tmp directory created:" << m_tmpDirectory;
        } else {
            qDebug() << "ImageDownloader: Failed to create tmp directory:" << tmpPath;
        }
    } else {
        m_tmpDirectory = dir.absolutePath();
        qDebug() << "ImageDownloader: tmp directory set:" << m_tmpDirectory;
    }
}

bool ImageDownloader::isDownloading() const
{
    return m_isProcessing;
}

QString ImageDownloader::getImagePath(const QString &fileName) const
{
    return QDir(m_tmpDirectory).absoluteFilePath(fileName);
}

bool ImageDownloader::imageExists(const QString &fileName) const
{
    return QFileInfo::exists(getImagePath(fileName));
}

void ImageDownloader::onConnected()
{
    qDebug() << "ImageDownloader: Connected to file server";

    // FileTransfer 인스턴스 생성
    if (m_fileTransfer) {
        delete m_fileTransfer;
    }
    m_fileTransfer = new FileTransfer(m_socket, this);

    // FileTransfer의 저장 디렉토리를 tmp 디렉토리로 설정
    m_fileTransfer->setSaveDirectory(m_tmpDirectory);

    // FileTransfer 시그널 연결
    connect(m_fileTransfer, &FileTransfer::fileReceiveStarted,
            this, &ImageDownloader::onFileReceiveStarted);
    connect(m_fileTransfer, &FileTransfer::fileReceiveProgress,
            this, &ImageDownloader::onFileReceiveProgress);
    connect(m_fileTransfer, &FileTransfer::fileReceiveCompleted,
            this, &ImageDownloader::onFileReceiveCompleted);
    connect(m_fileTransfer, &FileTransfer::fileReceiveFailed,
            this, &ImageDownloader::onFileReceiveFailed);

    // 소켓에서 데이터 수신 시 FileTransfer로 자동 전달
    connect(m_socket, &QTcpSocket::readyRead, this, [this]() {
        if (m_fileTransfer && m_isProcessing) {
            QByteArray data = m_socket->readAll();
            qDebug() << "ImageDownloader: Received data, size:" << data.size();
            m_fileTransfer->processFileData(data);
        }
    });

    qDebug() << "ImageDownloader: FileTransfer signals connected";
    qDebug() << "ImageDownloader: Save directory set to:" << m_tmpDirectory;

    emit connected();

    // 대기 중인 다운로드가 있으면 시작
    if (!m_downloadQueue.isEmpty() && !m_isProcessing) {
        QTimer::singleShot(100, this, &ImageDownloader::processNextDownload);
    }
}

void ImageDownloader::onDisconnected()
{
    qDebug() << "ImageDownloader: Disconnected from file server";

    // FileTransfer 정리
    if (m_fileTransfer) {
        delete m_fileTransfer;
        m_fileTransfer = nullptr;
    }

    m_isProcessing = false;
    emit disconnected();
}

void ImageDownloader::onSocketError(QAbstractSocket::SocketError error)
{
    QString errorString = m_socket->errorString();
    qDebug() << "ImageDownloader socket error:" << errorString;
    emit errorOccurred(errorString);

    // 현재 처리 중인 요청이 있으면 실패 처리
    if (m_isProcessing) {
        emit downloadFailed(m_currentRequest.requestId, m_currentRequest.fileName, errorString);
        m_isProcessing = false;
    }
}

void ImageDownloader::processNextDownload()
{
    if (m_isProcessing || m_downloadQueue.isEmpty() || !isConnected()) {
        if (m_downloadQueue.isEmpty()) {
            emit queueEmpty();
        }
        return;
    }

    m_currentRequest = m_downloadQueue.dequeue();
    m_isProcessing = true;

    qDebug() << "Processing image download:" << m_currentRequest.fileName;

    // 서버에 파일 요청 전송
    processCurrentRequest();
}

void ImageDownloader::processCurrentRequest()
{
    // 파일 요청 메시지를 서버로 전송 (간단한 텍스트 프로토콜)
    QString requestMessage = m_currentRequest.fileName + "\n";
    QByteArray requestData = requestMessage.toUtf8();

    qint64 bytesWritten = m_socket->write(requestData);
    if (bytesWritten != requestData.size()) {
        emit downloadFailed(m_currentRequest.requestId, m_currentRequest.fileName,
                            "Failed to send file request");
        m_isProcessing = false;
        QTimer::singleShot(10, this, &ImageDownloader::processNextDownload);
    }
}

void ImageDownloader::onFileReceiveStarted(const QString &fileName, qint64 totalSize)
{
    qDebug() << "Image download started:" << fileName << "Size:" << totalSize;
    emit downloadStarted(m_currentRequest.requestId, fileName);
}

void ImageDownloader::onFileReceiveProgress(qint64 bytesReceived, qint64 totalBytes)
{
    emit downloadProgress(m_currentRequest.requestId, bytesReceived, totalBytes);
}

void ImageDownloader::onFileReceiveCompleted(const QString &completedFilePath)
{
    qDebug() << "Image download completed:" << completedFilePath;

    // FileTransfer가 이미 올바른 위치에 저장했으므로 파일 이동 불필요
    QFileInfo fileInfo(completedFilePath);
    if (!fileInfo.exists()) {
        emit downloadFailed(m_currentRequest.requestId, m_currentRequest.fileName,
                            "Completed file not found: " + completedFilePath);
        m_isProcessing = false;
        QTimer::singleShot(10, this, &ImageDownloader::processNextDownload);
        return;
    }

    // 파일 완전성 검증
    if (fileInfo.size() == 0) {
        qDebug() << "Downloaded file is empty:" << completedFilePath;
        QFile::remove(completedFilePath);
        emit downloadFailed(m_currentRequest.requestId, m_currentRequest.fileName,
                            "Downloaded file is empty");
        m_isProcessing = false;
        QTimer::singleShot(10, this, &ImageDownloader::processNextDownload);
        return;
    }

    // 이미지 파일 검증
    if (!validateImageFile(completedFilePath, m_currentRequest.fileName)) {
        QFile::remove(completedFilePath);
        emit downloadFailed(m_currentRequest.requestId, m_currentRequest.fileName,
                            "Image file validation failed");
        m_isProcessing = false;
        QTimer::singleShot(10, this, &ImageDownloader::processNextDownload);
        return;
    }

    // 최종 경로가 요청한 경로와 다른 경우에만 이동
    QString requestedPath = m_currentRequest.savePath;
    if (completedFilePath != requestedPath) {
        // 대상 디렉토리 생성
        QFileInfo finalFileInfo(requestedPath);
        QDir targetDir = finalFileInfo.absoluteDir();
        if (!targetDir.exists()) {
            targetDir.mkpath(".");
        }

        // 기존 파일 제거 후 이동
        if (QFile::exists(requestedPath)) {
            QFile::remove(requestedPath);
        }

        if (QFile::rename(completedFilePath, requestedPath)) {
            qDebug() << "Image moved from" << completedFilePath << "to" << requestedPath;
            emit downloadCompleted(m_currentRequest.requestId, m_currentRequest.fileName, requestedPath);
        } else {
            qDebug() << "Failed to move image, using current location:" << completedFilePath;
            emit downloadCompleted(m_currentRequest.requestId, m_currentRequest.fileName, completedFilePath);
        }
    } else {
        // 이미 올바른 위치에 있음
        qDebug() << "Image already in correct location:" << completedFilePath;
        emit downloadCompleted(m_currentRequest.requestId, m_currentRequest.fileName, completedFilePath);
    }

    // 다음 다운로드 처리
    m_isProcessing = false;
    QTimer::singleShot(10, this, &ImageDownloader::processNextDownload);
}

bool ImageDownloader::validateImageFile(const QString &filePath, const QString &fileName)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open file for validation:" << filePath;
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    if (data.isEmpty()) {
        qDebug() << "File data is empty:" << filePath;
        return false;
    }

    qDebug() << "File header for" << fileName << ":" << data.left(16).toHex();

    if (fileName.toLower().endsWith(".png")) {
        return validatePngFile(data);
    } else if (fileName.toLower().endsWith(".jpg") || fileName.toLower().endsWith(".jpeg")) {
        return validateJpegFile(data);
    }

    return true; // 기타 파일 형식은 통과
}

bool ImageDownloader::validatePngFile(const QByteArray &data)
{
    // PNG 시그니처 확인
    const QByteArray pngSignature = QByteArray::fromHex("89504E470D0A1A0A");
    if (!data.startsWith(pngSignature)) {
        qDebug() << "Invalid PNG signature";
        return false;
    }

    // IHDR 청크 확인
    if (data.size() < 33) {
        qDebug() << "PNG file too small";
        return false;
    }

    const QByteArray ihdrChunk = QByteArray::fromHex("49484452");
    if (data.mid(12, 4) != ihdrChunk) {
        qDebug() << "Missing IHDR chunk in PNG";
        return false;
    }

    return true; // 기본 검증 통과
}

bool ImageDownloader::validateJpegFile(const QByteArray &data)
{
    // JPEG 시그니처 확인: FF D8 FF
    if (data.size() < 3) {
        return false;
    }

    const QByteArray jpegSignature = QByteArray::fromHex("FFD8FF");
    if (!data.startsWith(jpegSignature)) {
        qDebug() << "Invalid JPEG signature";
        return false;
    }

    return true;
}

void ImageDownloader::onFileReceiveFailed(const QString &error)
{
    qDebug() << "Image download failed:" << error;
    emit downloadFailed(m_currentRequest.requestId, m_currentRequest.fileName, error);

    // 다음 다운로드 처리
    m_isProcessing = false;
    QTimer::singleShot(10, this, &ImageDownloader::processNextDownload);
}

void ImageDownloader::initializeTmpDirectory()
{
    // 기본 tmp 디렉토리 설정
    QString defaultTmpPath = QDir::currentPath() + "/tmp";
    setTmpDirectory(defaultTmpPath);
}

QString ImageDownloader::generateSavePath(const QString &fileName) const
{
    return QDir(m_tmpDirectory).absoluteFilePath(fileName);
}
