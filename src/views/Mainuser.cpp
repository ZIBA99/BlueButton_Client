// #include "Mainuser.h"
// #include "ui_main_user.h"
// #include <QWidget>
// #include <QVBoxLayout>
// #include <QLabel>

// MainUser::MainUser(QWidget *parent)
//     : QMainWindow(parent)
//     , ui(new Ui::MainUser)
// {
//     ui->setupUi(this);

//     stackedWidget = new QStackedWidget(this);

//     // 6개의 위젯 생성 및 추가
//     QWidget *page1 = new QWidget();
//     QVBoxLayout *layout1 = new QVBoxLayout(page1);
//     layout1->addWidget(new QLabel("제품 페이지", page1));

//     QWidget *page2 = new QWidget();
//     QVBoxLayout *layout2 = new QVBoxLayout(page2);
//     layout2->addWidget(new QLabel("교육 정보 및 신청 페이지", page2));

//     QWidget *page3 = new QWidget();
//     QVBoxLayout *layout3 = new QVBoxLayout(page3);
//     layout3->addWidget(new QLabel("교육 소통방 페이지", page3));

//     QWidget *page4 = new QWidget();
//     QVBoxLayout *layout4 = new QVBoxLayout(page4);
//     layout4->addWidget(new QLabel("스스로 해결 페이지", page4));

//     QWidget *page5 = new QWidget();
//     QVBoxLayout *layout5 = new QVBoxLayout(page5);
//     layout5->addWidget(new QLabel("제품 불만 해결 페이지", page5));

//     QWidget *page6 = new QWidget();
//     QVBoxLayout *layout6 = new QVBoxLayout(page6);
//     layout6->addWidget(new QLabel("종합 민원 페이지", page6));

//     // 스택 위젯에 페이지 추가
//     stackedWidget->addWidget(page1);
//     stackedWidget->addWidget(page2);
//     stackedWidget->addWidget(page3);
//     stackedWidget->addWidget(page4);
//     stackedWidget->addWidget(page5);
//     stackedWidget->addWidget(page6);

//     // ui 파일의 stackedWidget에 추가
//     ui->main_stacked_widget->addWidget(stackedWidget);
// }

// // 소멸자 구현 추가
// MainUser::~MainUser()
// {
//     delete ui;
//     // stackedWidget은 부모 위젯이 삭제될 때 자동으로 삭제되므로
//     // 여기서 명시적으로 삭제할 필요 없음
// }


// MainUser.cpp
#include "Mainuser.h"
#include "ui_main_user.h"
#include <QVBoxLayout>
#include <QLabel>

MainUser::MainUser(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainUser)
{
    ui->setupUi(this);

    // main_stacked_widget.ui 로드
    QFile stackedFile("main_stacked_widget.ui");
    stackedFile.open(QFile::ReadOnly);

    QUiLoader loader;
    QWidget *stackedContainer = loader.load(&stackedFile, this);
    stackedFile.close();

    // stackedWidget 찾기
    stackedWidget = stackedContainer->findChild<QStackedWidget*>("stackedWidget");

    // main_user.ui의 특정 영역에 stackedWidget 추가
    // 'frame_container'를 실제 위젯을 넣고 싶은 컨테이너 이름으로 변경하세요
    QWidget *container = findChild<QWidget*>("frame_container");
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->addWidget(stackedWidget);
}

MainUser::~MainUser()
{
    delete ui;
}

// 슬롯 함수 구현
void MainUser::on_pushButton_clicked()
{
    stackedWidget->setCurrentIndex(0); // 첫 번째 위젯 표시
}

void MainUser::on_pushButton_2_clicked()
{
    stackedWidget->setCurrentIndex(1); // 두 번째 위젯 표시
}

void MainUser::on_pushButton_3_clicked()
{
    stackedWidget->setCurrentIndex(2); // 세 번째 위젯 표시
}

void MainUser::on_pushButton_4_clicked()
{
    stackedWidget->setCurrentIndex(3); // 네 번째 위젯 표시
}

void MainUser::on_pushButton_5_clicked()
{
    stackedWidget->setCurrentIndex(4); // 다섯 번째 위젯 표시
}

void MainUser::on_pushButton_6_clicked()
{
    stackedWidget->setCurrentIndex(5); // 여섯 번째 위젯 표시
}

