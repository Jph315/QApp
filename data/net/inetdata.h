#ifndef INETDATA_H
#define INETDATA_H

#include <QByteArray>

enum NetDataType
{
    RegisterAccount = 1001, //注册账户
    AccountLogin = 1002, //用户登录
    AccountLogout = 1003
};

class INetData
{
public:
    INetData();
    virtual ~INetData();

public:
    virtual void connectStatus(bool bStatus) = 0;
    virtual void processNetData(const QByteArray &recvData) = 0;
};

#endif // INETDATA_H
