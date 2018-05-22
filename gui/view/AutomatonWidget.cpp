#include "AutomatonWidget.hpp"
#include "ui_AutomatonWidget.h"

AutomatonWidget::AutomatonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutomatonWidget)
{
    ui->setupUi(this);
}

AutomatonWidget::~AutomatonWidget()
{
    delete ui;
}
