#include "ProductWidget.h"
#include "ui_product_widget.h"
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QThread>
#include <QImageReader>
#include <QBuffer>

ProductWidget::ProductWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProductWidget)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    productNameLabel = ui->label_productName;
    productImageButton = ui->pushButton_mainImage;

    // 기본 이미지 설정
    setDefaultImage();

    connect(productImageButton, &DoubleClickButton::doubleClicked, this, &ProductWidget::doubleClicked);
}

ProductWidget::~ProductWidget()
{
    delete ui;
}

void ProductWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragStartPosition = event->pos();
    }
}

void ProductWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;

    if ((event->pos() - m_dragStartPosition).manhattanLength() < QApplication::startDragDistance())
        return;

    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData;

    // 위젯 정보를 MIME 데이터로 저장
    mimeData->setText(objectName());
    drag->setMimeData(mimeData);

    // 드래그 이미지 설정
    QPixmap pixmap = grab();
    drag->setPixmap(pixmap);

    Qt::DropAction dropAction = drag->exec(Qt::MoveAction);
}

void ProductWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit doubleClicked();
    }
}

id_t ProductWidget::getChatRoomId()
{
    return m_roomId;
}

void ProductWidget::setChatRoomId(id_t roomId)
{
    m_roomId = roomId;
}

void ProductWidget::setInfo(id_t id, id_t roomId, QString category, QString name, qreal price, qint32 stock)
{
    m_id = id;
    m_roomId = roomId;
    m_category = category;
    m_name = name;
    m_price = price;
    m_stock = stock;
    productNameLabel->setText(m_name + " : " + m_category);

    // 이미지 파일명이 없으면 기본 이미지 유지
    if (m_imageFileName.isEmpty()) {
        setDefaultImage();
    }
}

void ProductWidget::setInfo(id_t id, id_t roomId, QString category, QString name, qreal price, qint32 stock, const QString &imageFileName)
{
    // 기존 setInfo 호출
    setInfo(id, roomId, category, name, price, stock);

    // 이미지 파일명 설정
    m_imageFileName = imageFileName;

    // 이미지 파일명이 있으면 해당 이미지로 설정 시도
    if (!imageFileName.isEmpty()) {
        QString imagePath = QString("tmp/%1").arg(imageFileName);
        if (QFileInfo::exists(imagePath)) {
            setProductImage(imagePath);
        } else {
            // 파일이 없으면 기본 이미지 + 파일명 텍스트 표시
            setDefaultImage();
            productImageButton->setText(QString("Loading...\n%1").arg(imageFileName));
        }
    }
}

void ProductWidget::setProductImage(const QString &imagePath)
{
    QFileInfo fileInfo(imagePath);
    if (!fileInfo.exists()) {
        qDebug() << "ProductWidget: Image file not found:" << imagePath;
        setDefaultImage();
        return;
    }

    if (fileInfo.size() == 0) {
        qDebug() << "ProductWidget: Image file is empty:" << imagePath;
        setDefaultImage();
        return;
    }

    // 여러 방법으로 이미지 로딩 시도
    QPixmap pixmap;

    // 방법 1: QImageReader로 시도 (가장 강력)
    if (loadImageWithReader(imagePath, pixmap)) {
        setPixmapToButton(pixmap, imagePath);
        return;
    }

    // 방법 2: 바이트 배열로 시도
    if (loadImageFromBytes(imagePath, pixmap)) {
        setPixmapToButton(pixmap, imagePath);
        return;
    }

    // 방법 4: 외부 이미지 뷰어로 검증 (디버깅용)
    debugImageFile(imagePath);

    // 모든 방법 실패 시 기본 이미지
    qDebug() << "ProductWidget: All image loading methods failed for:" << imagePath;
    setDefaultImage();
}


void ProductWidget::setDefaultImage()
{
    QString defaultImagePath = getDefaultImagePath();

    // 기본 이미지 파일이 있으면 사용
    if (QFileInfo::exists(defaultImagePath)) {
        QPixmap defaultPixmap(defaultImagePath);
        if (!defaultPixmap.isNull()) {
            QPixmap scaledPixmap = scaleImageToButton(defaultPixmap);
            productImageButton->setIcon(QIcon(scaledPixmap));
            productImageButton->setIconSize(scaledPixmap.size());
            productImageButton->setText("");
            return;
        }
    }

    // 기본 이미지가 없으면 회색 배경에 텍스트 표시
    productImageButton->setIcon(QIcon()); // 아이콘 제거
    productImageButton->setText("No Image");
    productImageButton->setStyleSheet("QPushButton { background-color: #f0f0f0; color: #666; font-size: 12px; }");
}

QPixmap ProductWidget::scaleImageToButton(const QPixmap &originalPixmap) const
{
    // 버튼 크기 (210x210)에 맞게 이미지 스케일링
    QSize buttonSize(210, 210);
    return originalPixmap.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

QString ProductWidget::getDefaultImagePath() const
{
    // 기본 이미지 경로들을 시도
    QStringList defaultPaths = {
        "images/default_product.png",
        "images/default_product.jpg",
        "resources/default_product.png",
        ":/images/default_product.png"  // Qt 리소스
    };

    for (const QString &path : defaultPaths) {
        if (QFileInfo::exists(path)) {
            return path;
        }
    }

    return QString(); // 기본 이미지가 없음
}


bool ProductWidget::loadImageWithReader(const QString &imagePath, QPixmap &pixmap)
{
    QImageReader reader(imagePath);

    // 지원되는 형식 확인
    if (!reader.canRead()) {
        qDebug() << "QImageReader cannot read:" << imagePath;
        qDebug() << "Detected format:" << reader.format();
        qDebug() << "Error:" << reader.errorString();
        return false;
    }

    // 이미지 크기 제한 (메모리 보호)
    QSize imageSize = reader.size();
    if (imageSize.width() > 2000 || imageSize.height() > 2000) {
        reader.setScaledSize(QSize(500, 500));
        qDebug() << "Large image scaled down:" << imageSize;
    }

    // 이미지 읽기
    QImage image = reader.read();
    if (image.isNull()) {
        qDebug() << "QImageReader failed to read image:" << reader.errorString();
        return false;
    }

    pixmap = QPixmap::fromImage(image);
    qDebug() << "Successfully loaded with QImageReader:" << imagePath;
    return true;
}

bool ProductWidget::loadImageFromBytes(const QString &imagePath, QPixmap &pixmap)
{
    QFile file(imagePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open file for byte loading:" << imagePath;
        return false;
    }

    QByteArray imageData = file.readAll();
    file.close();

    if (imageData.isEmpty()) {
        qDebug() << "Image data is empty";
        return false;
    }

    // QBuffer를 통한 로딩
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::ReadOnly);

    QImageReader bufferReader(&buffer);
    bufferReader.setAutoDetectImageFormat(true);

    // 여러 형식으로 시도
    QStringList formats = {"PNG", "JPEG", "JPG", "BMP", "GIF"};
    for (const QString &format : formats) {
        buffer.seek(0);
        bufferReader.setFormat(format.toLocal8Bit());

        QImage image = bufferReader.read();
        if (!image.isNull()) {
            pixmap = QPixmap::fromImage(image);
            qDebug() << "Successfully loaded as" << format << "from bytes:" << imagePath;
            return true;
        }
    }

    // 직접 QPixmap으로 시도
    if (pixmap.loadFromData(imageData)) {
        qDebug() << "Successfully loaded with loadFromData:" << imagePath;
        return true;
    }

    return false;
}


bool ProductWidget::repairAndLoadPng(const QString &imagePath, const QString &repairedPath, QPixmap &pixmap)
{
    qDebug() << "Attempting PNG repair for:" << imagePath;

    QFile file(imagePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    // PNG 시그니처 확인
    const QByteArray pngSignature = QByteArray::fromHex("89504E470D0A1A0A");
    if (!data.startsWith(pngSignature)) {
        qDebug() << "Not a valid PNG file";
        return false;
    }

    // 손상된 청크 제거 및 필수 청크 확인
    QByteArray repairedData = repairPngChunks(data);

    // 복구된 데이터를 파일로 저장
    QFile repairedFile(repairedPath);
    if (!repairedFile.open(QIODevice::WriteOnly)) {
        return false;
    }

    repairedFile.write(repairedData);
    repairedFile.close();

    // 복구된 파일로 로딩 시도
    QThread::msleep(100); // 파일 쓰기 완료 대기

    if (pixmap.load(repairedPath)) {
        qDebug() << "Successfully loaded repaired PNG:" << repairedPath;
        return true;
    }

    // QImageReader로 다시 시도
    QImageReader reader(repairedPath);
    reader.setFormat("PNG");
    QImage image = reader.read();
    if (!image.isNull()) {
        pixmap = QPixmap::fromImage(image);
        qDebug() << "Successfully loaded repaired PNG with QImageReader";
        return true;
    }

    // 복구 실패
    QFile::remove(repairedPath);
    return false;
}

QByteArray ProductWidget::repairPngChunks(const QByteArray &originalData)
{
    QByteArray repairedData;

    // PNG 시그니처 추가
    repairedData.append(QByteArray::fromHex("89504E470D0A1A0A"));

    // 원본 데이터에서 시그니처 제거
    QByteArray chunkData = originalData.mid(8);

    int pos = 0;
    bool hasIEND = false;

    while (pos < chunkData.size() - 8) {
        // 청크 길이 읽기
        if (pos + 4 > chunkData.size()) break;

        quint32 chunkLength = qFromBigEndian<quint32>(
            reinterpret_cast<const uchar*>(chunkData.data() + pos));
        pos += 4;

        // 청크 타입 읽기
        if (pos + 4 > chunkData.size()) break;
        QByteArray chunkType = chunkData.mid(pos, 4);
        pos += 4;

        // 청크 데이터 읽기
        if (pos + static_cast<int>(chunkLength) > chunkData.size()) {
            qDebug() << "Truncated chunk detected:" << chunkType;
            break;
        }
        QByteArray chunkDataBytes = chunkData.mid(pos, chunkLength);
        pos += chunkLength;

        // CRC 읽기
        if (pos + 4 > chunkData.size()) break;
        QByteArray chunkCRC = chunkData.mid(pos, 4);
        pos += 4;

        // IEND 청크 확인
        if (chunkType == "IEND") {
            hasIEND = true;
        }

        // 청크를 복구된 데이터에 추가 (CRC 검증 생략)
        repairedData.append(qToBigEndian(chunkLength));
        repairedData.append(chunkType);
        repairedData.append(chunkDataBytes);
        repairedData.append(chunkCRC);

        qDebug() << "Added chunk:" << chunkType << "Length:" << chunkLength;
    }

    // IEND 청크가 없으면 추가
    if (!hasIEND) {
        qDebug() << "Adding missing IEND chunk";
        repairedData.append(QByteArray::fromHex("0000000049454E44AE426082"));
    }

    return repairedData;
}

void ProductWidget::debugImageFile(const QString &imagePath)
{
    QFile file(imagePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    qDebug() << "=== Image Debug Info ===";
    qDebug() << "File:" << imagePath;
    qDebug() << "Size:" << data.size() << "bytes";
    qDebug() << "First 32 bytes:" << data.left(32).toHex(' ');
    qDebug() << "Last 32 bytes:" << data.right(32).toHex(' ');

    // PNG 청크 분석
    if (data.startsWith(QByteArray::fromHex("89504E470D0A1A0A"))) {
        analyzePngChunks(data);
    }

    qDebug() << "========================";
}

void ProductWidget::analyzePngChunks(const QByteArray &data)
{
    qDebug() << "PNG Chunk Analysis:";

    int pos = 8; // Skip PNG signature
    int chunkCount = 0;

    while (pos < data.size() - 8 && chunkCount < 10) { // Limit to first 10 chunks
        if (pos + 8 > data.size()) break;

        quint32 length = qFromBigEndian<quint32>(
            reinterpret_cast<const uchar*>(data.data() + pos));
        QByteArray type = data.mid(pos + 4, 4);

        qDebug() << "Chunk" << chunkCount << ":" << type << "Length:" << length;

        pos += 8 + length + 4; // length + type + data + CRC
        chunkCount++;

        if (type == "IEND") {
            qDebug() << "Found IEND chunk at position" << pos;
            break;
        }
    }
}

void ProductWidget::setPixmapToButton(const QPixmap &pixmap, const QString &imagePath)
{
    QPixmap scaledPixmap = scaleImageToButton(pixmap);
    productImageButton->setIcon(QIcon(scaledPixmap));
    productImageButton->setIconSize(scaledPixmap.size());
    productImageButton->setText("");

    qDebug() << "ProductWidget: Image set successfully:" << imagePath
             << "Original size:" << pixmap.size()
             << "Scaled size:" << scaledPixmap.size();
}
