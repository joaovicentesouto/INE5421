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

    std::map<QString, automaton_type_ptr> * map;
    automaton_type_ptr * machine_ptr;

    if (machine == 1)
    {
        machine_ptr = &m_m1;
        map = &m_m1_history;
    }
    else
    {
        machine_ptr = &m_m2;
        map = &m_m2_history;
    }

    *machine_ptr = automaton_type_ptr(new ndfa_type(automaton));

    QString automaton_name = "Máquina " + QString::number(map->size());

    (*map)[automaton_name] = *machine_ptr;

    if (machine == 1)
        emit update_automaton_to_m1(automaton, automaton_name);
    else
        emit update_automaton_to_m2(automaton, automaton_name);
}

void Facade::new_expression(unsigned machine, expression_type_ptr expression)
{
    formal_device::manipulator::DeSimoneTree tree(expression);

    dfa_type automaton = tree.execute();

    std::map<QString, automaton_type_ptr> * map;
    automaton_type_ptr * machine_ptr;

    if (machine == 1)
    {
        machine_ptr = &m_m1;
        map = &m_m1_history;
    }
    else
    {
        machine_ptr = &m_m2;
        map = &m_m2_history;
    }

    *machine_ptr = automaton_type_ptr(new dfa_type(automaton));

    QString automaton_name = "Máquina " + QString::number(map->size());

    (*map)[automaton_name] = *machine_ptr;

    if (machine == 1)
        emit update_automaton_to_m1(automaton, automaton_name);
    else
        emit update_automaton_to_m2(automaton, automaton_name);
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
