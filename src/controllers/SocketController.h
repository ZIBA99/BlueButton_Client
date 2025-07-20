#ifndef SOCKETCONTROLLER_H
#define SOCKETCONTROLLER_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTimer>
#include <QHostAddress>

class SocketController : public QObject
{
    Q_OBJECT

public:
    explicit SocketController(QObject *parent = nullptr);
    ~SocketController();

    // 연결 관련 메서드
    void connectToHost(const QString &hostName, quint16 port);
    void connectToHost(const QHostAddress &address, quint16 port);
    void disconnectFromHost();

    // JSON 전송 메서드
    bool sendJsonData(const QJsonObject &jsonObject);
    bool sendJsonData(const QJsonDocument &jsonDocument);
    bool sendJsonString(const QString &jsonString);

    // 상태 확인
    bool isConnected() const;
    QAbstractSocket::SocketState socketState() const;

    // 설정
    void setAutoReconnect(bool enabled, int intervalMs = 5000);
    void setTimeout(int timeoutMs);

signals:
    void connected();
    void disconnected();
    void jsonDataSent(const QJsonObject &data);
    void errorOccurred(const QString &errorString);
    void connectionTimeout();

private slots:
    void onConnected();
    void onDisconnected();
    void onSocketError(QAbstractSocket::SocketError error);
    void onTimeout();
    void attemptReconnect();

private:
    QTcpSocket *m_socket;
    QTimer *m_timeoutTimer;
    QTimer *m_reconnectTimer;

    QString m_hostName;
    QHostAddress m_hostAddress;
    quint16 m_port;
    bool m_autoReconnect;
    int m_reconnectInterval;
    int m_timeout;
    bool m_useHostName;

    void setupConnections();
    QByteArray createJsonPacket(const QByteArray &jsonData);
};

#endif // SOCKETCONTROLLER_H
