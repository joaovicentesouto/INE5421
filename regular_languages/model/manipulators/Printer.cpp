#include "Printer.hpp"

namespace formal_device
{

std::ostream& operator<<(std::ostream& os, const finite_automaton::Deterministic& machine)
{
    return os << machine.to_string();
}

std::ostream& operator<<(std::ostream& os, const finite_automaton::NonDeterministic& machine)
{
    return os << machine.to_string();
}

std::ostream& operator<<(std::ostream& os, const grammar::Regular& reg_grammar)
{
    return os << reg_grammar.to_string();
}

std::ostream& operator<<(std::ostream& os, const expression::regular_ptr& expression)
{
    return os << expression->to_string();
}

}   // namespace formal_devices
