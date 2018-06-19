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

        if (grammars_history.find(m_grammar) != grammars_history.end())
            return true;

        grammars_history.insert(m_grammar);
        std::string grammar_name = "grammar" + std::to_string(grammars_history.size());

        grammar_mapping[grammar_name] = m_grammar;

        construct_grammar_data();
        emit insert_grammar_name(grammar_name);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

void Facade::new_result_grammar(const ContextFree& grammar)
{
    if (grammars_history.find(m_grammar) == grammars_history.end())
    {
        std::string grammar_name = "grammar" + std::to_string(grammars_history.size());

        grammar_mapping[grammar_name] = grammar;

        emit insert_grammar_name(grammar_name);
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
    auto new_grammar = m_grammar.factor(n);

    new_result_grammar(new_grammar);

    emit set_static_grammar(new_grammar.to_string(), "");
}

void Facade::make_own()
{
    ContextFree::symbol_ptr_set_type reachable;
    ContextFree::simple_production_map_type na;
    ContextFree::non_terminal_set_type fertible;
    ContextFree::non_terminal_set_type derives_epsilon;

    auto new_grammar = m_grammar.own(derives_epsilon, na, fertible, reachable);

    new_result_grammar(new_grammar);

    std::string string = "Derives Epsilon";
    string << derives_epsilon;

    string += "\nSimple Productions";
    string << na;

    string += "\nFertile symbols";
    string << derives_epsilon;

    string += "\nReachable symbols";
    string << reachable;

    emit set_static_grammar(new_grammar.to_string(), string);
}

void Facade::epsilon_free()
{
    ContextFree::non_terminal_set_type derives_epsilon;
    auto new_grammar = m_grammar.epsilon_free(derives_epsilon);

    new_result_grammar(new_grammar);

    std::string string = "Derives Epsilon";
    string << derives_epsilon;

    emit set_static_grammar(new_grammar.to_string(), string);
}

void Facade::remove_dead_symbols()
{
    ContextFree::non_terminal_set_type fertile_symbols;
    auto new_grammar = m_grammar.remove_infertile_symbols(fertile_symbols);

    new_result_grammar(new_grammar);

    std::string string = "Fertile symbols";
    string << fertile_symbols;

    emit set_static_grammar(new_grammar.to_string(), string);
}

void Facade::remove_left_recursion()
{
    ContextFree::recursion_map_type recursion;
    auto new_grammar = m_grammar.remove_recursion(recursion);

    new_result_grammar(new_grammar);

    std::string string = "Types of recursion";
    string << recursion;

    emit set_static_grammar(new_grammar.to_string(), string);
}

void Facade::remove_inutile_symbols()
{
    ContextFree::symbol_ptr_set_type reachable;
    ContextFree::non_terminal_set_type fertile_symbols;

    auto new_grammar = m_grammar.remove_useless_symbols(fertile_symbols, reachable);

    new_result_grammar(new_grammar);

    std::string string = "Fertile symbols";
    string << fertile_symbols;

    string += "\nReachable symbols";
    string << reachable;

    emit set_static_grammar(new_grammar.to_string(), string);
}

void Facade::remove_simple_production()
{
    ContextFree::simple_production_map_type na;
    auto new_grammar = m_grammar.remove_simple_productions(na);

    new_result_grammar(new_grammar);

    std::string string = "Simple Productions";
    string << na;

    emit set_static_grammar(new_grammar.to_string(), string);
}

void Facade::remove_unreachable_symbols()
{
    ContextFree::symbol_ptr_set_type reachable;
    auto new_grammar = m_grammar.remove_unreachable_symbols(reachable);

    new_result_grammar(new_grammar);

    std::string string = "Reachable symbols";
    string << reachable;

    emit set_static_grammar(new_grammar.to_string(), string);
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
