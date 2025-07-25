#include "JoinMemberMainWindow.h"



JoinMemberMainWindow::JoinMemberMainWindow(QWidget *parent,ClientSocket* client_socket)
    : QMainWindow(parent)
    , ui(new Ui::JoinMemberMainWindow)
    , m_client(client_socket)
{
    ui->setupUi(this);
    connect(m_client, &ClientSocket::registrationResponse, this, &JoinMemberMainWindow::onRegistrationResponse);

}

JoinMemberMainWindow::~JoinMemberMainWindow()
{
    delete ui;
}

void JoinMemberMainWindow::on_pushButton_register_clicked()
{
    QString strId = ui->lineEdit_id->text();
    QString password = ui->lineEdit_pw->text();
    QString name = ui->lineEdit_name->text();
    QString email = ui->lineEdit_email->text();
    QString address = ui->lineEdit_address->text();
    m_client->registerUser(strId, password, name, email, address);
}

void JoinMemberMainWindow::onRegistrationResponse(bool success, const QJsonObject &userData)
{
    if (success) {
        QString name = userData.value("name").toString();
        qDebug() << QString("✅ 회원가입 성공: %1").arg(name);
        ui->lineEdit_id->clear();
        ui->lineEdit_name->clear();
        ui->lineEdit_pw->clear();
        ui->lineEdit_email->clear();
        ui->lineEdit_address->clear();
        close();
    } else {
        qDebug() << "❌ 회원가입 실패";
    }
}
