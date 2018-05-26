#include "Facade.hpp"

Facade::Facade()
{

}

Facade::~Facade()
{

}

Facade::automaton_type_ptr Facade::request_automaton(unsigned machine, QString automaton)
{
    if (machine == 1)
        return m_m1_history[automaton];
    else
        return m_m2_history[automaton];
}

void Facade::new_grammar(unsigned machine, grammar_type grammar)
{
    formal_device::manipulator::DevicesConverter converter;

    ndfa_type automaton = converter.convert(grammar);

    if (machine == 1)
    {
        m_m1 = automaton_type_ptr(new ndfa_type(automaton));

        QString automaton_name = "Máquina " + QString::number(m_m1_history.size());
        m_m1_history[automaton_name] = m_m1;

        emit update_automaton_to_m1(automaton, automaton_name);
    }
    else
    {
        m_m2 = automaton_type_ptr(new ndfa_type(automaton));

        QString automaton_name = "Máquina " + QString::number(m_m2_history.size());
        m_m2_history[automaton_name] = m_m2;

        emit update_automaton_to_m2(automaton, automaton_name);
    }
}

void Facade::new_expression(unsigned machine, expression_type_ptr expression)
{
    if (machine == 1)
        emit update_automaton_to_m1(dfa_type(), "");
    else
        emit update_automaton_to_m2(dfa_type(), "");
}

void Facade::new_automaton(unsigned machine, dfa_type automaton)
{
    if (machine == 1)
        emit update_automaton_to_m1(automaton, "");
    else
        emit update_automaton_to_m2(automaton, "");
}

void Facade::new_automaton(unsigned machine, ndfa_type automaton)
{
    if (machine == 1)
        emit update_automaton_to_m1(automaton, "");
    else
        emit update_automaton_to_m2(automaton, "");
}
