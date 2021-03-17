#ifndef MAINUI_H
#define MAINUI_H

#include <QWidget>

namespace Ui {
class MainUi;
}

class WelcomeUi;
class ToolUi;
class MainUi : public QWidget
{
    Q_OBJECT

public:
    explicit MainUi(QWidget *parent = nullptr);
    ~MainUi() override;

protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

private:
    void init();

public slots:

private slots:
    void on_widget_title_doubleclicked();
    void on_btn_min_clicked();
    void on_btn_max_clicked();
    void on_btn_close_clicked();

private:
    Ui::MainUi *ui;
    WelcomeUi *welcomeUi;
    ToolUi *toolUi;
};

#endif // MAINUI_H
