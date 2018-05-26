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

void DynamicAutomatonWidget::name(unsigned number)
{
    m_number = number;
    ui->m_name_machine->setText("Máquina " + QString::number(number));
}

void DynamicAutomatonWidget::on_m_new_grammar_btn_clicked()
{
    NewGrammarDialog dialog(this);

    QObject::connect(&dialog, SIGNAL(new_grammar(unsigned, grammar_type)),
                    m_facade, SLOT  (new_grammar(unsigned, grammar_type)));
    dialog.exec();
}

void DynamicAutomatonWidget::update_automaton(const dfa_type& automaton, QString automaton_name)
{
    ui->m_machine << automaton;
    ui->m_history->addItem(automaton_name);
}

void DynamicAutomatonWidget::update_automaton(const ndfa_type& automaton, QString automaton_name)
{
    ui->m_machine << automaton;
    ui->m_history->addItem(automaton_name);
}

void DynamicAutomatonWidget::on_m_new_exp_btn_clicked()
{
    NewExpressionDialog dialog(this);

    QObject::connect(&dialog, SIGNAL(new_expression(unsigned, expression_type_ptr)),
                    m_facade, SLOT  (new_expression(unsigned, expression_type_ptr)));
    dialog.exec();
}

void DynamicAutomatonWidget::on_m_new_machine_btn_clicked()
{
    NewAutomatonDialog dialog(this);

    QObject::connect(&dialog, SIGNAL(new_automaton(unsigned, dfa_type)),
                    m_facade, SLOT  (new_automaton(unsigned, dfa_type)));

    QObject::connect(&dialog, SIGNAL(new_automaton(unsigned, ndfa_type)),
                    m_facade, SLOT  (new_automaton(unsigned, ndfa_type)));

    dialog.exec();
}

void DynamicAutomatonWidget::on_m_history_itemClicked(QListWidgetItem *item)
{
    Facade::automaton_type_ptr p = m_facade->request_automaton(m_number, item->text());

    const dfa_type * automaton = dynamic_cast<const dfa_type*>(p.get());
    if (automaton)
        ui->m_machine << *automaton;
    else
        ui->m_machine << *dynamic_cast<const ndfa_type*>(p.get());
}
