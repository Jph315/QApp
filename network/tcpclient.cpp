#include <QThread>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include "tcpclient.h"
#include <QThread>
#include <QTimer>
#include "tcpsocket.h"
#include "data/net/inetdata.h"

TcpClient::TcpClient(QObject *parent)
    : QObject(parent),
      bConn(false),
      bLogin(false)
{
    init();
}

TcpClient::~TcpClient()
{
    if(thread->isRunning())
    {
        thread->quit();
    }
}

TcpClient &TcpClient::instance()
{
    static TcpClient obj;
    return obj;
}

void TcpClient::addNetData(INetData *netData)
{
    netDatas.insert(netData);
}

void TcpClient::removeNetData(INetData *netData)
{
    netDatas.remove(netData);
}

void TcpClient::connectToHost(const QString &ip, quint16 port)
{
    if(!bConn)
    {
        emit connectToServer(ip, port);
    }
}

void TcpClient::registerAccount(const QString &account, const QString &password)
{
    if(bConn)
    {
        QJsonObject rootObj;
        QJsonObject contentObj;
        contentObj.insert("Account", account);
        contentObj.insert("Password", password);
        rootObj.insert("NetDataType", 1001);
        rootObj.insert("Content", contentObj);
        QJsonDocument document(rootObj);
        emit dataToSend(document.toJson());
    }
}

void TcpClient::login(const QString &account, const QString &password)
{
    if(bConn)
    {
        QJsonObject rootObj;
        QJsonObject contentObj;
        contentObj.insert("Account", account);
        contentObj.insert("Password", password);
        rootObj.insert("NetDataType", 1002);
        rootObj.insert("Content", contentObj);
        QJsonDocument document(rootObj);
        emit dataToSend(document.toJson());
    }
}

void TcpClient::init()
{
    timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &TcpClient::onTimeout);
    timer->start(5*1000);

    thread = new QThread;
    socket = new TcpSocket;
    connect(thread, &QThread::started, socket, &TcpSocket::initSocket);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(thread, &QThread::finished, socket, &TcpSocket::deleteLater);
    connect(socket, &TcpSocket::connected, this, &TcpClient::onConnected, Qt::QueuedConnection);
    connect(socket, &TcpSocket::disconnected, this, &TcpClient::onDisconnected, Qt::QueuedConnection);
    connect(socket, &TcpSocket::recvData, this, &TcpClient::onRecvData, Qt::QueuedConnection);
    connect(this, &TcpClient::connectToServer, socket, &TcpSocket::connectToServer, Qt::QueuedConnection);
    connect(this, &TcpClient::dataToSend, socket, &TcpSocket::sendData, Qt::QueuedConnection);
    socket->moveToThread(thread);
    thread->start();
}

void TcpClient::onConnected()
{
    bConn = true;
    QList<INetData*> temp = netDatas.values();
    for(int i = 0; i != temp.size(); ++i)
    {
        temp.at(i)->connectStatus(true);
    }
    if(timer->isActive())
    {
        timer->stop();
    }
}

void TcpClient::onDisconnected()
{
    bConn = false;
    bLogin = false;
    QList<INetData*> temp = netDatas.values();
    for(int i = 0; i != temp.size(); ++i)
    {
        temp.at(i)->connectStatus(false);
    }
    if(timer->isActive())
    {
        timer->stop();
    }
    timer->start(5*1000);
}

void TcpClient::onRecvData(QByteArray data)
{
    QList<INetData*> temp = netDatas.values();
    for(int i = 0; i != temp.size(); ++i)
    {
        temp.at(i)->processNetData(data);
    }
}

void TcpClient::onTimeout()
{
    connectToHost(ip, port);
}
