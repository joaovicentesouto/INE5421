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

    for (auto pair : result)
        ui->m_history->addItem(pair.second);
}

void StaticAutomatonWidget::on_m_history_itemClicked(QListWidgetItem *item)
{
    m_current = m_facade->request_automaton(3, item->text());

    const dfa_type * automaton = dynamic_cast<const dfa_type*>(m_current.get());
    if (automaton)
        ui->m_machine << *automaton;
    else
        ui->m_machine << *dynamic_cast<const ndfa_type*>(m_current.get());
}
