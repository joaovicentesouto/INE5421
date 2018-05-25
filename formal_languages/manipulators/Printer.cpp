#include "Printer.hpp"

namespace formal_device
{

std::ostream& operator<<(std::ostream& os, const finite_automaton::Deterministic& machine)
{
    os << "Deterministic";
    return os;
}

std::ostream& operator<<(std::ostream& os, const finite_automaton::NonDeterministic& machine)
{
    os << "NonDeterministic";
    return os;
}

std::ostream& operator<<(std::ostream& os, const grammar::Regular& reg_grammar)
{
    os << "Grammar\n";
    auto init = reg_grammar.initial_symbol();

    os << init.value() << " -> ";
    auto copy(reg_grammar.productions());

    int i = copy[init].size();
    for (auto production : copy[init])
    {
        os << production->to_string();
        if (--i > 0)
            os << " | ";
    }

    os << "\n";
    for (auto non_terminal : reg_grammar.vn())
    {
        if (non_terminal == init)
            continue;

        os << non_terminal.value() << " -> ";
        auto copy(reg_grammar.productions());
        int i = copy[non_terminal].size();
        for (auto production : copy[non_terminal])
        {
            os << production->to_string();
            if (--i > 0)
                os << " | ";
        }
        os << "\n";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const expression::regular_ptr& expression)
{
    return os << expression->to_string();
}

}   // namespace formal_devices
