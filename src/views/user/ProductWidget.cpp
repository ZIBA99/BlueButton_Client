#include "ProductWidget.h"
#include "ui_product_widget.h"


ProductWidget::ProductWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProductWidget)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    productNameLabel = ui->label_productName;
    productImageButton = ui->pushButton_mainImage;
    // connect(productImageButton,&DoubleClickButton::doubleClicked, &ProductWidget::onDoubleClicked);
    connect(productImageButton, &DoubleClickButton::doubleClicked, this, &ProductWidget::doubleClicked);
}

ProductWidget::~ProductWidget()
{
    delete ui;
}

void ProductWidget::mousePressEvent(QMouseEvent* event){
    if (event->button() == Qt::LeftButton) {
        m_dragStartPosition = event->pos();
    }
}

void ProductWidget::mouseMoveEvent(QMouseEvent* event){
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

void ProductWidget::mouseDoubleClickEvent(QMouseEvent* event){
    if (event->button() == Qt::LeftButton) {
        emit doubleClicked();
    }
}

id_t ProductWidget::getChatRoomId(){
    return m_roomId;
}

void ProductWidget::setChatRoomId(id_t roomId){
    m_roomId = roomId;
}


void ProductWidget::setInfo(id_t id , id_t roomId, QString category, QString name , qreal price, qint32 stock){
    m_id = id;
    m_roomId = roomId;
    m_category = category;
    m_name = name;
    m_price = price;
    m_stock = stock;
    productNameLabel->setText(m_name+" : "+m_category);
}
