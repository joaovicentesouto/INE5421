#ifndef DYNAMICAUTOMATONWIDGET_HPP
#define DYNAMICAUTOMATONWIDGET_HPP

#include <QWidget>
#include <QColor>

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

    void name(QString name);

public slots:
    void update_automaton(dfa_type automaton);
    void update_automaton(ndfa_type automaton);

private slots:
    void on_m_new_grammar_btn_clicked();
    void on_m_new_machine_btn_clicked();
    void on_m_new_exp_btn_clicked();

private:
    Ui::DynamicAutomatonWidget *ui;
    Facade * m_facade;
};

#endif // DYNAMICAUTOMATONWIDGET_HPP
