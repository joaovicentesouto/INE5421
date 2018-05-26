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

Facade::automaton_type_ptr DynamicAutomatonWidget::current_machine()
{
    return m_current;
}

void DynamicAutomatonWidget::on_m_new_grammar_btn_clicked()
{
    NewGrammarDialog dialog(m_number, this);

    QObject::connect(&dialog, SIGNAL(new_grammar(unsigned, grammar_type)),
                    m_facade, SLOT  (new_grammar(unsigned, grammar_type)));
    dialog.exec();
}

void DynamicAutomatonWidget::update_automaton(const dfa_type& automaton, QString automaton_name)
{
    ui->m_machine << automaton;

    bool exists = false;

    for (auto i = 0; i < ui->m_history->count(); ++i)
        exists |= (ui->m_history->item(i)->text() == automaton_name);

    if (!exists)
    {
        ui->m_history->addItem(automaton_name);
    }

    m_current = Facade::automaton_type_ptr(new dfa_type(automaton));
}

void DynamicAutomatonWidget::update_automaton(const ndfa_type& automaton, QString automaton_name)
{
    ui->m_machine << automaton;

    bool exists = false;

    for (auto i = 0; i < ui->m_history->count(); ++i)
        exists |= (ui->m_history->item(i)->text() == automaton_name);

    if (!exists)
    {
        ui->m_history->addItem(automaton_name);
    }

    m_current = Facade::automaton_type_ptr(new ndfa_type(automaton));
}

void DynamicAutomatonWidget::on_m_new_exp_btn_clicked()
{
    NewExpressionDialog dialog(m_number, this);

    QObject::connect(&dialog, SIGNAL(new_expression(unsigned, expression_type_ptr)),
                    m_facade, SLOT  (new_expression(unsigned, expression_type_ptr)));
    dialog.exec();
}

void DynamicAutomatonWidget::on_m_new_machine_btn_clicked()
{
    NewAutomatonDialog dialog(m_number, this);

    QObject::connect(&dialog, SIGNAL(new_automaton(unsigned, dfa_type)),
                    m_facade, SLOT  (new_automaton(unsigned, dfa_type)));

    QObject::connect(&dialog, SIGNAL(new_automaton(unsigned, ndfa_type)),
                    m_facade, SLOT  (new_automaton(unsigned, ndfa_type)));

    dialog.exec();
}

void DynamicAutomatonWidget::on_m_history_itemClicked(QListWidgetItem *item)
{
    m_current = m_facade->request_automaton(m_number, item->text());

    const dfa_type * automaton = dynamic_cast<const dfa_type*>(m_current.get());
    if (automaton)
        ui->m_machine << *automaton;
    else
        ui->m_machine << *dynamic_cast<const ndfa_type*>(m_current.get());
}

void DynamicAutomatonWidget::on_m_grammar_btn_clicked()
{
    if (!m_current.get())
        return;

    formal_device::manipulator::DevicesConverter converter;

    ndfa_type * to_grammar;

    const dfa_type * automaton = dynamic_cast<const dfa_type*>(m_current.get());
    if (automaton)
        to_grammar = new ndfa_type(*automaton);
    else
        to_grammar = new ndfa_type(*dynamic_cast<const ndfa_type*>(m_current.get()));

    GrammarViewer dialog(converter.convert(*to_grammar), this);
    dialog.exec();
}

void DynamicAutomatonWidget::on_m_negation_btn_clicked()
{
    if (!m_current.get())
        return ;

    m_facade->complement(m_current);
}

void DynamicAutomatonWidget::on_m_closure_btn_clicked()
{
    if (!m_current.get())
        return ;

    m_facade->reflexive_closure(m_current);
}

void DynamicAutomatonWidget::on_m_reverse_btn_clicked()
{
    if (!m_current.get())
        return ;

    m_facade->reverse(m_current);
}

void DynamicAutomatonWidget::on_m_determinization_btn_clicked()
{
    if (!m_current.get())
        return ;

    m_facade->determination(m_current);
}

void DynamicAutomatonWidget::on_m_minimization_btn_clicked()
{
    if (!m_current.get())
        return ;

    m_facade->minimization(m_current);
}
