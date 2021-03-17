#include <QMouseEvent>
#include <QStyleOption>
#include <QPainter>
#include "titlebar.h"

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent),
      bPressed(false)
{

}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        bPressed = true;
        pressPoint = event->globalPos();
    }
    QWidget::mousePressEvent(event);
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        bPressed = false;
    }
    QWidget::mouseReleaseEvent(event);
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit doubleClicked();
    QWidget::mouseDoubleClickEvent(event);
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(bPressed)
    {
        QWidget *parent = parentWidget();
        if(parent != nullptr)
        {
            QPoint movePoint = event->globalPos();
            QPoint parentPoint = parent->pos();
            parent->move(parentPoint.x()+movePoint.x()-pressPoint.x(), parentPoint.y()+movePoint.y()-pressPoint.y());
            pressPoint = movePoint;
        }
    }
    QWidget::mouseMoveEvent(event);
}

void TitleBar::paintEvent(QPaintEvent *event)
{
    QStyleOption op;
    QPainter painter(this);
    op.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &op, &painter, this);
}
