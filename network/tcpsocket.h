#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QString>
#include <QAbstractSocket>

class QTcpSocket;
class TcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit TcpSocket(QObject *parent = nullptr);
    ~TcpSocket();

private:
    void parseRecvData(QByteArray &_untreatedData, QList<QByteArray> &result);

signals:
    void connected();
    void disconnected();
    void recvData(QByteArray);
    void finished();

public slots:
    void initSocket();
    void connectToServer(QString ip, quint16 port);
    void sendData(QByteArray replyData);

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onSocketError(QAbstractSocket::SocketError error);

private:
    QTcpSocket *socket;
    QByteArray untreatedData;
};

#endif // TCPSOCKET_H
