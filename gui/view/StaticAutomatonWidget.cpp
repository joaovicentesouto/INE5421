#include "StaticAutomatonWidget.hpp"
#include "ui_StaticAutomatonWidget.h"

StaticAutomatonWidget::StaticAutomatonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaticAutomatonWidget)
{
    ui->setupUi(this);
}

StaticAutomatonWidget::~StaticAutomatonWidget()
{
    delete ui;
}
