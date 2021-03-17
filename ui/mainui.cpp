#include <QDebug>
#include "mainui.h"
#include "ui_mainui.h"
#include "login/welcomeui.h"
#include "tool/toolui.h"
#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <windowsx.h>
#endif
MainUi::MainUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainUi)
{
    ui->setupUi(this);
    init();
}

MainUi::~MainUi()
{
    delete welcomeUi;
    delete toolUi;
    delete ui;
}

bool MainUi::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    MSG *param = static_cast<MSG*>(message);
    switch(param->message)
    {
    case WM_NCHITTEST:
        int x = GET_X_LPARAM(param->lParam) - this->frameGeometry().x();
        int y = GET_Y_LPARAM(param->lParam) - this->frameGeometry().y();

        *result = HTCAPTION;

        //左
        if(x > 0 && x < 5)
        {
            *result = HTLEFT;
        }
        //右
        if(x > (this->width()-5) && x < (this->width()-0))
        {
            *result = HTRIGHT;
        }
        //上
        if((y > 0) && (y < 5))
        {
            *result = HTTOP;
        }
        //下
        if((y > this->height()-5) && (y < this->height()-0))
        {
            *result = HTBOTTOM;
        }
        //上左
        if((x > 0) && (x < 5) && (y > 0) && (y < 5))
        {
            *result = HTTOPLEFT;
        }
        //上右
        if((x > this->width()-5) && (x < this->width()-0) && (y > 0) && (y < 5))
        {
            *result = HTTOPRIGHT;
        }
        //下左
        if((x > 0) && (x < 5) && (y > this->height()-5) && (y < this->height()-0))
        {
            *result = HTBOTTOMLEFT;
        }
        //下右
        if((x > this->width()-5) && (x < this->width()-0) && (y > this->height()-5) && (y < this->height()-0))
        {
            *result = HTBOTTOMRIGHT;
        }
        if(*result == HTCAPTION)
        {
            return false;
        }
        return true;
    }
    return false;
}

void MainUi::init()
{
    setWindowTitle("Tools");
    setWindowIcon(QIcon("picture/icon.png"));
    ui->label_title->setText("Tools");
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    connect(ui->widget_title, &TitleBar::doubleClicked, this, &MainUi::on_widget_title_doubleclicked);
    ui->label_icon->setPixmap(QPixmap("picture/icon.png"));
    ui->btn_setting->setIcon(QIcon("picture/menu.png"));
    ui->btn_setting->setIconSize(QSize(25,25));
    ui->btn_min->setIcon(QIcon("picture/min.png"));
    ui->btn_min->setIconSize(QSize(25,25));
    ui->btn_max->setIcon(QIcon("picture/max_false.png"));
    ui->btn_max->setIconSize(QSize(25,25));
    ui->btn_close->setIcon(QIcon("picture/close.png"));
    ui->btn_close->setIconSize(QSize(25,25));

    welcomeUi = new WelcomeUi;
    toolUi = new ToolUi;
    ui->stackedWidget->addWidget(welcomeUi);
    ui->stackedWidget->addWidget(toolUi);
    ui->stackedWidget->setCurrentWidget(welcomeUi);

    connect(welcomeUi, &WelcomeUi::login, [&]()->void{ ui->stackedWidget->setCurrentWidget(toolUi); });
}

void MainUi::on_widget_title_doubleclicked()
{
    on_btn_max_clicked();
}

void MainUi::on_btn_min_clicked()
{
    showMinimized();
}

void MainUi::on_btn_max_clicked()
{
    if(isMaximized())
    {
        showNormal();
        ui->btn_max->setIcon(QIcon("picture/max_false.png"));

    }else
    {
        showMaximized();
        ui->btn_max->setIcon(QIcon("picture/max_true.png"));
    }
}

void MainUi::on_btn_close_clicked()
{
    close();
}
