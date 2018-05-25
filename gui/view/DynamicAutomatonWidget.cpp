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

void DynamicAutomatonWidget::set_facade(Facade * facade)
{
    m_facade = facade;
}

void DynamicAutomatonWidget::name(QString name)
{
    ui->m_name_machine->setText(name);
}

void DynamicAutomatonWidget::on_m_new_grammar_btn_clicked()
{
    NewGrammarDialog dialog(this);

    QObject::connect(&dialog, SIGNAL(new_grammar(grammar_type)),
                    m_facade, SLOT  (new_grammar(grammar_type)));
    dialog.exec();
}

void DynamicAutomatonWidget::update_grammar(grammar_type grammar)
{

}

void DynamicAutomatonWidget::on_m_new_exp_btn_clicked()
{
    NewExpressionDialog dialog(this);

    QObject::connect(&dialog, SIGNAL(new_expression(expression_type_ptr)),
                    m_facade, SLOT  (new_expression(expression_type_ptr)));
    dialog.exec();
}

void DynamicAutomatonWidget::update_expression(expression_type_ptr expression)
{

}

void DynamicAutomatonWidget::on_m_new_machine_btn_clicked()
{
    NewAutomatonDialog dialog(this);

    QObject::connect(&dialog, SIGNAL(new_automaton(QString)),
                    m_facade, SLOT  (new_automaton(QString)));
    dialog.exec();
}

void DynamicAutomatonWidget::update_automaton(QString automaton)
{

}
