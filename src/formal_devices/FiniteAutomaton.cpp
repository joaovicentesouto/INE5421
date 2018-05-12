#include "FiniteAutomaton.hpp"

namespace formal_device
{
namespace finite_automaton
{

Deterministic Deterministic::operator!() const
{
    return Deterministic();
}

Deterministic Deterministic::operator|(const Deterministic &machine) const
{
    return Deterministic();
}

Deterministic Deterministic::operator+(const Deterministic &machine) const
{
    return Deterministic();
}

Deterministic Deterministic::operator&(const Deterministic &machine) const
{
    return Deterministic();
}

Deterministic Deterministic::operator-(const Deterministic &machine) const
{
    return Deterministic();
}

Deterministic Deterministic::operator^(const Operation &op) const
{
    return Deterministic();
}

bool Deterministic::operator==(const Deterministic & machine) const
{
    return m_alphabet      == machine.m_alphabet      
        && m_states        == machine.m_states
        && m_transitions   == machine.m_transitions
        && m_final_states  == machine.m_final_states
        && m_initial_state == machine.m_initial_state;
}

bool Deterministic::membership(const string_type &sentece) const
{
    return false;
}

bool Deterministic::emptiness() const
{
    return false;
}

bool Deterministic::finiteness() const
{
    return false;
}

bool Deterministic::containment(const Deterministic &machine) const
{
    return false;
}

bool Deterministic::equivalence(const Deterministic &machine) const
{
    return false;
}

}  // namespace finite_automaton
}  // namespace formal_device

