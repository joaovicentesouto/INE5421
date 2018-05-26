#include "GrammarViewer.hpp"
#include "ui_GrammarViewer.h"

GrammarViewer::GrammarViewer(grammar_type grammar, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GrammarViewer),
    m_grammar(grammar)
{
    ui->setupUi(this);
    ui->plainTextEdit->clear();
    QString text = QString::fromStdString(m_grammar.to_string());
    ui->plainTextEdit->insertPlainText(text);

    //ui->plainTextEdit->setEnabled(false);
    ui->plainTextEdit->setReadOnly(true);
}

GrammarViewer::~GrammarViewer()
{
    delete ui;
}

void GrammarViewer::on_pushButton_clicked()
{
    this->close();
}
