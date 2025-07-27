#include "UserMainWindow.h"
#include "ui_user_main_window.h"
#include <QDebug>
#include <QStandardItemModel>
UserMainWindow::UserMainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserMainWindow)
    , m_client(nullptr)
    , m_imageDownloader(nullptr)
{
    ui->setupUi(this);
    setAcceptDrops(true);

    // ClientSocket 초기화 및 연결
    m_client = new ClientSocket(this);
    connectServer();
    m_login = new LoginMainWindow(this, m_client);
    model = new QStandardItemModel(this);
    ui->listView_rooms->setModel(model);
    // ImageDownloader 초기화 및 연결
    m_imageDownloader = new ImageDownloader(this);
    connectImageDownloader();

    // 제품 목록 요청
    m_client->requestProductList();
    m_client->requestChatRoomList();
    connect(m_client, &ClientSocket::productListReceived, this, &UserMainWindow::onProductListReceived);
    connect(m_client, &ClientSocket::chatRoomListReceived, this, &UserMainWindow::onChatRoomListReceived);
    connect(ui->listView_rooms, &QListView::clicked, this, &UserMainWindow::onChatRoomClicked);

    connect(m_client, &ClientSocket::chatRoomJoined, this, &UserMainWindow::onChatRoomJoined);
    connect(m_client, &ClientSocket::chatRoomLeft, this, &UserMainWindow::onChatRoomLeft);
    connect(m_client, &ClientSocket::chatMessageSent, this, &UserMainWindow::onChatMessageSent);
    connect(m_client, &ClientSocket::chatHistoryReceived, this, &UserMainWindow::onChatHistoryReceived);
    connect(m_client, &ClientSocket::chatMessageReceived, this, &UserMainWindow::onChatMessageReceived);
    connect(m_client, &ClientSocket::errorOccurred, this, &UserMainWindow::onErrorOccurred);


    QFont font = ui->plainTextEdit_chat->font();
    font.bold();
    font.setPointSize(14);
    ui->plainTextEdit_chat->setFont(font);
    switchMainView(UserMainView::Shop);
}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}

void UserMainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
}

void UserMainWindow::dragLeaveEvent(QDragLeaveEvent* event)
{
    // 드래그 떠날 때 처리
}

void UserMainWindow::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();

    if (mimeData->hasText()) {
        // 타겟 위젯 찾기
        QPoint dropPos = event->position().toPoint();
        QGridLayout* targetLayout = getTargetLayoutAtPosition(dropPos);

        // 드롭된 위젯 찾기
        ProductWidget* draggedWidget = qobject_cast<ProductWidget*>(findWidgetByName(mimeData->text()));
        qDebug() << draggedWidget->productImageButton->text();

        if (!targetLayout) {
            qDebug() << "No target layout found at position:" << dropPos;
            return;
        }

        if (draggedWidget->parent()) {
            QGridLayout* oldLayout = qobject_cast<QGridLayout*>(draggedWidget->parentWidget()->layout());
            if (oldLayout) {
                oldLayout->removeWidget(draggedWidget);
            }
            draggedWidget->setParent(nullptr);
        }

        if (draggedWidget) {
            // 위젯을 새 위치로 이동
            targetLayout->addWidget(draggedWidget);
            rearrangeGridLayout(ui->layout_cartList, 1);
            rearrangeGridLayout(ui->layout_productList, PRODUCT_LIST_COL_SIZE);
        }
        event->acceptProposedAction();
    }
}

void UserMainWindow::rearrangeGridLayout(QGridLayout* layout, int maxColumns)
{
    if (!layout) return;

    // 모든 위젯 수집
    QList<QWidget*> widgets;
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            widgets.append(item->widget());
        }
        delete item;
    }

    // 다시 순서대로 배치
    for (int i = 0; i < widgets.size(); i++) {
        int row = i / maxColumns;
        int col = i % maxColumns;
        layout->addWidget(widgets[i], row, col, Qt::AlignTop | Qt::AlignLeft);
    }
}

QGridLayout* UserMainWindow::getTargetLayoutAtPosition(const QPoint& pos)
{
    // 해당 위치의 자식 위젯 찾기
    QWidget* childWidget = this->childAt(pos);

    if (!childWidget) {
        qDebug() << "No child widget at position:" << pos;
        return nullptr;
    }

    qDebug() << "Child widget at position:" << childWidget->objectName();

    // 위젯의 부모를 따라 올라가면서 ScrollArea 찾기
    QWidget* current = childWidget;
    while (current && current != this) {
        qDebug() << "Checking widget:" << current->objectName();

        if (current == ui->scrollArea_2 || current == ui->scrollAreaWidgetContents_2) {
            qDebug() << "Found product area";
            return ui->layout_productList;
        }

        if (current == ui->scrollArea || current == ui->scrollAreaWidgetContents) {
            qDebug() << "Found cart area";
            return ui->layout_cartList;
        }

        current = current->parentWidget();
    }

    qDebug() << "Could not determine target layout";
    return nullptr;
}

void UserMainWindow::onAnyProductDoubleClicked()
{
    ProductWidget* pw = qobject_cast<ProductWidget*>(sender());
    if (pw) {
        id_t roomId = pw->getChatRoomId();
        m_client->leaveChatRoom(m_currentChatRoomId, 0);
        switchMainView(UserMainView::Chat);
        selectChatRoomById(roomId);
        m_client->joinChatRoom(roomId, 0);
        qDebug() << "Product double-clicked:" << roomId;
    }
}

void UserMainWindow::onProductListReceived(const QJsonArray &products)
{
    qDebug() << QString("📦 제품 목록 수신 (%1개)").arg(products.size());

    int count = 0;
    for (const QJsonValue &value : products) {
        ProductWidget *productWidget = new ProductWidget();
        int row = count / PRODUCT_LIST_COL_SIZE;
        int col = count % PRODUCT_LIST_COL_SIZE;

        QJsonObject productJson = value.toObject();

        QString name = productJson.value("name").toString();
        QString category = productJson.value("category").toString();
        double price = productJson.value("price").toDouble();
        int stock = productJson.value("stock").toInt();
        id_t productId = productJson.value("productId").toInteger();
        id_t roomId = productJson.value("roomId").toInteger();
        QString imageFileName = productJson.value("imageFileName").toString();  // 이미지 파일명 추가

        // 제품 정보 설정 (이미지 파일명 포함)
        if (!imageFileName.isEmpty()) {
            productWidget->setInfo(productId, roomId, category, name, price, stock, imageFileName);

            // 파일명 -> 위젯 매핑 저장
            m_fileNameToWidget[imageFileName] = productWidget;
        } else {
            productWidget->setInfo(productId, roomId, category, name, price, stock);
        }

        productWidget->setObjectName(QString("product_%1").arg(count));
        connect(productWidget, SIGNAL(doubleClicked()), this, SLOT(onAnyProductDoubleClicked()));
        ui->layout_productList->addWidget(productWidget, row, col, Qt::AlignTop | Qt::AlignLeft);

        qDebug() << QString("  - [%1] %2 (%3) - %4, 재고: %5개, 이미지: %6")
                        .arg(productId)
                        .arg(name, category)
                        .arg(price)
                        .arg(stock)
                        .arg(imageFileName.isEmpty() ? "없음" : imageFileName);
        count++;
    }

    rearrangeGridLayout(ui->layout_cartList, 1);
    rearrangeGridLayout(ui->layout_productList, PRODUCT_LIST_COL_SIZE);

    // 제품 목록 로딩 완료 후 이미지 다운로드 시작
    downloadProductImages();
}



void UserMainWindow::onChatRoomListReceived(const QJsonArray &rooms){

    qDebug() << QString("📦 채팅방 목록 수신 (%1개)").arg(rooms.size());
    int count = 0;
    for (const QJsonValue &value : rooms) {
        count++;
        QJsonObject chatRoomJson = value.toObject();
        QString name = chatRoomJson.value("chatRoomName").toString();
        id_t roomId = chatRoomJson.value("chatRoomId").toInteger();
        QStandardItem* item = new QStandardItem(name);
        QFont font = item->font();
        font.setPointSize(20);
        item->setFont(font);
        item->setEditable(false);
        item->setData(roomId, Qt::UserRole + 1);
        model->appendRow(item);

    }
}


void UserMainWindow::connectServer()
{
    if (!m_client->isConnected()) {
        QString host = "192.168.2.181";
        quint16 port = 5105;

        qDebug() << QString("JSON 서버 연결 시도: %1:%2").arg(host).arg(port);
        bool success = m_client->connectToServer(host, port);

        if (!success) {
            qDebug("JSON 서버 연결에 실패했습니다.");
        } else {
            qDebug("JSON 서버 연결 성공!");
        }
    } else {
        m_client->disconnectFromServer();
    }
}

void UserMainWindow::connectImageDownloader()
{
    // ImageDownloader 시그널 연결
    connect(m_imageDownloader, &ImageDownloader::connected, this, []() {
        qDebug() << "✅ 이미지 다운로드 서버 연결 성공!";
    });

    connect(m_imageDownloader, &ImageDownloader::disconnected, this, []() {
        qDebug() << "❌ 이미지 다운로드 서버 연결 해제";
    });

    connect(m_imageDownloader, &ImageDownloader::errorOccurred, this, [](const QString &error) {
        qDebug() << "🔥 이미지 다운로드 서버 오류:" << error;
    });

    connect(m_imageDownloader, &ImageDownloader::downloadCompleted,
            this, &UserMainWindow::onImageDownloadCompleted);
    connect(m_imageDownloader, &ImageDownloader::downloadFailed,
            this, &UserMainWindow::onImageDownloadFailed);
    connect(m_imageDownloader, &ImageDownloader::downloadProgress,
            this, &UserMainWindow::onImageDownloadProgress);

    // 이미지 서버에 연결
    QString host = "192.168.2.181";
    quint16 port = 5115;

    qDebug() << QString("이미지 서버 연결 시도: %1:%2").arg(host).arg(port);
    bool success = m_imageDownloader->connectToServer(host, port);

    if (!success) {
        qDebug("이미지 서버 연결에 실패했습니다.");
    }
}

void UserMainWindow::downloadProductImages()
{
    if (!m_imageDownloader->isConnected()) {
        qDebug() << "이미지 서버가 연결되지 않았습니다. 다운로드를 건너뜁니다.";
        return;
    }

    qDebug() << QString("🔄 제품 이미지 다운로드 시작 (%1개 파일)").arg(m_fileNameToWidget.size());

    // 각 제품의 이미지 파일 다운로드 요청
    for (auto it = m_fileNameToWidget.begin(); it != m_fileNameToWidget.end(); ++it) {
        const QString &fileName = it.key();
        ProductWidget *widget = it.value();

        // 이미 다운로드된 이미지인지 확인
        if (m_imageDownloader->imageExists(fileName)) {
            qDebug() << "이미지가 이미 존재함:" << fileName;
            updateProductImage(widget, m_imageDownloader->getImagePath(fileName));
            continue;
        }

        // 이미지 다운로드 요청
        int requestId = m_imageDownloader->requestImage(fileName);
        if (requestId != -1) {
            m_downloadRequests[requestId] = widget;
            qDebug() << QString("이미지 다운로드 요청: %1 (RequestID: %2)").arg(fileName).arg(requestId);
        }
    }
}

void UserMainWindow::updateProductImage(ProductWidget* widget, const QString &imagePath)
{
    if (widget) {
        widget->setProductImage(imagePath);
        qDebug() << "제품 이미지 업데이트 완료:" << imagePath;
    }
}

void UserMainWindow::onImageDownloadCompleted(int requestId, const QString &fileName, const QString &savedPath)
{
    qDebug() << QString("📥 이미지 다운로드 완료: %1 → %2").arg(fileName).arg(savedPath);

    // 요청 ID로 위젯 찾기
    if (m_downloadRequests.contains(requestId)) {
        ProductWidget *widget = m_downloadRequests[requestId];
        updateProductImage(widget, savedPath);
        m_downloadRequests.remove(requestId);
    }
}

void UserMainWindow::onImageDownloadFailed(int requestId, const QString &fileName, const QString &error)
{
    qDebug() << QString("❌ 이미지 다운로드 실패: %1 - %2").arg(fileName).arg(error);

    // 실패한 요청 정리
    if (m_downloadRequests.contains(requestId)) {
        ProductWidget *widget = m_downloadRequests[requestId];
        // 실패 시 기본 이미지로 설정
        widget->setDefaultImage();
        m_downloadRequests.remove(requestId);
    }
}

void UserMainWindow::onImageDownloadProgress(int requestId, qint64 bytesReceived, qint64 totalBytes)
{
    // 진행률 로그 (필요시 UI 업데이트)
    int progress = (bytesReceived * 100) / totalBytes;
    if (progress % 25 == 0) { // 25% 단위로만 로그
        qDebug() << QString("📊 다운로드 진행률 (RequestID %1): %2%").arg(requestId).arg(progress);
    }
}

void UserMainWindow::switchMainView(UserMainView view)
{
    ui->stackedWidget->setCurrentIndex(static_cast<int>(view));
    QRect shop_geo = ui->pushButton_shop->geometry();
    QRect chat_geo = ui->pushButton_chat->geometry();
    if(view == UserMainView::Shop){
        ui->pushButton_shop->setStyleSheet(QString("QPushButton{ \
                                                        background: qlineargradient(x1:0, y1:0, x2:1, y2:1, \
                                                                stop:0 #7fdbda, stop:1 #5fb3b3); \
                                                        color: #1a1a1a; \
                                                        border-radius: 20px; \
                                                        padding: 10px 20px; \
                                                        max-width: 1040px; \
                                                    }"
                                                   ));
        ui->pushButton_chat->setStyleSheet(QString("QPushButton{ \
                                                        background: qlineargradient(x1:0, y1:0, x2:1, y2:1, \
                                                                stop:0 #a8edea, stop:1 #7dd3fc); \
                                                        color: #1a1a1a; \
                                                        border-radius: 20px; \
                                                        padding: 10px 20px; \
                                                        max-width: 400px; \
                                                    }"
                                                   ));


        // chat_geo.setX(shop_geo.left()+1040+10);
        // shop_geo.setWidth(1040);
        // chat_geo.setWidth(400);

        // ui->pushButton_shop->setGeometry(shop_geo);
        // ui->pushButton_chat->setGeometry(chat_geo);
        // ui->pushButton_shop->hasFocus();
    }else if(view == UserMainView::Chat){

        ui->pushButton_chat->setStyleSheet(QString("QPushButton{ \
                                                        background: qlineargradient(x1:0, y1:0, x2:1, y2:1, \
                                                                stop:0 #7fdbda, stop:1 #5fb3b3); \
                                                        color: #1a1a1a; \
                                                        font-weight: bold; \
                                                        border-radius: 20px; \
                                                        padding: 10px 20px; \
                                                        max-width: 1040px; \
                                                    }"
                                                   ));
        ui->pushButton_shop->setStyleSheet(QString("QPushButton{ \
                                                        background: qlineargradient(x1:0, y1:0, x2:1, y2:1, \
                                                                stop:0 #a8edea, stop:1 #7dd3fc); \
                                                        color: #1a1a1a; \
                                                        border-radius: 20px; \
                                                        padding: 10px 20px; \
                                                        max-width: 400px; \
                                                    }"
                                                   ));


        // chat_geo.setX(shop_geo.left()+400+10);
        // shop_geo.setWidth(400);
        // chat_geo.setWidth(1040);
        // ui->pushButton_shop->setGeometry(shop_geo);
        // ui->pushButton_chat->setGeometry(chat_geo);
        // ui->pushButton_chat->hasFocus();
    }
}

void UserMainWindow::on_pushButton_shop_clicked()
{
    switchMainView(UserMainView::Shop);
}

void UserMainWindow::on_pushButton_chat_clicked()
{
    switchMainView(UserMainView::Chat);
}

void UserMainWindow::selectChatRoomById(id_t roomIdToSelect) {
    for (int row = 0; row < model->rowCount(); ++row) {
        QStandardItem* item = model->item(row);
        id_t roomId = item->data(Qt::UserRole + 1).toInt();  // 저장된 roomId 추출

        if (roomId == roomIdToSelect) {
            QModelIndex index = model->indexFromItem(item);
            ui->listView_rooms->setCurrentIndex(index);  // 현재 선택
            ui->listView_rooms->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);
            break;
        }
    }
}

void UserMainWindow::onChatRoomClicked(const QModelIndex& index) {
    QString roomName = index.data(Qt::DisplayRole).toString();
    if(m_currentChatRoomId>0){
        m_client->leaveChatRoom(m_currentChatRoomId, 0);
    }

    id_t roomId = index.data(Qt::UserRole+1).toInt();
    m_currentChatRoomId = roomId;
    qDebug() << "채팅방 선택됨:" << roomName << "(" << roomId << ")";
    m_client->leaveChatRoom(roomId, 0);

    qDebug() << "채팅방 열기:" << roomName;
    switchMainView(UserMainView::Chat);
    // selectChatRoomById(roomId);
    m_client->joinChatRoom(roomId, 0);
}


void UserMainWindow::requestChatRoomJoin(id_t roomId) {
    if(m_currentChatRoomId>0){
        m_client->leaveChatRoom(m_currentChatRoomId, 0);
    }
    m_currentChatRoomId = roomId;
    // selectChatRoomById(roomId);
    m_client->joinChatRoom(roomId, 0);
}

void UserMainWindow::openChatRoom(const QString& roomName) {

    // 예: QWidget을 띄우거나 데이터 로딩 등
}

void UserMainWindow::onChatRoomJoined(const QJsonObject &chatRoom)
{
    qDebug() << "Debug :: chatRoom "<< chatRoom;
    if(chatRoom.empty()){
        qDebug() << "charRoom empty";
        qDebug() <<QString("❌ 채팅방 참여 실패!");
        requestChatRoomJoin(m_currentChatRoomId);
        return;
    }
    int roomId = chatRoom.value("chatRoomId").toInt();
    QString roomName = chatRoom.value("chatRoomName").toString();

    qDebug() <<QString("✅ 채팅방 참여 완료 - ID: %1, 이름: %2").arg(roomId).arg(roomName);
    // ui->plainTextEdit_chat->clear();
    m_client->requestChatHistory(roomId);
}

void UserMainWindow::onChatRoomLeft(bool success)
{
    if (success) {
        qDebug() <<"✅ 채팅방 나가기 완료";
    } else {
        qDebug() <<"❌ 채팅방 나가기 실패";
    }
}

void UserMainWindow::onChatMessageSent(const QJsonObject &message)
{
    int chatId = message.value("chatId").toInt();
    QString chatStr = message.value("chatStr").toString();

    qDebug() <<QString("✅ 메시지 전송 완료 - ID: %1, 내용: %2").arg(chatId).arg(chatStr);

    m_client->requestChatHistory(m_currentChatRoomId);
    ui->lineEdit->clear();
}

void UserMainWindow::onChatHistoryReceived(const QJsonArray &messages)
{
    qDebug() <<QString("💬 채팅 기록 수신 (%1개):").arg(messages.size());

    ui->plainTextEdit_chat->clear();

    ui->plainTextEdit_chat->appendPlainText(QString("환영합니다!!!"));
    for (const QJsonValue &value : messages) {
        QJsonObject message = value.toObject();
        int userId = message.value("userId").toInt();
        QString userName = message.value("userName").toString();
        QString chatStr = message.value("chatStr").toString();
        QString chatTime = message.value("chatTime").toString();
        QString chatlog = QString("[%1]: %2").arg(userName).arg(chatStr);
        qDebug() << "json Debug ||| " << messages;
        qDebug() << chatlog;
        ui->plainTextEdit_chat->appendPlainText(chatlog);
    }
}

void UserMainWindow::onChatMessageReceived(const QJsonObject &message)
{
    QString userName = message.value("userName").toString();
    QString chatStr = message.value("chatStr").toString();
    QString chatlog = QString("[%1]: %2").arg(userName).arg(chatStr);
    qDebug() << chatlog;
    ui->plainTextEdit_chat->appendPlainText(chatlog);
}

void UserMainWindow::on_lineEdit_editingFinished()
{
    QString chatText = ui->lineEdit->text();
    m_client->sendChatMessage(m_currentChatRoomId,chatText);
}

void UserMainWindow::onErrorOccurred(const QString &error)
{
    qDebug() << QString("⚠️ 오류: %1").arg(error);
}
