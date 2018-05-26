#ifndef FACADE_H
#define FACADE_H

#include <QObject>
#include <QString>

#include <map>

#include <formal_languages/devices/FiniteAutomaton.hpp>
#include <formal_languages/devices/Grammar.hpp>
#include <formal_languages/devices/RegularExpression.hpp>

#include <formal_languages/manipulators/DevicesConverter.hpp>
#include <formal_languages/manipulators/DeSimoneTree.hpp>

using dfa_type            = formal_device::finite_automaton::Deterministic;
using ndfa_type           = formal_device::finite_automaton::NonDeterministic;
using grammar_type        = formal_device::grammar::Regular;
using expression_type_ptr = formal_device::expression::regular_ptr;

class Facade : public QObject
{
    Q_OBJECT

public:
    using automaton_type_ptr = std::shared_ptr<formal_device::finite_automaton::GenericAutomaton>;

    Facade();
    ~Facade();

    automaton_type_ptr request_automaton(unsigned machine, QString automaton);

public slots:
    void new_grammar(unsigned machine, grammar_type grammar);
    void new_expression(unsigned machine, expression_type_ptr expression);
    void new_automaton(unsigned machine, dfa_type automaton);
    void new_automaton(unsigned machine, ndfa_type automaton);

signals:
    void update_automaton_to_m1(const dfa_type& automaton, QString automaton_name);
    void update_automaton_to_m1(const ndfa_type& automaton, QString automaton_name);
    void update_automaton_to_m2(const dfa_type& automaton, QString automaton_name);
    void update_automaton_to_m2(const ndfa_type& automaton, QString automaton_name);

private:
    automaton_type_ptr m_m1;
    automaton_type_ptr m_m2;
    automaton_type_ptr m_result;

    std::map<QString, automaton_type_ptr> m_m1_history;
    std::map<QString, automaton_type_ptr> m_m2_history;
    std::map<QString, automaton_type_ptr> m_result_history;
};

#endif // FACADE_H
