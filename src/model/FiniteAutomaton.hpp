#ifndef MODEL_FINITEAUTOMATON_HPP
#define MODEL_FINITEAUTOMATON_HPP

#include <string>
#include <unordered_set>
#include <unordered_map>
#include "./FiniteAutomatonComponents.hpp"

namespace formal_device
{
namespace finite_automaton
{

enum class Operation
{
    Reverse,
    Complete,
    Reflexive,
    Transitive,
    Optional
};

class Deterministic
{
  public:
    template <class T>
    using set_type            = std::unordered_set<T, Hasher>;
    template <class Key, class Value>
    using map_type            = std::unordered_map<Key, Value, Hasher>;

    using string_type         = std::string;
    using state_type          = State;
    using symbol_type         = Symbol;
    using state_set_type      = set_type<state_type>;
    using symbol_set_type     = set_type<symbol_type>;
    using transition_map_type = map_type<state_type, map_type<symbol_type, state_type>>;

    // Class constructors
    Deterministic() = default;

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

    // Basic properties
    virtual Deterministic operator!() const; // not
    virtual Deterministic operator|(const Deterministic & machine) const; // or
    virtual Deterministic operator+(const Deterministic & machine) const; // concat
    virtual Deterministic operator&(const Deterministic & machine) const; // and
    virtual Deterministic operator-(const Deterministic & machine) const; // difference
    virtual Deterministic operator^(const Operation & op) const; // operation

    // Decision problems
    virtual bool membership(const string_type& sentece) const;
    virtual bool emptiness() const;
    virtual bool finiteness() const;
    virtual bool containment(const Deterministic & machine) const;
    virtual bool equivalence(const Deterministic & machine) const;

private:
    symbol_set_type     m_alphabet;
    state_set_type      m_states;
    transition_map_type m_transitions;
    state_set_type      m_final_states;
    state_type          m_initial_state{""};
};

class MinimalDeterministic : public Deterministic
{
public:
    friend class Deterministic;

private:
    MinimalDeterministic(); // Only the Deterministic can build it.
};

class DeterministicEpsilon : public Deterministic
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

class NonDeterministicEpsilon : public NonDeterministic
{

};

}  // finite_automaton
} // namespace formal_device

#endif // MODEL_FINITEAUTOMATON_HPP
