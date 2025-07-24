#ifndef IMAGEDOWNLOADER_H
#define IMAGEDOWNLOADER_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QQueue>
#include <QDir>
#include <QThread>
#include "FileTransfer.h"

struct ImageDownloadRequest {
    QString fileName;
    QString savePath;
    int requestId;
};

class ImageDownloader : public QObject
{
    Q_OBJECT

public:
    explicit ImageDownloader(QObject *parent = nullptr);
    ~ImageDownloader();

    // 서버 연결 관리
    bool connectToServer(const QString &host, quint16 port = 5115);
    void disconnectFromServer();
    bool isConnected() const;

    // 이미지 다운로드 요청
    int requestImage(const QString &fileName);
    int requestImage(const QString &fileName, const QString &customSavePath);

    // tmp 디렉토리 설정
    void setTmpDirectory(const QString &tmpPath);
    QString tmpDirectory() const { return m_tmpDirectory; }

    // 상태 확인
    bool isDownloading() const;
    int queueSize() const { return m_downloadQueue.size(); }

    // 유틸리티
    QString getImagePath(const QString &fileName) const;
    bool imageExists(const QString &fileName) const;

signals:
    void connected();
    void disconnected();
    void errorOccurred(const QString &error);

    // 다운로드 관련 시그널
    void downloadStarted(int requestId, const QString &fileName);
    void downloadProgress(int requestId, qint64 bytesReceived, qint64 totalBytes);
    void downloadCompleted(int requestId, const QString &fileName, const QString &savedPath);
    void downloadFailed(int requestId, const QString &fileName, const QString &error);

    // 큐 관리 시그널
    void queueEmpty();

private slots:
    void onConnected();
    void onDisconnected();
    void onSocketError(QAbstractSocket::SocketError error);
    void processNextDownload();

    // FileTransfer 시그널 처리
    void onFileReceiveStarted(const QString &fileName, qint64 totalSize);
    void onFileReceiveProgress(qint64 bytesReceived, qint64 totalBytes);
    void onFileReceiveCompleted(const QString &fileName);
    void onFileReceiveFailed(const QString &error);

private:
    QTcpSocket *m_socket;
    FileTransfer *m_fileTransfer;

    // 다운로드 큐 관리
    QQueue<ImageDownloadRequest> m_downloadQueue;
    ImageDownloadRequest m_currentRequest;
    bool m_isProcessing;
    int m_nextRequestId;

    // 경로 관리
    QString m_tmpDirectory;

    // 유틸리티 메서드
    void initializeTmpDirectory();
    void processCurrentRequest();
    QString generateSavePath(const QString &fileName) const;


    // 이미지 파일 검증 메서드들
    bool validateImageFile(const QString &filePath, const QString &fileName);
    bool validatePngFile(const QByteArray &data);
    bool validateJpegFile(const QByteArray &data);
};

#endif // IMAGEDOWNLOADER_H
