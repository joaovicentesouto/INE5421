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

