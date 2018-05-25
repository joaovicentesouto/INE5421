#include "NewExpressionDialog.hpp"
#include "ui_NewExpressionDialog.h"

NewExpressionDialog::NewExpressionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewExpressionDialog)
{
    ui->setupUi(this);
}

NewExpressionDialog::~NewExpressionDialog()
{
    delete ui;
}

void NewExpressionDialog::on_m_ok_btn_clicked()
{
    try
    {
        expression_type_ptr exp = formal_device::parser::make_regular_expression(ui->m_text->text().toStdString());
        emit new_expression(exp);
        this->close();
    }
    catch (std::out_of_range)
    {
        ui->m_error->setText("Invalido");
    }
}

void NewExpressionDialog::on_m_cancel_btn_clicked()
{
    this->close();
}
