#include "Facade.hpp"

Facade::Facade()
{

}

Facade::~Facade()
{

}

void Facade::new_grammar(unsigned machine, grammar_type grammar)
{
    if (machine == 1)
        emit update_automaton_to_m1(dfa_type());
    else
        emit update_automaton_to_m2(dfa_type());
}

void Facade::new_expression(unsigned machine, expression_type_ptr expression)
{
    if (machine == 1)
        emit update_automaton_to_m1(dfa_type());
    else
        emit update_automaton_to_m2(dfa_type());
}

void Facade::new_automaton(unsigned machine, dfa_type automaton)
{
    if (machine == 1)
        emit update_automaton_to_m1(automaton);
    else
        emit update_automaton_to_m2(automaton);
}

void Facade::new_automaton(unsigned machine, ndfa_type automaton)
{
    if (machine == 1)
        emit update_automaton_to_m1(automaton);
    else
        emit update_automaton_to_m2(automaton);
}
