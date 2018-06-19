#include "Printer.hpp"

grammar_type::string_type& operator<<(grammar_type::string_type& title, const grammar_type::terminal_set_type& set)
{
    title += " = { ";

    unsigned i = 0;
    for (const auto& terminal : set)
        title += ++i < set.size()? terminal.value() + " , " : terminal.value();

    return title += " }\n";
}

grammar_type::string_type& operator<<(grammar_type::string_type& title, const grammar_type::non_terminal_set_type& set)
{
    title += " = { ";

    unsigned i = 0;
    for (const auto& non_terminal : set)
        title += ++i < set.size()? non_terminal.value() + " , " : non_terminal.value();

    return title += " }\n";
}

grammar_type::string_type& operator<<(grammar_type::string_type& title, const grammar_type::recursion_map_type& map)
{
    title += "\n";

    unsigned i = 0;
    for (auto recursion : map)
    {
        if (!recursion.second[grammar_type::Recursion::Direct].empty())
            title += recursion.first.value() + " : Possuía recursão direta\n";
        else
            title += recursion.first.value() + " : Não possuía recursão direta\n";

        if (!recursion.second[grammar_type::Recursion::Indirect].empty())
        {
            title += recursion.first.value() + " : Indireta = { ";

            unsigned i = 0;
            for (const auto& non_terminal : recursion.second[grammar_type::Recursion::Indirect])
                title += ++i < map.size()? non_terminal.value() + " , " : non_terminal.value();

            title += " }";
        }
        else
            title += recursion.first.value() + " = Não possuía recursão direta";
    }

    return title += "\n";
}

grammar_type::string_type& operator<<(grammar_type::string_type& title, const grammar_type::simple_production_map_type& map)
{
    title += "\n";

    for (auto pair : map)
    {
        title += pair.first.value() + " = { ";

        unsigned i = 0;
        for (auto non_terminal : pair.second)
            title += ++i < map.size()? non_terminal.value() + " , " : non_terminal.value();

        title += " }\n";
    }

    return title;
}

grammar_type::string_type& operator<<(grammar_type::string_type& title, const grammar_type::symbol_ptr_set_type& set)
{
    title += " = { ";

    unsigned i = 0;
    for (const auto& symbol : set)
        title += ++i < set.size()? symbol->value() + " , " : symbol->value();

    return title += " }\n";
}
