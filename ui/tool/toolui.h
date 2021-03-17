#ifndef TOOLUI_H
#define TOOLUI_H

#include <QWidget>

namespace Ui {
class ToolUi;
}

class ToolUi : public QWidget
{
    Q_OBJECT

public:
    explicit ToolUi(QWidget *parent = nullptr);
    ~ToolUi();

private:
    Ui::ToolUi *ui;
};

#endif // TOOLUI_H
