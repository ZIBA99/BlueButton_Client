#include "SocketController.h"
#include <QDebug>
#include <QDataStream>

SocketController::SocketController(QObject *parent)
    : QObject(parent)
    , m_socket(new QTcpSocket(this))
    , m_timeoutTimer(new QTimer(this))
    , m_reconnectTimer(new QTimer(this))
    , m_port(0)
    , m_autoReconnect(false)
    , m_reconnectInterval(5000)
    , m_timeout(30000)
    , m_useHostName(true)
{
    setupConnections();

    m_timeoutTimer->setSingleShot(true);
    m_reconnectTimer->setSingleShot(true);
}

SocketController::~SocketController()
{
    if (m_socket->state() != QAbstractSocket::UnconnectedState) {
        m_socket->disconnectFromHost();
        if (m_socket->state() != QAbstractSocket::UnconnectedState) {
            m_socket->waitForDisconnected(3000);
        }
    }
}

void SocketController::setupConnections()
{
    connect(m_socket, &QTcpSocket::connected, this, &SocketController::onConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &SocketController::onDisconnected);
    connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &SocketController::onSocketError);

    connect(m_timeoutTimer, &QTimer::timeout, this, &SocketController::onTimeout);
    connect(m_reconnectTimer, &QTimer::timeout, this, &SocketController::attemptReconnect);
}

void SocketController::connectToHost(const QString &hostName, quint16 port)
{
    m_hostName = hostName;
    m_port = port;
    m_useHostName = true;

    if (m_socket->state() != QAbstractSocket::UnconnectedState) {
        m_socket->abort();
    }

    qDebug() << "Connecting to" << hostName << ":" << port;
    m_socket->connectToHost(hostName, port);

    if (m_timeout > 0) {
        m_timeoutTimer->start(m_timeout);
    }
}

void SocketController::connectToHost(const QHostAddress &address, quint16 port)
{
    m_hostAddress = address;
    m_port = port;
    m_useHostName = false;

    if (m_socket->state() != QAbstractSocket::UnconnectedState) {
        m_socket->abort();
    }

    qDebug() << "Connecting to" << address.toString() << ":" << port;
    m_socket->connectToHost(address, port);

    if (m_timeout > 0) {
        m_timeoutTimer->start(m_timeout);
    }
}

void SocketController::disconnectFromHost()
{
    m_autoReconnect = false;
    m_reconnectTimer->stop();
    m_timeoutTimer->stop();

    if (m_socket->state() != QAbstractSocket::UnconnectedState) {
        m_socket->disconnectFromHost();
    }
}

bool SocketController::sendJsonData(const QJsonObject &jsonObject)
{
    QJsonDocument doc(jsonObject);
    return sendJsonData(doc);
}

bool SocketController::sendJsonData(const QJsonDocument &jsonDocument)
{
    if (!isConnected()) {
        emit errorOccurred("Socket is not connected");
        return false;
    }

    QByteArray jsonData = jsonDocument.toJson(QJsonDocument::Compact);
    QByteArray packet = createJsonPacket(jsonData);

    qint64 bytesWritten = m_socket->write(packet);
    bool success = (bytesWritten == packet.size()) && m_socket->waitForBytesWritten(3000);

    if (success) {
        emit jsonDataSent(jsonDocument.object());
        qDebug() << "JSON data sent:" << jsonData;
    } else {
        emit errorOccurred("Failed to send JSON data");
    }

    return success;
}

bool SocketController::sendJsonString(const QString &jsonString)
{
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        emit errorOccurred(QString("Invalid JSON: %1").arg(parseError.errorString()));
        return false;
    }

    return sendJsonData(doc);
}

bool SocketController::isConnected() const
{
    return m_socket->state() == QAbstractSocket::ConnectedState;
}

QAbstractSocket::SocketState SocketController::socketState() const
{
    return m_socket->state();
}

void SocketController::setAutoReconnect(bool enabled, int intervalMs)
{
    m_autoReconnect = enabled;
    m_reconnectInterval = intervalMs;
}

void SocketController::setTimeout(int timeoutMs)
{
    m_timeout = timeoutMs;
}

QByteArray SocketController::createJsonPacket(const QByteArray &jsonData)
{
    // 패킷 구조: [4바이트 크기][JSON 데이터]
    QByteArray packet;
    QDataStream stream(&packet, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);

    stream << static_cast<quint32>(jsonData.size());
    packet.append(jsonData);

    return packet;
}

void SocketController::onConnected()
{
    m_timeoutTimer->stop();
    m_reconnectTimer->stop();

    qDebug() << "Connected to server";
    emit connected();
}

void SocketController::onDisconnected()
{
    qDebug() << "Disconnected from server";
    emit disconnected();

    if (m_autoReconnect && m_port > 0) {
        qDebug() << "Auto-reconnect enabled, will retry in" << m_reconnectInterval << "ms";
        m_reconnectTimer->start(m_reconnectInterval);
    }
}

void SocketController::onSocketError(QAbstractSocket::SocketError error)
{
    m_timeoutTimer->stop();

    QString errorString = m_socket->errorString();
    qDebug() << "Socket error:" << errorString;
    emit errorOccurred(errorString);

    if (m_autoReconnect && m_port > 0) {
        m_reconnectTimer->start(m_reconnectInterval);
    }
}

void SocketController::onTimeout()
{
    qDebug() << "Connection timeout";
    m_socket->abort();
    emit connectionTimeout();

    if (m_autoReconnect && m_port > 0) {
        m_reconnectTimer->start(m_reconnectInterval);
    }
}

void SocketController::attemptReconnect()
{
    if (m_socket->state() == QAbstractSocket::UnconnectedState) {
        qDebug() << "Attempting to reconnect...";
        if (m_useHostName) {
            connectToHost(m_hostName, m_port);
        } else {
            connectToHost(m_hostAddress, m_port);
        }
    }
}
