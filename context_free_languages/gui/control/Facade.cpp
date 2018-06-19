#include "Facade.hpp"
#include <iostream>

Facade::Facade()
{
}

Facade::~Facade()
{
}

bool Facade::new_grammar(std::string grammar_text)
{
    try {
        m_grammar = formal_device::parser::grammar_parser(grammar_text);
        grammars_history.insert(m_grammar);
        grammar_mapping["grammar" + std::to_string(grammars_history.size())] = m_grammar;
        construct_grammar_data();
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

bool Facade::factored()
{
    return m_grammar.is_factored();
}

bool Facade::emptiness()
{
    return m_grammar.emptiness();
}

bool Facade::finiteness()
{
    return m_grammar.finitiness();
}

void Facade::factoring(uint n)
{
    emit set_static_grammar(m_grammar.factor(n).to_string());
}

void Facade::make_own()
{
    ContextFree::symbol_ptr_set_type reachable;
    ContextFree::simple_production_map_type na;
    ContextFree::non_terminal_set_type fertible;
    ContextFree::non_terminal_set_type derives_epsilon;
    emit set_static_grammar(m_grammar.own(derives_epsilon, na, fertible, reachable).to_string());
}

void Facade::epsilon_free()
{
    ContextFree::non_terminal_set_type derives_epsilon;
    emit set_static_grammar(m_grammar.epsilon_free(derives_epsilon).to_string());
}

void Facade::remove_dead_symbols()
{
    ContextFree::non_terminal_set_type fertile_symbols;
    emit set_static_grammar(m_grammar.remove_infertile_symbols(fertile_symbols).to_string());
}

void Facade::remove_left_recursion()
{
    //ContextFree::resursion_map_type recursion();
    //emit set_static_grammar(m_grammar.remove_recursion(recursion).to_string());
}

void Facade::remove_inutile_symbols()
{
    ContextFree::symbol_ptr_set_type reachable;
    ContextFree::non_terminal_set_type fertile_symbols;
    emit set_static_grammar(m_grammar.remove_useless_symbols(fertile_symbols, reachable).to_string());
}

void Facade::remove_simple_production()
{
    ContextFree::simple_production_map_type na;
    emit set_static_grammar(m_grammar.remove_simple_productions(na).to_string());
}

void Facade::remove_unreachable_symbols()
{
    ContextFree::symbol_ptr_set_type reachable;
    emit set_static_grammar(m_grammar.remove_unreachable_symbols(reachable).to_string());
}

void Facade::construct_grammar_data()
{
    std::string data = "FIRST:\n\n";
    for (auto producer : m_grammar.first()) {
        auto symb = producer.first->value();
        data += "First( " + symb + " ) = { ";
        int i = 1;
        for (auto symbol : producer.second) {
            if (i++ == producer.second.size())
                data += symbol.value() + " }\n";
            else
                data += symbol.value() + " , ";
        }
    }
    emit update_grammar_data(data);
}
