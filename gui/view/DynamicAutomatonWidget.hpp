#ifndef DYNAMICAUTOMATONWIDGET_HPP
#define DYNAMICAUTOMATONWIDGET_HPP

#include <QWidget>
#include <QColor>
#include <QListWidget>

#include <control/Facade.hpp>
#include <control/Filler.hpp>
#include <view/NewGrammarDialog.hpp>
#include <view/NewAutomatonDialog.hpp>
#include <view/NewExpressionDialog.hpp>

namespace Ui {
class DynamicAutomatonWidget;
}

class DynamicAutomatonWidget : public QWidget
{
    Q_OBJECT

public:
    using dfa_type            = formal_device::finite_automaton::Deterministic;
    using ndfa_type           = formal_device::finite_automaton::NonDeterministic;
    using grammar_type        = formal_device::grammar::Regular;
    using expression_type_ptr = formal_device::expression::regular_ptr;

    explicit DynamicAutomatonWidget(QWidget *parent = 0);
    ~DynamicAutomatonWidget();

    void set_facade(Facade * facade);

    void name(unsigned number);

public slots:
    void update_automaton(const dfa_type& automaton, QString automaton_name);
    void update_automaton(const ndfa_type& automaton, QString automaton_name);

private slots:
    void on_m_new_grammar_btn_clicked();
    void on_m_new_machine_btn_clicked();
    void on_m_new_exp_btn_clicked();

    void on_m_history_itemClicked(QListWidgetItem *item);

private:
    Ui::DynamicAutomatonWidget *ui;
    Facade * m_facade;
    unsigned m_number;
};

#endif // DYNAMICAUTOMATONWIDGET_HPP
