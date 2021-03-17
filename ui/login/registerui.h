#ifndef REGISTERUI_H
#define REGISTERUI_H

#include <QWidget>
#include "data/net/inetdata.h"

namespace Ui {
class RegisterUi;
}

class RegisterUi : public QWidget, public INetData
{
    Q_OBJECT

public:
    explicit RegisterUi(QWidget *parent = nullptr);
    ~RegisterUi() override;

public:
    virtual void connectStatus(bool bStatus) override;
    virtual void processNetData(const QByteArray &recvData) override;

protected:
    virtual void paintEvent(QPaintEvent *event) override;

signals:
    void registerSucceede();

private slots:
    void on_btn_register_clicked();
    void on_btn_code_clicked();

private:
    Ui::RegisterUi *ui;
};

#endif // REGISTERUI_H
