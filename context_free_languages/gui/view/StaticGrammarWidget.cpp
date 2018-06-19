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
    emit select_grammar(m_grammar_name);
    ui->grammar->clear();
    ui->grammarData->clear();
    m_grammar_name = "";
}

void StaticGrammarWidget::set_grammar(std::string grammar, std::string grammar_name)
{
    ui->grammar->setText(QString::fromStdString(grammar));
    m_grammar_name = grammar_name;
}

void StaticGrammarWidget::set_grammar_data(std::string data)
{
    ui->grammarData->setText(QString::fromStdString(data));
}
