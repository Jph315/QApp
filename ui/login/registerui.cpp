#include <QPainter>
#include <QStyleOption>
#include <QDateTime>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonParseError>
#include "registerui.h"
#include "ui_registerui.h"
#include "./network/tcpclient.h"

RegisterUi::RegisterUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterUi)
{
    ui->setupUi(this);
    on_btn_code_clicked();
    TcpClient::instance().addNetData(this);
}

RegisterUi::~RegisterUi()
{
    TcpClient::instance().removeNetData(this);
    delete ui;
}

void RegisterUi::connectStatus(bool bStatus)
{
    Q_UNUSED(bStatus)
}

void RegisterUi::processNetData(const QByteArray &recvData)
{
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(recvData, &error);
    if(error.error == QJsonParseError::NoError)
    {
        QJsonObject rootObj = document.object();
        if(rootObj.contains("NetDataType"))
        {
            QJsonValue netDataTypeValue = rootObj.value("NetDataType");
            NetDataType type = static_cast<NetDataType>(netDataTypeValue.toInt());
            if(RegisterAccount == type)
            {
                if(rootObj.contains("Content"))
                {
                    QJsonObject contentObj = rootObj.value("Content").toObject();
                    if(contentObj.contains("Result"))
                    {
                        int result = contentObj.value("Result").toInt();
                        if(4 == result)
                        {
                            QMessageBox::information(this, tr("工具"), tr("注册成功"));
                            emit registerSucceede();

                        }else if(1 == result)
                        {
                            QMessageBox::information(this, tr("工具"), tr("账户已存在"));

                        }else
                        {
                            QMessageBox::information(this, tr("工具"), tr("注册失败"));
                        }
                    }
                }
            }
        }
    }
}

void RegisterUi::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QStyleOption op;
    op.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &op, &p, this);
}

void RegisterUi::on_btn_register_clicked()
{
    QString account = ui->edit_account->text();
    QString password = ui->edit_password->text();
    if(account.isEmpty() || password.isEmpty())
    {
        QMessageBox::information(this, tr("工具"), "账户和密码不能为空");

    }else
    {
        QString code = ui->edit_code->text();
        if(code.compare(ui->btn_code->text()))
        {
            QMessageBox::information(this, tr("工具"), tr("验证码错误"));

        }else
        {
            TcpClient::instance().registerAccount(account, password);
        }
    }
}

void RegisterUi::on_btn_code_clicked()
{
    QString code;
    for(int i = 0; i < 4; ++i)
    {
        code.append(QString::number(QRandomGenerator::global()->generate64() % 10));
    }
    ui->btn_code->setText(code);
}
