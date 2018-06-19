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

    std::string direct{"\nDirect = { "}, indirect{"\nIndirect\n"};
    bool has_indirect = false;

    unsigned i = 0;
    for (auto recursion : map)
    {
        if (!recursion.second[grammar_type::Recursion::Direct].empty())
            direct += i++ == 0? recursion.first.value() : " , " + recursion.first.value();

        if (!recursion.second[grammar_type::Recursion::Indirect].empty())
        {
            has_indirect = true;

            indirect += recursion.first.value() + " = { ";

            unsigned j = 0;
            for (const auto& non_terminal : recursion.second[grammar_type::Recursion::Indirect])
                indirect += j++ == 0? non_terminal.value() : " , " + non_terminal.value();

            indirect += " }\n";
        }
    }

    title += direct + " } \n" + (has_indirect? indirect : "");

    return title;
}

grammar_type::string_type& operator<<(grammar_type::string_type& title, const grammar_type::simple_production_map_type& map)
{
    title += "\n";

    for (auto pair : map)
    {
        title += pair.first.value() + " = { ";

        unsigned i = 0;
        for (auto non_terminal : pair.second)
            title += i++ == 0? non_terminal.value() : " , " + non_terminal.value();

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
