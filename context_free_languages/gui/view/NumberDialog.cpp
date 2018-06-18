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
    emit factoring(ui->numberBox->text().toUInt());
    emit set_msg_text("Tentativa de Fatoraçao em " + ui->numberBox->text() + " Passos Realizada!");
    close();
}
