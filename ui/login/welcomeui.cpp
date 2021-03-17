#include <QStyleOption>
#include <QPainter>
#include "welcomeui.h"
#include "ui_welcomeui.h"
#include "loginui.h"
#include "registerui.h"

WelcomeUi::WelcomeUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeUi)
{
    ui->setupUi(this);
    init();
}

WelcomeUi::~WelcomeUi()
{
    delete loginUi;
    delete  registerUi;
    delete ui;
}

void WelcomeUi::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QStyleOption op;
    op.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &op, &p, this);
}

void WelcomeUi::init()
{
    loginUi = new LoginUi;
    registerUi = new RegisterUi;
    connect(loginUi, &LoginUi::login, [&](){ emit login(); });
    connect(registerUi, &RegisterUi::registerSucceede, [&]()->void{ ui->tabWidget->setCurrentIndex(0); loginUi->clearInput(); });
    ui->tabWidget->addTab(loginUi, "登录");
    ui->tabWidget->addTab(registerUi, "注册");
    ui->tabWidget->setCurrentIndex(0);
}
