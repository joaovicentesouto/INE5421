#include "StaticGrammarWidget.hpp"
#include "ui_StaticGrammarWidget.h"

StaticGrammarWidget::StaticGrammarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaticGrammarWidget)
{
    ui->setupUi(this);
}

StaticGrammarWidget::~StaticGrammarWidget()
{
    delete ui;
}
