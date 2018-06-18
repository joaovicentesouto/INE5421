#include "StaticGrammarWidget.hpp"
#include "ui_StaticGrammarWidget.h"

StaticGrammarWidget::StaticGrammarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaticGrammarWidget)
{
    ui->setupUi(this);
    ui->grammar->setReadOnly(true);
}

StaticGrammarWidget::~StaticGrammarWidget()
{
    delete ui;
}

void StaticGrammarWidget::on_updateButton_clicked()
{
//    emit update_grammaer(ui->grammar->)
}
