#ifndef MAINUSER_H
#define MAINUSER_H

#include <QMainWindow>
#include <QStackedWidget> // 이 헤더 추가
#include <QVBoxLayout>
#include <QFile>
#include <QUiLoader>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainUser;//mainuser.ui 이름이랑 일치
}
QT_END_NAMESPACE

class MainUser : public QMainWindow
{
    Q_OBJECT

public:
    MainUser(QWidget *parent = nullptr);
    ~MainUser();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainUser *ui;
    QStackedWidget *stackedWidget; // 이 부분 추가
};
#endif // MAINUSER_H
