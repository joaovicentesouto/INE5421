#include "NewGrammarDialog.hpp"
#include "ui_NewGrammarDialog.h"

NewGrammarDialog::NewGrammarDialog(unsigned number, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGrammarDialog),
    m_number(number)
{
    ui->setupUi(this);
}

NewGrammarDialog::~NewGrammarDialog()
{
    delete ui;
}

void NewGrammarDialog::on_m_ok_btn_clicked()
{
    try
    {
        grammar_type regular = formal_device::parser::make_regular_grammar(ui->m_text->toPlainText().toStdString());
        emit new_grammar(m_number, regular);
        this->close();
    }
    catch (std::out_of_range error)
    {
        ui->m_error->setText(QString::fromStdString(error.what()));
    }
}

void NewGrammarDialog::on_m_cancel_btn_clicked()
{
    this->close();
}
