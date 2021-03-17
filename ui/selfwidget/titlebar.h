#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QPoint>

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);

signals:
    void doubleClicked();

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    bool bPressed;
    QPoint pressPoint;
};

#endif // TITLEBAR_H
