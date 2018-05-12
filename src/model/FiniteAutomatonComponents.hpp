#ifndef MODEL_FINITEAUTOMATON_COMPONENTS_H
#define MODEL_FINITEAUTOMATON_COMPONENTS_H

#include <string>
#include <utility>
#include <unordered_set>
#include <unordered_map>

namespace formal_device
{
namespace finite_automaton
{

class Symbol
{
public:
    friend class Hasher;
    using string_type = std::string;

    Symbol() = delete;

    Symbol(const Symbol &) = default;
    Symbol &operator=(const Symbol &) = default;
    Symbol(Symbol &&) = default;
    Symbol &operator=(Symbol &&) = default;

    template <class Arg1>
    Symbol(Arg1 &&value) :
        m_value{std::forward<Arg1>(value)}
    {
    }

    ~Symbol() = default;

private:
    const string_type m_value;
};

class State
{
public:
    friend class Hasher;
    using string_type = std::string;

    State() = delete;

    State(const State &) = default;
    State &operator=(const State &) = default;
    State(State &&) = default;
    State &operator=(State &&) = default;

    template <class Arg1>
    State(Arg1 &&value) :
        m_value{std::forward<Arg1>(value)}
    {
    }

    ~State() = default;

private:
    const string_type m_value;
    bool        m_final; // It is necessary? Because exists a final states set
};

class Hasher
{
public:
  using symbol_type = Symbol;
  using state_type  = State;

  std::size_t operator()(const symbol_type &symbol) const;
  std::size_t operator()(const state_type &state) const;
};

} // namespace finite_automaton
} // namespace formal_device

#endif // MODEL_FINITEAUTOMATON_COMPONENTS_H
