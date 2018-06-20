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
    ui->history->clear();
    m_grammar_name = "";
}

void StaticGrammarWidget::set_grammar(std::string grammar, std::string grammar_name, bool first)
{
    if (first)
    {
        ui->history->clear();
        m_name_to_grammar.clear();
        m_name_to_data.clear();
    }

    ui->grammar->setText(QString::fromStdString(grammar));

    m_grammar_name = grammar_name;
    m_result_grammar_name = "Step " + std::to_string(ui->history->count()+1) + ": " + grammar_name;
    m_name_to_grammar[m_result_grammar_name] = grammar;
    m_result_to_original_name[m_result_grammar_name] = grammar_name;

    ui->history->addItem(new QListWidgetItem(QString::fromStdString(m_result_grammar_name)));
}

void StaticGrammarWidget::set_grammar_data(std::string data)
{
    ui->grammarData->setText(QString::fromStdString(data));
    m_name_to_data[m_result_grammar_name] = data;
}

void StaticGrammarWidget::on_history_itemClicked(QListWidgetItem *item)
{
    for (int i = 0; i < ui->history->count(); i++)
        ui->history->item(i)->setBackgroundColor(QColor("#ffffff"));

    item->setBackgroundColor(QColor("#71d773"));
    ui->history->clearSelection();
    m_result_grammar_name = item->text().toStdString();
    m_grammar_name = m_result_to_original_name[m_result_grammar_name];

    ui->grammar->setText(QString::fromStdString(m_name_to_grammar[m_result_grammar_name]));
    ui->grammarData->setText(QString::fromStdString(m_name_to_data[m_result_grammar_name]));
}
