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
    emit new_grammar(formal_device::grammar::Regular());
    this->close();
}

void NewGrammarDialog::on_m_cancel_btn_clicked()
{
    this->close();
}
