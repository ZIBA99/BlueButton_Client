#include "UserMainWindow.h"
#include "ui_user_main_window.h"

UserMainWindow::UserMainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserMainWindow)
{
    setAcceptDrops(true);
    ui->setupUi(this);
}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}
void UserMainWindow::dragEnterEvent(QDragEnterEvent* event){
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
        setStyleSheet("border: 2px dashed #0080ff;"); // 드래그 시 하이라이트
    }
}

void UserMainWindow::dragLeaveEvent(QDragLeaveEvent* event){
    setStyleSheet("border: 2px dashed #aaa;"); // 원래 스타일로 복원
}

void UserMainWindow::dropEvent(QDropEvent* event){
    const QMimeData* mimeData = event->mimeData();

    if (mimeData->hasText()) {
        QPoint dropPos = event->position().toPoint();

        // 드롭된 위젯 찾기
        QWidget* draggedWidget = findWidgetByName(mimeData->text());
        if (draggedWidget) {
            // 위젯을 새 위치로 이동
            draggedWidget->setParent(this);
            draggedWidget->move(dropPos);
            draggedWidget->show();
        }

        event->acceptProposedAction();
    }

    setStyleSheet("border: 2px dashed #aaa;");
}
