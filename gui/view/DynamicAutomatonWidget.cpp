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

    QObject::connect(&dialog, SIGNAL(new_grammar(QString)),
                        this, SLOT  (new_grammar(QString)));
    dialog.exec();
}

void DynamicAutomatonWidget::new_grammar(QString new_grammar)
{

}

void DynamicAutomatonWidget::new_automaton(QString new_automaton)
{

}

void DynamicAutomatonWidget::new_expression(QString new_expression)
{

}

void DynamicAutomatonWidget::on_m_new_machine_btn_clicked()
{
    NewAutomatonDialog dialog(this);

    QObject::connect(&dialog, SIGNAL(new_automaton(QString)),
                        this, SLOT  (new_automaton(QString)));
    dialog.exec();
}
