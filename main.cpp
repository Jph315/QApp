#include <QApplication>
#include <QFile>
#include "../ui/mainui.h"
#include "network/tcpclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //设置样式
    QFile file("Style/app.qss");
    if(file.open(QFile::ReadOnly))
    {
        QString qss = file.readAll();
        qApp->setStyleSheet(qss);
    }

    //创建主界面
    MainUi mainUi;
    mainUi.showMaximized();

    //连接服务器
//    TcpClient::instance().connectToHost("115.29.168.74", 2021);
    TcpClient::instance().connectToHost("127.0.0.1", 2021);

    return a.exec();
}
