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
