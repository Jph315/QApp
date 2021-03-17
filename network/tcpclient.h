#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QSet>

class QThread;
class QTimer;
class TcpSocket;
class INetData;
class TcpClient : public QObject
{
    Q_OBJECT
private:
    explicit TcpClient(QObject *parent = nullptr);
    TcpClient(const TcpClient&) = delete;
    TcpClient &operator=(const TcpClient&) = delete;

public:
    ~TcpClient() override;

public:
    static TcpClient &instance();
    void addNetData(INetData *netData);
    void removeNetData(INetData *netData);
    void connectToHost(const QString &ip, quint16 port);
    void registerAccount(const QString &account, const QString &password);
    void login(const QString &account, const QString &password);

private:
    void init();

signals:
    void dataToSend(QByteArray data);
    void connectToServer(QString ip, quint16 port);

private slots:
    void onConnected();
    void onDisconnected();
    void onRecvData(QByteArray data);
    void onTimeout();

private:
    QThread *thread;
    TcpSocket *socket;
    QTimer *timer;
    QSet<INetData*> netDatas;
    bool bConn;
    bool bLogin;
};

#endif // TCPCLIENT_H
