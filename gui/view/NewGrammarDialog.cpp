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
