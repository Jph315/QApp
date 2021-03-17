#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMessageBox>
#include <QPainter>
#include <QStyleOption>
#include "loginui.h"
#include "ui_loginui.h"
#include "network/tcpclient.h"
#include <QDebug>

LoginUi::LoginUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginUi)
{
    ui->setupUi(this);
    TcpClient::instance().addNetData(this);
}

LoginUi::~LoginUi()
{
    TcpClient::instance().removeNetData(this);
    delete ui;
}

void LoginUi::connectStatus(bool bStatus)
{

}

void LoginUi::processNetData(const QByteArray &recvData)
{
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(recvData, &error);
    if(error.error == QJsonParseError::NoError)
    {
        QJsonObject jsonObj = document.object();
        if(jsonObj.contains("NetDataType"))
        {
            QJsonValue value = jsonObj.value("NetDataType");
            NetDataType type = static_cast<NetDataType>(value.toInt());
            if(AccountLogin == type)
            {
                if(jsonObj.contains("Content"))
                {
                    QJsonObject contentObj = jsonObj.value("Content").toObject();
                    if(contentObj.contains("Result"))
                    {
                        int retValue = contentObj.value("Result").toInt();
                        qDebug() << "retValue: " << retValue;
                        if(6 == retValue)
                        {
                            emit login();

                        }else
                        {
                            QMessageBox::information(this, tr("登录失败"), tr("账户或密码错误"));
                        }
                    }
                }
            }
        }
    }
}

void LoginUi::clearInput()
{
    ui->edit_account->clear();
    ui->edit_password->clear();
    ui->check_remember->setChecked(false);
}

void LoginUi::paintEvent(QPaintEvent *event)
{
    QStyleOption op;
    op.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &op, &p, this);
}

void LoginUi::on_btn_login_clicked()
{
    QString account = ui->edit_account->text();
    QString password = ui->edit_password->text();
    if(account.isEmpty() || password.isEmpty())
    {
        QMessageBox::information(this, tr("登录"), tr("用户名或密码不能为空"));

    }else
    {
        TcpClient::instance().login(account, password);
    }
}
