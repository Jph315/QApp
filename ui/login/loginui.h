#ifndef LOGINUI_H
#define LOGINUI_H

#include <QWidget>
#include <QJsonValue>
#include "./data/net/inetdata.h"

namespace Ui {
class LoginUi;
}

class LoginUi : public QWidget, public INetData
{
    Q_OBJECT

public:
    explicit LoginUi(QWidget *parent = nullptr);
    ~LoginUi() override;

public:
    virtual void connectStatus(bool bStatus) override;
    virtual void processNetData(const QByteArray &recvData) override;

    void clearInput();

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void processRegisterNetData(const QJsonValue &value);
    void processLoginNetData(const QJsonValue &value);

signals:
    void login();

private slots:
    void on_btn_login_clicked();

private:
    Ui::LoginUi *ui;
};

#endif // LOGINUI_H
