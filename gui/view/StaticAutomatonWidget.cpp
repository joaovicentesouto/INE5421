#include "StaticAutomatonWidget.hpp"
#include "ui_StaticAutomatonWidget.h"

StaticAutomatonWidget::StaticAutomatonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaticAutomatonWidget)
{
    ui->setupUi(this);
}

StaticAutomatonWidget::~StaticAutomatonWidget()
{
    delete ui;
}

void StaticAutomatonWidget::set_facade(Facade * facade)
{
    m_facade = facade;
}

void StaticAutomatonWidget::update_result(Facade::automaton_ptr_container_type& result)
{
    m_current = result.back().first;

    const dfa_type * automaton = dynamic_cast<const dfa_type*>(m_current.get());
    if (automaton)
        ui->m_machine << *automaton;
    else
        ui->m_machine << *dynamic_cast<const ndfa_type*>(m_current.get());

    ui->m_history->clear();

    m_current_item = result.size()-1;

    for (auto pair : result)
        ui->m_history->addItem(pair.second);

    ui->m_history->item(m_current_item)->setBackgroundColor(Qt::gray);
}

void StaticAutomatonWidget::on_m_history_itemClicked(QListWidgetItem *item)
{
    ui->m_history->item(m_current_item)->setBackgroundColor(Qt::white);
    m_current_item = ui->m_history->currentRow();
    ui->m_history->item(m_current_item)->setBackgroundColor(Qt::gray);

    m_current = m_facade->request_automaton(3, item->text());

    const dfa_type * automaton = dynamic_cast<const dfa_type*>(m_current.get());
    if (automaton)
        ui->m_machine << *automaton;
    else
        ui->m_machine << *dynamic_cast<const ndfa_type*>(m_current.get());
}

void StaticAutomatonWidget::on_m_grammar_clicked()
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

void StaticAutomatonWidget::on_m_to_m1_clicked()
{
    const dfa_type  * dfa  = dynamic_cast<const dfa_type*>(m_current.get());
    const ndfa_type * ndfa = dynamic_cast<const ndfa_type*>(m_current.get());

    if (dfa)
        emit new_automaton(11, *dfa);

    if (ndfa)
        emit new_automaton(11, *ndfa);
}

void StaticAutomatonWidget::on_m_to_m2_clicked()
{
    const dfa_type  * dfa  = dynamic_cast<const dfa_type*>(m_current.get());
    const ndfa_type * ndfa = dynamic_cast<const ndfa_type*>(m_current.get());

    if (dfa)
        emit new_automaton(12, *dfa);

    if (ndfa)
        emit new_automaton(12, *ndfa);
}
