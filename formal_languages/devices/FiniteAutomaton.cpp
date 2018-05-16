#include "FiniteAutomaton.hpp"

namespace formal_device
{
namespace finite_automaton
{

//using string_type         = std::string;
//using state_type          = State;
//using symbol_type         = Symbol;
//using state_set_type      = set_type<state_type>;
//using symbol_set_type     = set_type<symbol_type>;
//using transition_map_type = map_type<state_type, map_type<symbol_type, state_type>>;


// symbol_set_type     m_alphabet;
// state_set_type      m_states;
// transition_map_type m_transitions;
// state_set_type      m_final_states;
// state_type          m_initial_state;


Deterministic Deterministic::operator!() const
{
     symbol_set_type     new_alphabet = m_alphabet;
     state_set_type      new_states = m_states;
     transition_map_type new_transitions = m_transitions;
     state_set_type      new_final_states;
     state_type          new_initial_state = m_initial_state;

    state_type error("Error");

    new_states.insert(error);

    for (auto symbol : m_alphabet)
        new_transitions[error][symbol] = error;

    for (auto state : m_states)
        for (auto symbol : m_alphabet)
            new_transitions[state][symbol];

    auto not_final = m_final_states.end();

    for(auto state : m_states)
        if (m_final_states.find(state) == not_final)
            new_final_states.insert(state);

    new_final_states.insert(error);

    return Deterministic(std::move(new_alphabet),
                         std::move(new_states),
                         std::move(new_transitions),
                         std::move(new_final_states),
                         std::move(new_initial_state));
}

//map_type< state_type, map_type< symbol_type, set_type<state_type>>>;

NonDeterministic Deterministic::operator|(const Deterministic &machine) const
{
    NonDeterministic::symbol_set_type     new_alphabet = m_alphabet;
    NonDeterministic::state_set_type      new_states;
    NonDeterministic::transition_map_type new_transitions;
    NonDeterministic::state_set_type      new_final_states;

    NonDeterministic::state_type new_initial_state("q0");
    new_states.insert(new_initial_state);

    for (auto symbol : machine.m_alphabet)
        new_alphabet.insert(symbol);

    int i = 1;
    Deterministic::map_type<state_type, state_type> state_map_m1, state_map_m2;

    for (auto state : m_states) {
        state_type q{ "q" + std::to_string(i++) };
        state_map_m1[state] = q;
        new_states.insert(q);
    }

    for (auto state : machine.m_states) {
        state_type q{ "q" + std::to_string(i++) };
        state_map_m2[state] = q;
        new_states.insert(q);
    }

    for (auto trans : Deterministic::transition_map_type(m_transitions))
        for (auto target : trans.second)
            new_transitions[state_map_m1[trans.first]][target.first].insert(state_map_m1[target.second]);

    for (auto trans : Deterministic::transition_map_type(machine.m_transitions))
        for (auto target : trans.second)
            new_transitions[state_map_m2[trans.first]][target.first].insert(state_map_m2[target.second]);

    for (auto state : m_final_states)
        new_final_states.insert(state_map_m1[state]);
    
    for (auto state : machine.m_final_states)
        new_final_states.insert(state_map_m2[state]);

    Deterministic::transition_map_type copy = m_transitions;
    for (auto target : copy[m_initial_state])
        new_transitions[new_initial_state][target.first].insert(state_map_m1[target.second]);

    copy = machine.m_transitions;
    for (auto target : copy[machine.m_initial_state])
        new_transitions[new_initial_state][target.first].insert(state_map_m2[target.second]);

    if (m_final_states.find(m_initial_state) != m_final_states.end() || 
        machine.m_final_states.find(machine.m_initial_state) != machine.m_final_states.end())
        new_final_states.insert(new_initial_state);

    return NonDeterministic(std::move(new_alphabet),
                         std::move(new_states),
                         std::move(new_transitions),
                         std::move(new_final_states),
                         std::move(new_initial_state));
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

bool NonDeterministic::operator==(const NonDeterministic & machine) const
{
    return m_alphabet      == machine.m_alphabet
        && m_states        == machine.m_states
        && m_transitions   == machine.m_transitions
        && m_final_states  == machine.m_final_states
        && m_initial_state == machine.m_initial_state;
}

}  // namespace finite_automaton
}  // namespace formal_device

