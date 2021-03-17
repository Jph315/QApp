#include "toolui.h"
#include "ui_toolui.h"

ToolUi::ToolUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolUi)
{
    ui->setupUi(this);
}

ToolUi::~ToolUi()
{
    delete ui;
}
