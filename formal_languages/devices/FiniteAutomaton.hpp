#ifndef DEVICES_FINITEAUTOMATON_HPP
#define DEVICES_FINITEAUTOMATON_HPP

#include <string>
#include <deque>
#include <list>
#include <vector>
#include <functional>
#include <exception>
#include <set>
#include <unordered_map>
#include <map>
#include <formal_languages/components/FiniteAutomatonComponents.hpp>


namespace formal_device
{

namespace manipulator
{
    class DevicesConverter;
}

namespace finite_automaton
{

class NonDeterministic;

enum class Operation
{
    Reverse,
    Complete,
    Reflexive,
    Transitive,
    Optional
};

class GenericAutomaton
{
public:
    using string_type = std::string;

    virtual ~GenericAutomaton() = default;

    virtual bool membership(const string_type& sentece) const = 0;
    virtual bool emptiness() const = 0;
    virtual bool finiteness() const = 0;

    template <class Derived>
    const Derived* derived_ptr() const
    {
        return dynamic_cast<const Derived*>(this);
    }
};

class Deterministic : public GenericAutomaton
{
  public:
    friend class manipulator::DevicesConverter;
    friend class NonDeterministic;

    template <class T>
    using set_type            = std::set<T>;
    template <class Key, class Value>
    using map_type            = std::map<Key, Value>;

    using string_type         = GenericAutomaton::string_type;
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

    Deterministic(const symbol_set_type& alphabet);
    Deterministic(symbol_set_type&& alphabet);

    // Class member functions
    const symbol_set_type& alphabet() const;
    const state_set_type& states() const;
    const transition_map_type& transitions() const;
    const state_set_type& final_states() const;
    const state_type& initial_state() const;

    // Basic properties
    Deterministic    operator!() const; // not
    NonDeterministic operator|(const Deterministic & machine) const; // or
    NonDeterministic operator+(const Deterministic & machine) const; // concat
    Deterministic    operator&(const Deterministic & machine) const; // and
    Deterministic    operator-(const Deterministic & machine) const; // difference
    NonDeterministic operator^(const Operation & op) const; // operation
    bool operator==(const Deterministic & machine) const;

    Deterministic complete() const;
    Deterministic minimization() const;
    Deterministic remove_dead_states() const;
    Deterministic remove_unreachable_states() const;
    Deterministic remove_epsilon_transition() const;
    void equivalence_classes(set_type<state_set_type> & set) const;

    // decision problems
    bool membership(const string_type& sentece) const;
    bool emptiness() const;
    bool finiteness() const;
    bool containment(const Deterministic & machine) const;
    bool equivalence(const Deterministic & machine) const;

    bool is_complete() const;
    bool contains_epsilon_transition() const;

    string_type to_string() const;

private:
    bool contains_cycle(state_type state, state_set_type & temporary, state_set_type & permanent);

    symbol_set_type     m_alphabet;
    state_set_type      m_states{state_type("q0")};
    transition_map_type m_transitions;
    state_set_type      m_final_states;
    state_type          m_initial_state{"q0"};
};

class NonDeterministic : public GenericAutomaton
{
public:
    template <class T>
    using set_type            = Deterministic::set_type<T>;
    template <class Key, class Value>
    using map_type            = Deterministic::map_type<Key, Value>;

    using string_type         = Deterministic::string_type;
    using state_type          = Deterministic::state_type;
    using symbol_type         = Deterministic::symbol_type;
    using state_set_type      = Deterministic::state_set_type;
    using symbol_set_type     = Deterministic::symbol_set_type;
    using transition_map_type = map_type<state_type, map_type<symbol_type, set_type<state_type>>>;

    // Class constructors
    NonDeterministic() = default;

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

    NonDeterministic(const Deterministic &machine);
    NonDeterministic(const symbol_set_type& alphabet);
    NonDeterministic(symbol_set_type&& alphabet);

    // Class member functions
    const symbol_set_type& alphabet() const;
    const state_set_type& states() const;
    const transition_map_type& transitions() const;
    const state_set_type& final_states() const;
    const state_type& initial_state() const;

    Deterministic operator!() const; // not
    NonDeterministic operator|(const NonDeterministic & machine) const; // or
    NonDeterministic operator+(const NonDeterministic & machine) const; // concat
    Deterministic operator&(const NonDeterministic & machine) const; // and
    Deterministic operator-(const NonDeterministic & machine) const; // difference
    NonDeterministic operator^(const Operation & op) const; // operation
    bool operator==(const NonDeterministic & machine) const;

    Deterministic determination() const;
    Deterministic minimization() const;
    Deterministic remove_epsilon() const;

    bool membership(const string_type& sentence) const;
    bool emptiness() const;
    bool finiteness() const;
    bool containment(const NonDeterministic & machine) const;
    bool equivalence(const NonDeterministic & machine) const;

    bool contains_epsilon_transition() const;

    string_type to_string() const;

private:
    NonDeterministic reflexive() const;
    NonDeterministic transitive() const;
    NonDeterministic optional() const;
    NonDeterministic reverse() const;

    void build_closure(state_set_type& set, state_type state) const;

    symbol_set_type     m_alphabet;
    state_set_type      m_states;
    transition_map_type m_transitions;
    state_set_type      m_final_states;
    state_type          m_initial_state;
};

}  // finite_automaton
} // namespace formal_device

#endif // DEVICES_FINITEAUTOMATON_HPP
