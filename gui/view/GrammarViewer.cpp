#include "GrammarViewer.hpp"
#include "ui_GrammarViewer.h"

GrammarViewer::GrammarViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GrammarViewer)
{
    ui->setupUi(this);
}

GrammarViewer::~GrammarViewer()
{
    delete ui;
}
