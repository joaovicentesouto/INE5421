#ifndef MODEL_FINITEAUTOMATON_HPP
#define MODEL_FINITEAUTOMATON_HPP

#include <unordered_set>
#include <unordered_map>
#include "./FiniteAutomatonComponents.h"

namespace formal_device
{
namespace finite_automaton
{

class MinimalDeterministic; // Only the Deterministic can build it.

class Deterministic
{
  public:
    template <class T>
    using set_type            = std::unordered_set<T, Hasher>;
    template <class Key, class Value>
    using map_type            = std::unordered_map<Key, Value, Hasher>;

    using state_type          = State;
    using symbol_type         = Symbol;
    using state_set_type      = set_type<state_type>;
    using symbol_set_type     = set_type<symbol_type>;
    using transition_map_type = map_type<state_type, map_type<symbol_type, state_type>>;

    // Class constructors
    Deterministic() = delete;

    Deterministic(const Deterministic &) = default;
    Deterministic &operator=(const Deterministic &) = default;

    Deterministic(Deterministic &&) = default;
    Deterministic &operator=(Deterministic &&) = default;

    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    Deterministic(Arg1 &&alphabet, Arg2 &&states, Arg3 &&transitions, Arg4 &&final_states, Arg5 &&initial_state) :
        m_alphabet{std::forward<Arg1>(alphabet)},
        m_states{std::forward<Arg2>(states)},
        m_transitions{std::forward<Arg3>(transitions)},
        m_final_states{std::forward<Arg4>(final_states)},
        m_initial_state{std::forward<Arg5>(initial_state)}
    {
    }

    // Class member functions

    // union using operator+
    // denial using operator!
    // intersection using operator^
    // difference using operator-
    // reverse using operator^(char 'r') ???

private:
    symbol_set_type     m_alphabet;
    state_set_type      m_states;
    transition_map_type m_transitions;
    state_set_type      m_final_states;
    state_type          m_initial_state;
};

class DeterministicEpsilon : private Deterministic
{

};

class NonDeterministic
{
public:
    template <class T>
    using set_type            = Deterministic::set_type<T>;
    template <class Key, class Value>
    using map_type            = Deterministic::map_type<Key, Value>;

    using state_type          = Deterministic::state_type;
    using symbol_type         = Deterministic::symbol_type;
    using state_set_type      = Deterministic::state_set_type;
    using symbol_set_type     = Deterministic::symbol_set_type;
    using transition_map_type = map_type<state_type, map_type<symbol_type, set_type<state_type>>>;

    // Class constructors
    NonDeterministic() = delete;

    NonDeterministic(const NonDeterministic &) = default;
    NonDeterministic &operator=(const NonDeterministic &) = default;

    NonDeterministic(NonDeterministic &&) = default;
    NonDeterministic &operator=(NonDeterministic &&) = default;

    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    NonDeterministic(Arg1 &&alphabet, Arg2 &&states, Arg3 &&transitions, Arg4 &&final_states, Arg5 &&initial_state) :
        m_alphabet{std::forward<Arg1>(alphabet)},
        m_states{std::forward<Arg2>(states)},
        m_transitions{std::forward<Arg3>(transitions)},
        m_final_states{std::forward<Arg4>(final_states)},
        m_initial_state{std::forward<Arg5>(initial_state)}
    {
    }

private:
    symbol_set_type     m_alphabet;
    state_set_type      m_states;
    transition_map_type m_transitions;
    state_set_type      m_final_states;
    state_type          m_initial_state;
};

class NonDeterministicEpsilon : private NonDeterministic
{

};

}  // finite_automaton
} // namespace formal_device

#endif // MODEL_FINITEAUTOMATON_HPP
