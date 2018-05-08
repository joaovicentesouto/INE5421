#ifndef MODEL_FINITEAUTOMATON_COMPONENTS_H
#define MODEL_FINITEAUTOMATON_COMPONENTS_H

#include <string>
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

private:
    const string_type m_value;
};

class State
{
public:
    friend class Hasher;
    using string_type = std::string;

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
