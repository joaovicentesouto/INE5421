#include "NewGrammarDialog.hpp"
#include "ui_NewGrammarDialog.h"

NewGrammarDialog::NewGrammarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGrammarDialog)
{
    ui->setupUi(this);
}

NewGrammarDialog::~NewGrammarDialog()
{
    delete ui;
}

void NewGrammarDialog::on_m_ok_btn_clicked()
{
    std::string grammar_str = ui->m_text->toPlainText().toStdString();
    auto grammar = formal_device::grammar::parser::make_regular_grammar(grammar_str);
    emit new_grammar(grammar);
    this->close();
}

void NewGrammarDialog::on_m_cancel_btn_clicked()
{
    this->close();
}
