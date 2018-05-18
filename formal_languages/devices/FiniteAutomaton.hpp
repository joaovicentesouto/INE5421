#ifndef DEVICES_FINITEAUTOMATON_HPP
#define DEVICES_FINITEAUTOMATON_HPP

#include <string>
#include <deque>
#include <list>
#include <vector>
#include <functional>
#include <exception>
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
class NonDeterministic;
class Deterministic
{
  public:
    friend class NonDeterministic;

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
    Deterministic operator!() const; // not
    NonDeterministic operator|(const Deterministic & machine) const; // or
    NonDeterministic operator+(const Deterministic & machine) const; // concat
    NonDeterministic operator&(const Deterministic & machine) const; // and
    NonDeterministic operator-(const Deterministic & machine) const; // difference
    NonDeterministic operator^(const Operation & op) const; // operation

    Deterministic complete() const;
    NonDeterministic remove_epsilon_transition() const;
    Deterministic minimization() const;

    Deterministic remove_dead_states() const;
    Deterministic remove_unreachable_states() const;
    Deterministic remove_equivalent_states() const;

    // decision problems
    bool membership(const string_type& sentece) const;
    bool emptiness() const;
    bool finiteness() const;
    bool containment(const Deterministic & machine) const;
    bool equivalence(const Deterministic & machine) const;

    bool is_complete() const;
    bool contains_epsilon_transition() const;

    bool operator==(const Deterministic & machine) const;

    void equivalence_classes(set_type<state_set_type> & set);
private:
    NonDeterministic reflexive() const;
    NonDeterministic transitive() const;
    NonDeterministic optional() const;
    NonDeterministic reverse() const;

    bool topologicalOrdering()
    {
        std::list<state_type> list;
        state_set_type temporary;
        state_set_type permanent;
        state_set_type sink_set;

        for (auto state : m_states)
            if (m_transitions[state].empty())
                sink_set.insert(state);

        while (!sink_set.empty())
        {

            state_type state = *sink_set.begin();
            sink_set.erase(state);

            visit(state, list, temporary, permanent);
        }

        return true;
    }

    void visit(state_type state, std::list<state_type> & list, state_set_type & temporary, state_set_type & permanent)
    {

        if (permanent.find(state) != permanent.end())
            return;

        if (temporary.find(state) != temporary.end())
            throw std::out_of_range("Is not a DAG, contains a cycle!");

        temporary.emplace(state);

        for (auto state_pred : m_states)
        {
            transition_map_type copy(m_transitions);
            for (auto trans : copy[state_pred])
                if (trans.second == state)
                    visit(state_pred, list, temporary, permanent);
        }

        temporary.erase(state);
        permanent.emplace(state);

        list.push_back(state);
    }

    symbol_set_type     m_alphabet;
    state_set_type      m_states;
    transition_map_type m_transitions;
    state_set_type      m_final_states;
    state_type          m_initial_state;
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
    NonDeterministic() = default;

    NonDeterministic(const Deterministic &machine);

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

    Deterministic remove_epsilon() const;
    Deterministic determination() const;

    NonDeterministic operator!() const; // not
    NonDeterministic operator|(const NonDeterministic & machine) const; // or
    NonDeterministic operator+(const NonDeterministic & machine) const; // concat
    NonDeterministic operator&(const NonDeterministic & machine) const; // and
    NonDeterministic operator-(const NonDeterministic & machine) const; // difference
    NonDeterministic operator^(const Operation & op) const; // operation

    bool operator==(const NonDeterministic & machine) const;

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
