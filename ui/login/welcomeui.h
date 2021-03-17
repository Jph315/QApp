#ifndef WELCOMEUI_H
#define WELCOMEUI_H

#include <QWidget>

namespace Ui {
class WelcomeUi;
}
class LoginUi;
class RegisterUi;
class WelcomeUi : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeUi(QWidget *parent = nullptr);
    ~WelcomeUi() override;

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void init();

signals:
    void login();

private:
    Ui::WelcomeUi *ui;
    LoginUi *loginUi;
    RegisterUi *registerUi;
};

#endif // WELCOMEUI_H
