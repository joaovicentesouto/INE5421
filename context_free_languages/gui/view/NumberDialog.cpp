#include "NumberDialog.hpp"
#include "ui_NumberDialog.h"

NumberDialog::NumberDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NumberDialog)
{
    ui->setupUi(this);
    ui->numberBox->setMinimum(1);
}

NumberDialog::~NumberDialog()
{
    delete ui;
}

void NumberDialog::on_cancelButton_clicked()
{
    close();
}

void NumberDialog::on_confirmButton_clicked()
{
    if (emit factoring(ui->numberBox->text().toUInt()))
        emit set_msg_text("Grammar factored with successfully!");
    else
        emit set_msg_text("Grammar factoring with no success!");
    close();
}
