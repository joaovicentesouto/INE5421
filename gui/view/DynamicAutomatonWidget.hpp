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
#include <view/GrammarViewer.hpp>
#include <view/BooleanDialog.hpp>

#include <formal_languages/manipulators/DevicesConverter.hpp>

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
    Facade::automaton_type_ptr current_machine();

public slots:
    void update_automaton(const dfa_type& automaton, QString automaton_name);
    void update_automaton(const ndfa_type& automaton, QString automaton_name);

    void clean_up();

private slots:
    void on_m_new_grammar_btn_clicked();
    void on_m_new_machine_btn_clicked();
    void on_m_new_exp_btn_clicked();

    void on_m_history_itemClicked(QListWidgetItem *item);
    void on_m_grammar_btn_clicked();
    void on_m_negation_btn_clicked();
    void on_m_closure_btn_clicked();
    void on_m_reverse_btn_clicked();
    void on_m_determinization_btn_clicked();
    void on_m_minimization_btn_clicked();
    void on_m_transitive_btn_clicked();
    void on_m_optional_btn_clicked();
    void on_m_n_sentences_clicked();
    void on_m_finitude_clicked();
    void on_m_emptiness_clicked();
    void on_m_membership_clicked();

private:
    Ui::DynamicAutomatonWidget * ui;
    Facade *                     m_facade{nullptr};
    unsigned                     m_number;
    Facade::automaton_type_ptr   m_current;
    unsigned                     m_current_item;
};

#endif // DYNAMICAUTOMATONWIDGET_HPP
