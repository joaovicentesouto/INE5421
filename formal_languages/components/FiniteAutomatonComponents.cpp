#include "FiniteAutomatonComponents.hpp"

namespace formal_device
{
namespace finite_automaton
{

Symbol::Symbol(const string_type &symbol) :
    m_symbol{symbol}
{
}

Symbol::Symbol(string_type &&symbol) :
    m_symbol{std::move(symbol)}
{
}

bool Symbol::operator==(const Symbol &symbol) const
{
    return m_symbol == symbol.m_symbol;
}

bool Symbol::operator==(const string_type &symbol) const
{
    return m_symbol == symbol;
}

bool Symbol::operator<(const Symbol &symbol) const
{
    return m_symbol < symbol.m_symbol;
}

Symbol::string_type Symbol::value() const
{
    return m_symbol;
}

State::State(const string_type &state) :
    m_state(state)
{

}

State::State(string_type &&state) :
    m_state(std::move(state))
{

}

bool State::operator==(const State &state) const
{
    return m_state == state.m_state;
}

bool State::operator==(const string_type &state) const
{
    return m_state == state;
}

bool State::operator<(const State &state) const
{
    return m_state < state.m_state;
}

State::string_type State::value() const
{
    return m_state;
}

} // namespace finite_automaton
} // namespace formal_device
