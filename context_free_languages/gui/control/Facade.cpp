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
        std::string grammar_name = "Grammar " + (std::to_string(grammars_history.size() + 1));

        if (grammars_history.find(m_grammar) == grammars_history.end())
            emit insert_grammar_name(grammar_name, true);

        grammars_history.insert(m_grammar);
        grammar_mapping[grammar_name] = m_grammar;
        emit update_dynamic_grammar_data(construct_grammar_data(m_grammar));
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
    ContextFree grammar = m_grammar.factor(n);
    std::string grammar_name = "Grammar " + (std::to_string(grammars_history.size() + 1));

    if (grammars_history.find(grammar) == grammars_history.end())
        emit insert_grammar_name(grammar_name, false);

    grammars_history.insert(grammar);
    grammar_mapping[grammar_name] = grammar;

    emit set_static_grammar(grammar.to_string(), grammar_name);
    emit update_static_grammar_data("");
}

void Facade::make_own()
{
    ContextFree::symbol_ptr_set_type reachable;
    ContextFree::simple_production_map_type na;
    ContextFree::non_terminal_set_type fertible;
    ContextFree::non_terminal_set_type derives_epsilon;

    ContextFree grammar = m_grammar.own(derives_epsilon, na, fertible, reachable);
    std::string grammar_name = "Grammar " + (std::to_string(grammars_history.size() + 1));

    std::string string = "Derives Epsilon";
    string << derives_epsilon;

    string += "\nSimple Productions";
    string << na;

    string += "\nFertile symbols";
    string << derives_epsilon;

    string += "\nReachable symbols";
    string << reachable;

    if (grammars_history.find(grammar) == grammars_history.end())
        emit insert_grammar_name(grammar_name, false);

    grammars_history.insert(grammar);
    grammar_mapping[grammar_name] = grammar;

    emit set_static_grammar(grammar.to_string(), grammar_name);
    emit update_static_grammar_data(string);
}

void Facade::epsilon_free()
{
    ContextFree::non_terminal_set_type derives_epsilon;

    ContextFree grammar = m_grammar.epsilon_free(derives_epsilon);
    std::string grammar_name = "Grammar " + (std::to_string(grammars_history.size() + 1));

    std::string string = "Derives Epsilon";
    string << derives_epsilon;

    if (grammars_history.find(grammar) == grammars_history.end())
        emit insert_grammar_name(grammar_name, false);

    grammars_history.insert(grammar);
    grammar_mapping[grammar_name] = grammar;

    emit set_static_grammar(grammar.to_string(), grammar_name);
    emit update_static_grammar_data(string);
}

void Facade::remove_dead_symbols()
{
    ContextFree::non_terminal_set_type fertile_symbols;

    ContextFree grammar = m_grammar.remove_infertile_symbols(fertile_symbols);
    std::string grammar_name = "Grammar " + (std::to_string(grammars_history.size() + 1));
    
    std::string string = "Fertile symbols";
    string << fertile_symbols;

    if (grammars_history.find(grammar) == grammars_history.end())
        emit insert_grammar_name(grammar_name, false);

    grammars_history.insert(grammar);
    grammar_mapping[grammar_name] = grammar;

    emit set_static_grammar(grammar.to_string(), grammar_name);
    emit update_static_grammar_data(string);
}

void Facade::remove_left_recursion()
{
    ContextFree::recursion_map_type recursion;

    ContextFree grammar = m_grammar.remove_recursion(recursion);
    std::string grammar_name = "Grammar " + (std::to_string(grammars_history.size() + 1));

    std::string string = "Types of recursion";
    string << recursion;

    if (grammars_history.find(grammar) == grammars_history.end())
        emit insert_grammar_name(grammar_name, false);

    grammars_history.insert(grammar);
    grammar_mapping[grammar_name] = grammar;

    emit set_static_grammar(grammar.to_string(), grammar_name);
    emit update_static_grammar_data(string);
    
}

void Facade::remove_inutile_symbols()
{
    ContextFree::symbol_ptr_set_type reachable;
    ContextFree::non_terminal_set_type fertile_symbols;

    ContextFree grammar = m_grammar.remove_useless_symbols(fertile_symbols, reachable);
    std::string grammar_name = "Grammar " + (std::to_string(grammars_history.size() + 1));
    
    std::string string = "Fertile symbols";
    string << fertile_symbols;

    string += "\nReachable symbols";
    string << reachable;

    if (grammars_history.find(grammar) == grammars_history.end())
        emit insert_grammar_name(grammar_name, false);

    grammars_history.insert(grammar);
    grammar_mapping[grammar_name] = grammar;

    emit set_static_grammar(grammar.to_string(), grammar_name);
    emit update_static_grammar_data(string);
}

void Facade::remove_simple_production()
{
    ContextFree::simple_production_map_type na;

    ContextFree grammar = m_grammar.remove_simple_productions(na);
    std::string grammar_name = "Grammar " + (std::to_string(grammars_history.size() + 1));

    std::string string = "Simple Productions";
    string << na;

    if (grammars_history.find(grammar) == grammars_history.end())
        emit insert_grammar_name(grammar_name, false);

    grammars_history.insert(grammar);
    grammar_mapping[grammar_name] = grammar;

    emit set_static_grammar(grammar.to_string(), grammar_name);
    emit update_static_grammar_data(string);
    
}

void Facade::remove_unreachable_symbols()
{
    ContextFree::symbol_ptr_set_type reachable;

    ContextFree grammar = m_grammar.remove_unreachable_symbols(reachable);
    std::string grammar_name = "Grammar " + (std::to_string(grammars_history.size() + 1));
    
    std::string string = "Reachable symbols";
    string << reachable;

    if (grammars_history.find(grammar) == grammars_history.end())
        emit insert_grammar_name(grammar_name, false);

    grammars_history.insert(grammar);
    grammar_mapping[grammar_name] = grammar;

    emit set_static_grammar(grammar.to_string(), grammar_name);
    emit update_static_grammar_data(string);
}

std::string Facade::construct_grammar_data(ContextFree grammar)
{
    std::string data = "FIRST:\n\n";
    for (auto producer : grammar.first()) {
        auto symb = producer.first->value();
        data += "First( " + symb + " ) = { ";
        int i = 1;
        for (auto symbol : producer.second) {
            if (i++ == producer.second.size())
                data += symbol.value() + " }\n";
            else
                data += symbol.value() + " , ";
        }
        if (producer.second.size() == 0)
            data += " }\n";
    }

    data += "\nFOLLOW:\n\n";
    for (auto producer : grammar.follow()) {
        auto symb = producer.first.value();
        data += "Follow( " + symb + " ) = { ";
        int i = 1;
        for (auto symbol : producer.second) {
            if (i++ == producer.second.size())
                data += symbol.value() + " }\n";
            else
                data += symbol.value() + " , ";
        }
        if (producer.second.size() == 0)
            data += " }\n";
    }
    return data;
}

void Facade::change_grammar(std::string name)
{
    m_grammar = grammar_mapping[name];
    emit update_dynamic_grammar_data(construct_grammar_data(m_grammar));
    emit set_dynamic_grammar(m_grammar.to_string());
}
