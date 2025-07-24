#include "UserMainWindow.h"
#include "ui_user_main_window.h"


UserMainWindow::UserMainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserMainWindow)
{

    ui->setupUi(this);
    setAcceptDrops(true);
    m_client = new ClientSocket(this);
    connectServer();
    m_client->requestProductList();

    connect(m_client, &ClientSocket::productListReceived, this, &UserMainWindow::onProductListReceived);
}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}

void UserMainWindow::dragEnterEvent(QDragEnterEvent* event){
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
        // setStyleSheet("border: 2px dashed #0080ff;"); // 드래그 시 하이라이트
    }
}

void UserMainWindow::dragLeaveEvent(QDragLeaveEvent* event){
    // setStyleSheet("border: 2px dashed #aaa;"); // 원래 스타일로 복원
}

void UserMainWindow::dropEvent(QDropEvent* event){
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
            rearrangeGridLayout(ui->layout_cartList,1);
            rearrangeGridLayout(ui->layout_productList, PRODUCT_LIST_COL_SIZE);
        }
        event->acceptProposedAction();
    }

    // setStyleSheet("border: 2px dashed #aaa;");
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
        qDebug() << "Product double-clicked:" << roomId;
    }
}

void UserMainWindow::onProductListReceived(const QJsonArray &products)
{
    // addLogMessage(QString("📦 제품 목록 수신 (%1개):").arg(products.size()));
    int count = 0;
    for (const QJsonValue &value : products) {
        ProductWidget *productWidget = new ProductWidget();
        // product->setFixedSize(QSize(320,260));
        int row = count/PRODUCT_LIST_COL_SIZE;
        int col = count%PRODUCT_LIST_COL_SIZE;

        QJsonObject productJson = value.toObject();

        QString name = productJson.value("name").toString();
        QString category = productJson.value("category").toString();
        double price = productJson.value("price").toDouble();
        int stock = productJson.value("stock").toInt();
        id_t productId = productJson.value("productId").toInteger();
        id_t roomId = productJson.value("roomId").toInteger();

        productWidget->setInfo(productId, roomId, category, name, price, stock);
        productWidget->setObjectName(QString("product_%1").arg(count));
        productWidget->productImageButton->setText(QString("Item%1-%2").arg(row).arg(col));
        connect(productWidget, SIGNAL(doubleClicked()), this, SLOT(onAnyProductDoubleClicked()));
        ui->layout_productList->addWidget(productWidget,row,col,Qt::AlignTop|Qt::AlignLeft);
        qDebug() << QString("  - [%1] %2 (%3) - %4, 재고: %5개")
                          .arg(productId)
                          .arg(name, category)
                          .arg(price)
                          .arg(stock);
        count++;
    }
    rearrangeGridLayout(ui->layout_cartList,1);
    rearrangeGridLayout(ui->layout_productList, PRODUCT_LIST_COL_SIZE);
}

void UserMainWindow::connectServer()
{
    if (!m_client->isConnected()) {
        QString host = "192.168.2.181";
        quint16 port = 5105;

        qDebug() << QString("서버 연결 시도: %1:%2").arg(host).arg(port);
        bool success = m_client->connectToServer(host, port);

        if (!success) {
            qDebug("서버 연결에 실패했습니다.");
        }
    } else {
        m_client->disconnectFromServer();
    }
}


void UserMainWindow::switchMainView(UserMainView view)
{
    ui->stackedWidget->setCurrentIndex(static_cast<int>(view));
}

void UserMainWindow::on_pushButton_shop_clicked()
{
    switchMainView(UserMainView::Shop);
}


void UserMainWindow::on_pushButton_chat_clicked()
{
    switchMainView(UserMainView::Chat);
}

