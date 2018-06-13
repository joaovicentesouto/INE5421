#include "GrammarViewer.hpp"
#include "ui_GrammarViewer.h"

GrammarViewer::GrammarViewer(grammar_type grammar, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GrammarViewer),
    m_grammar(grammar)
{
    ui->setupUi(this);

    QString text = QString::fromStdString(m_grammar.to_string());

    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(text);
    ui->plainTextEdit->setReadOnly(true);
}

GrammarViewer::GrammarViewer(sentences_set sentences, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GrammarViewer)
{
    ui->setupUi(this);

    QString text;
    for (auto string : sentences)
        text += QString::fromStdString(string) + "\n";

    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(text);
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
