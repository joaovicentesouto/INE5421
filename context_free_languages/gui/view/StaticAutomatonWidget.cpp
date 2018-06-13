#include "StaticAutomatonWidget.hpp"
#include "ui_StaticAutomatonWidget.h"

StaticAutomatonWidget::StaticAutomatonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaticAutomatonWidget)
{
    ui->setupUi(this);
    ui->m_machine->setEditTriggers(QAbstractItemView::EditTriggers(0));
}

StaticAutomatonWidget::~StaticAutomatonWidget()
{
    delete ui;
}

void StaticAutomatonWidget::set_facade(Facade * facade)
{
    m_facade = facade;
}

void StaticAutomatonWidget::clean_up()
{
    ui->m_machine->clear();
    ui->m_machine->setRowCount(0);
    ui->m_machine->setColumnCount(0);

    ui->m_history->clear();

    m_current = Facade::automaton_type_ptr();
    m_current_item = 0;
}

void StaticAutomatonWidget::update_result(Facade::automaton_ptr_container_type& result)
{
    m_current = result.back().first;

    if (m_current->derived_ptr<dfa_type>())
        ui->m_machine << *m_current->derived_ptr<dfa_type>();
    else
        ui->m_machine << *m_current->derived_ptr<ndfa_type>();

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

    if (m_current->derived_ptr<dfa_type>())
        ui->m_machine << *m_current->derived_ptr<dfa_type>();
    else
        ui->m_machine << *m_current->derived_ptr<ndfa_type>();
}

void StaticAutomatonWidget::on_m_grammar_clicked()
{
    if (!m_current.get())
        return;

    grammar_type grammar;
    formal_device::manipulator::DevicesConverter converter;

    if (m_current->derived_ptr<dfa_type>())
        grammar = converter.convert(*m_current->derived_ptr<dfa_type>());
    else
        grammar = converter.convert(*m_current->derived_ptr<ndfa_type>());

    GrammarViewer dialog(grammar, this);
    dialog.exec();
}

void StaticAutomatonWidget::on_m_to_m1_clicked()
{
    const dfa_type  * dfa  = m_current->derived_ptr<dfa_type>();
    const ndfa_type * ndfa = m_current->derived_ptr<ndfa_type>();

    if (dfa)
        emit new_automaton(11, *dfa);

    if (ndfa)
        emit new_automaton(11, *ndfa);
}

void StaticAutomatonWidget::on_m_to_m2_clicked()
{
    const dfa_type  * dfa  = m_current->derived_ptr<dfa_type>();
    const ndfa_type * ndfa = m_current->derived_ptr<ndfa_type>();

    if (dfa)
        emit new_automaton(12, *dfa);

    if (ndfa)
        emit new_automaton(12, *ndfa);
}
