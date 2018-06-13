#include "DynamicAutomatonWidget.hpp"
#include "ui_DynamicAutomatonWidget.h"

DynamicAutomatonWidget::DynamicAutomatonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DynamicAutomatonWidget)
{
    ui->setupUi(this);
    ui->m_machine->setEditTriggers(QAbstractItemView::EditTriggers(0));
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

void DynamicAutomatonWidget::clean_up()
{
    ui->m_machine->clear();
    ui->m_machine->setRowCount(0);
    ui->m_machine->setColumnCount(0);

    ui->m_history->clear();
    ui->m_sentence->clear();
    ui->m_n_of_sentences->clear();

    m_current = Facade::automaton_type_ptr();
    m_current_item = 0;
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

    unsigned count_machines = ui->m_history->count();

    if (count_machines > 0)
        ui->m_history->item(m_current_item)->setBackgroundColor(Qt::white);

    bool exists = false;

    for (auto i = 0; i < count_machines; ++i)
    {
        if (ui->m_history->item(i)->text() == automaton_name)
        {
            exists = true;
            m_current_item = i;
            break;
        }
    }

    if (!exists)
    {
        m_current_item = count_machines;
        ui->m_history->addItem(automaton_name);
    }

    ui->m_history->item(m_current_item)->setBackgroundColor(Qt::gray);

    m_current = Facade::automaton_type_ptr(new dfa_type(automaton));
}

void DynamicAutomatonWidget::update_automaton(const ndfa_type& automaton, QString automaton_name)
{
    ui->m_machine << automaton;

    unsigned count_machines = ui->m_history->count();

    if (count_machines)
        ui->m_history->item(m_current_item)->setBackgroundColor(Qt::white);

    bool exists = false;

    for (auto i = 0; i < count_machines; ++i)
    {
        if (ui->m_history->item(i)->text() == automaton_name)
        {
            exists = true;
            m_current_item = i;
            break;
        }
    }

    if (!exists)
    {
        m_current_item = count_machines;
        ui->m_history->addItem(automaton_name);
    }

    ui->m_history->item(m_current_item)->setBackgroundColor(Qt::gray);

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
    NewAutomatonDialog dialog(m_number, m_current, this);

    QObject::connect(&dialog, SIGNAL(new_automaton(unsigned, dfa_type)),
                     m_facade, SLOT  (new_automaton(unsigned, dfa_type)));

    QObject::connect(&dialog, SIGNAL(new_automaton(unsigned, ndfa_type)),
                    m_facade, SLOT  (new_automaton(unsigned, ndfa_type)));

    dialog.exec();
}

void DynamicAutomatonWidget::on_m_history_itemClicked(QListWidgetItem *item)
{
    ui->m_history->item(m_current_item)->setBackgroundColor(Qt::white);
    m_current_item = ui->m_history->currentRow();
    ui->m_history->item(m_current_item)->setBackgroundColor(Qt::gray);

    m_current = m_facade->request_automaton(m_number, item->text());

    if (m_current->derived_ptr<dfa_type>())
        ui->m_machine << *m_current->derived_ptr<dfa_type>();
    else
        ui->m_machine << *m_current->derived_ptr<ndfa_type>();
}

void DynamicAutomatonWidget::on_m_grammar_btn_clicked()
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

void DynamicAutomatonWidget::on_m_transitive_btn_clicked()
{
    if (!m_current.get())
        return ;

    m_facade->transitive_closure(m_current);
}

void DynamicAutomatonWidget::on_m_optional_btn_clicked()
{
    if (!m_current.get())
        return ;

    m_facade->optional(m_current);
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

void DynamicAutomatonWidget::on_m_n_sentences_clicked()
{
    if (!m_current.get())
        return;

    grammar_type grammar;
    formal_device::manipulator::DevicesConverter converter;

    if (m_current->derived_ptr<dfa_type>())
        grammar = converter.convert(*m_current->derived_ptr<dfa_type>());
    else
        grammar = converter.convert(*m_current->derived_ptr<ndfa_type>());

    unsigned n = ui->m_n_of_sentences->value();
    auto sentences = grammar.sentences_generator(n);

    GrammarViewer dialog(sentences, this);
    dialog.exec();
}

void DynamicAutomatonWidget::on_m_finitude_clicked()
{
    if (!m_current.get())
        return;

    QString answer = m_current->finiteness()? "T(M) é finita" : "T(M) é infinita";

    BooleanDialog dialog(answer, this);
    dialog.exec();
}

void DynamicAutomatonWidget::on_m_emptiness_clicked()
{
    if (!m_current.get())
        return;

    QString answer = m_current->emptiness()? "T(M) é vazia" : "T(M) não é vazia";

    BooleanDialog dialog(answer, this);
    dialog.exec();
}

void DynamicAutomatonWidget::on_m_membership_clicked()
{
    if (!m_current.get() || ui->m_sentence->text() == "")
        return;

    QString answer = "\"" + ui->m_sentence->text() + "\"";

    if (m_current->membership(ui->m_sentence->text().toStdString()))
        answer += " pertence a T(M)";
    else
        answer += " não pertence a T(M)";

    BooleanDialog dialog(answer, this);
    dialog.exec();
}
