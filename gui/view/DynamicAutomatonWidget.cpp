#include "DynamicAutomatonWidget.hpp"
#include "ui_DynamicAutomatonWidget.h"

DynamicAutomatonWidget::DynamicAutomatonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DynamicAutomatonWidget)
{
    ui->setupUi(this);
}

DynamicAutomatonWidget::~DynamicAutomatonWidget()
{
    delete ui;
}

void DynamicAutomatonWidget::name(QString name)
{
    ui->m_name_machine->setText(name);
}

void DynamicAutomatonWidget::on_m_new_grammar_btn_clicked()
{
    NewGrammarDialog dialog(this);

    QObject::connect(&dialog, SIGNAL(new_grammar(formal_device::grammar::Regular*)),
                        this, SLOT  (new_grammar(formal_device::grammar::Regular*)));
    dialog.exec();
}

void DynamicAutomatonWidget::new_grammar(formal_device::grammar::Regular new_grammar)
{

}

void DynamicAutomatonWidget::new_expression(QString new_expression)
{

}
