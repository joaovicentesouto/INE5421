#include "DynamicGrammarWidget.hpp"
#include "ui_DynamicGrammarWidget.h"

DynamicGrammarWidget::DynamicGrammarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DynamicGrammarWidget)
{
    ui->setupUi(this);
}

DynamicGrammarWidget::~DynamicGrammarWidget()
{
    delete ui;
}
