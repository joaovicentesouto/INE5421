#ifndef FACADE_H
#define FACADE_H

#include <QObject>
#include <QString>

#include <map>

#include <formal_languages/devices/FiniteAutomaton.hpp>
#include <formal_languages/devices/Grammar.hpp>
#include <formal_languages/devices/RegularExpression.hpp>

using dfa_type            = formal_device::finite_automaton::Deterministic;
using ndfa_type           = formal_device::finite_automaton::NonDeterministic;
using grammar_type        = formal_device::grammar::Regular;
using expression_type_ptr = formal_device::expression::regular_ptr;

class Facade : public QObject
{
    Q_OBJECT

public:
    Facade();
    ~Facade();

public slots:
    void new_grammar(grammar_type grammar);
    void new_expression(expression_type_ptr expression);
    void new_automaton(QString automaton);

signals:
    void update_automaton(QString automaton);
    void update_expression(expression_type_ptr expression);
    void update_grammar(grammar_type grammar);

private:
    ndfa_type m_m1;
    ndfa_type m_m2;
    ndfa_type m_result;

    std::map<QString, ndfa_type> m_m1_history;
    std::map<QString, ndfa_type> m_m2_history;
    std::map<QString, ndfa_type> m_result_history;
};

#endif // FACADE_H
