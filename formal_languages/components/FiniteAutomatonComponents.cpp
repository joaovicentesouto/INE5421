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

State State::operator+(const State &sufix) const
{
    return m_state + sufix.m_state;
}

State State::operator+(const string_type &sufix) const
{
    return m_state + m_state;
}

bool State::operator<(const State &state) const
{
    return m_state < state.m_state;
}

std::size_t Hasher::operator()(const symbol_type &symbol) const
{
    return std::hash<std::string>()(symbol.m_symbol);
}

std::size_t Hasher::operator()(const state_type &state) const
{
    return std::hash<std::string>()(state.m_state);
}

std::size_t Hasher::operator()(const set_type<state_type> &set) const
{
    std::size_t acum = 0;

    for (auto state : set)
        acum += operator ()(state);

    return acum;
}

} // namespace finite_automaton
} // namespace formal_device
