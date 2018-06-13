#include "BooleanDialog.hpp"
#include "ui_BooleanDialog.h"

BooleanDialog::BooleanDialog(QString answer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BooleanDialog)
{
    ui->setupUi(this);
    ui->m_answer->setText(answer);
}

BooleanDialog::~BooleanDialog()
{
    delete ui;
}

void BooleanDialog::on_m_close_clicked()
{
    this->close();
}
