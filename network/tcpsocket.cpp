#include "tcpsocket.h"
#include <QTcpSocket>
#include <QDebug>
#include <QRegExp>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

TcpSocket::TcpSocket(QObject *parent)
    : QObject(parent),
      socket(nullptr),
      untreatedData(QByteArray())
{
    initSocket();
}

TcpSocket::~TcpSocket()
{
    if(socket != nullptr)
    {
        delete socket;
        socket = nullptr;
    }
}

void TcpSocket::connectToServer(QString ip, quint16 port)
{
    socket->connectToHost(ip, port);
}

void TcpSocket::sendData(QByteArray replyData)
{
    if(socket != nullptr)
    {
        socket->write(replyData);
    }
}

void TcpSocket::onConnected()
{
    emit connected();
}

void TcpSocket::onDisconnected()
{
    emit disconnected();
    emit finished();
}

void TcpSocket::onReadyRead()
{
    if(socket != nullptr)
    {
        while(socket->bytesAvailable() > 0)
        {
            QByteArray data;
            qint64 size = socket->bytesAvailable();
            data.resize(static_cast<int>(size));
            socket->read(data.data(), size);
            untreatedData += data;
            QList<QByteArray> results;
            parseRecvData(untreatedData, results);
            for(int i = 0; i != results.size(); ++i)
            {
                emit recvData(data);
            }
        }
    }
}

void TcpSocket::onSocketError(QAbstractSocket::SocketError error)
{
    qDebug() << "error: " << error << "---error string: " << socket->errorString();
}

void TcpSocket::parseRecvData(QByteArray &_untreatedData, QList<QByteArray> &results)
{
    QString untreatedDataStr = QString(_untreatedData);
    QString temp = untreatedDataStr;
    QString result;

    int leftCount = 0, rightCount = 0;
    for(int i = 0; i != untreatedDataStr.size(); ++i)
    {
        result.push_back(untreatedDataStr.at(i));
        temp.remove(untreatedDataStr.at(i));
        if(untreatedDataStr.at(i) == '{')
        {
            ++leftCount;
        }
        if(untreatedDataStr.at(i) == '}')
        {
            ++rightCount;
        }
        if(leftCount == rightCount)
        {
            QJsonDocument document = QJsonDocument::fromRawData(result.toLocal8Bit().data(), result.size());
            results.push_back(document.toJson());
            _untreatedData = temp.toLocal8Bit();
            break;
        }
    }

    if((leftCount == rightCount) && (leftCount > 0) && (rightCount > 0))
    {
        parseRecvData(_untreatedData, results);
    }
}

void TcpSocket::initSocket()
{
    socket = new QTcpSocket;
    connect(socket, &QTcpSocket::connected, this, &TcpSocket::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &TcpSocket::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &TcpSocket::onReadyRead);
    qRegisterMetaType<QAbstractSocket::SocketError>();
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &TcpSocket::onSocketError);
}
