#include "Facade.hpp"
#include <iostream>

Facade::Facade()
{
}

Facade::~Facade()
{
}

std::string Facade::new_grammar(std::string grammar_text)
{
    try {
        m_grammar = formal_device::parser::grammar_parser(grammar_text);
        std::string grammar_name = "Grammar " + (std::to_string(grammars_history.size() + 1));

        if (grammars_history.find(m_grammar) == grammars_history.end())
            emit insert_grammar_name(grammar_name, true);
        else
            for (auto component: grammar_mapping)
                if (m_grammar == component.second)
                    grammar_name = component.first;

        grammars_history.insert(m_grammar);
        grammar_mapping[grammar_name] = m_grammar;
        emit update_dynamic_grammar_data(construct_grammar_data(m_grammar));
        return "Validated with successfully!";

    } catch (const std::out_of_range& e) {
        return e.what();
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

bool Facade::has_recursion()
{
    return m_grammar.has_recursion();
}

bool Facade::factoring(uint n)
{
    ContextFree grammar = m_grammar.factor(n);
    make_change(grammar, "");
    return grammar.is_factored();
}

void Facade::make_own()
{
    ContextFree::symbol_ptr_set_type reachable;
    ContextFree::simple_production_map_type na;
    ContextFree::non_terminal_set_type fertible;
    ContextFree::non_terminal_set_type derives_epsilon;

    ContextFree grammar = m_grammar.epsilon_free(derives_epsilon);

    std::string string = "Derives Epsilon";
    string << derives_epsilon;

    make_change(grammar, string);

    grammar = grammar.remove_simple_productions(na);

    string += "\nSimple Productions";
    string << na;

    make_change(grammar, string, false);

    grammar = grammar.remove_infertile_symbols(fertible);

    string += "\nFertile symbols";
    string << fertible;

    make_change(grammar, string, false);

    grammar = grammar.remove_unreachable_symbols(reachable);

    string += "\nReachable symbols";
    string << reachable;

    make_change(grammar, string, false);
}

void Facade::epsilon_free()
{
    ContextFree::non_terminal_set_type derives_epsilon;

    ContextFree grammar = m_grammar.epsilon_free(derives_epsilon);

    std::string string = "Derives Epsilon";
    string << derives_epsilon;

    make_change(grammar, string);
}

void Facade::remove_dead_symbols()
{
    ContextFree::non_terminal_set_type fertile_symbols;

    ContextFree grammar = m_grammar.remove_infertile_symbols(fertile_symbols);
    
    std::string string = "Fertile symbols";
    string << fertile_symbols;

    make_change(grammar, string);
}

void Facade::remove_left_recursion()
{
    ContextFree::recursion_map_type recursion;

    ContextFree grammar = m_grammar.remove_recursion(recursion);

    std::string string = "Types of recursion";
    string << recursion;
    
    make_change(grammar, string);
}

void Facade::remove_inutile_symbols()
{
    ContextFree::symbol_ptr_set_type reachable;
    ContextFree::non_terminal_set_type fertile_symbols;

    ContextFree grammar = m_grammar.remove_infertile_symbols(fertile_symbols);
    
    std::string string = "Fertile symbols";
    string << fertile_symbols;

    make_change(grammar, string);

    grammar = grammar.remove_unreachable_symbols(reachable);

    string += "\nReachable symbols";
    string << reachable;

    make_change(grammar, string, false);
}

void Facade::remove_simple_production()
{
    ContextFree::simple_production_map_type na;

    ContextFree grammar = m_grammar.remove_simple_productions(na);

    std::string string = "Simple Productions";
    string << na;
    
    make_change(grammar, string);
}

void Facade::remove_unreachable_symbols()
{
    ContextFree::symbol_ptr_set_type reachable;

    auto grammar = m_grammar.remove_unreachable_symbols(reachable);

    std::string string = "Reachable symbols";
    string << reachable;

    make_change(grammar, string);
}

void Facade::make_change(ContextFree grammar, std::string result_data, bool first)
{
    std::string grammar_name = "Grammar " + (std::to_string(grammars_history.size() + 1));

    if (grammars_history.find(grammar) == grammars_history.end())
        emit insert_grammar_name(grammar_name, false);
    else
        for (auto component: grammar_mapping)
            if (grammar == component.second)
                grammar_name = component.first;

    grammars_history.insert(grammar);
    grammar_mapping[grammar_name] = grammar;

    emit set_static_grammar(grammar.to_string(), grammar_name, first);
    emit update_static_grammar_data(result_data);
}

std::string Facade::construct_grammar_data(ContextFree grammar)
{
    std::string data = "FIRST:\n\n";
    for (auto producer : grammar.first()) {
        if (producer.first->is_terminal())
            continue;

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
    data += "\nFIRST-NT:\n\n";
    for (auto producer : grammar.first_nt()) {
        auto symb = producer.first.value();
        data += "First-NT( " + symb + " ) = { ";
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
