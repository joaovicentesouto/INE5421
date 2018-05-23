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
    os << "Grammar";
    return os;
}

}   // namespace formal_devices
