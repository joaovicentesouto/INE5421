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
    emit set_dynamic_grammar(ui->grammar->toPlainText());
    ui->grammar->clear();
}

void StaticGrammarWidget::set_grammar(std::string grammar)
{
    ui->grammar->setText(QString::fromStdString(grammar));
}
