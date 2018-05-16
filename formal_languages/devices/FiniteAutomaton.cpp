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
    NonDeterministic::symbol_set_type     new_alphabet;
    NonDeterministic::state_set_type      new_states;
    NonDeterministic::transition_map_type new_transitions;
    NonDeterministic::state_set_type      new_final_states;
    Deterministic::map_type<state_type, state_type> state_map_m1, state_map_m2;

    /* ------ New initial state ------ */

    NonDeterministic::state_type new_initial_state("q0");
    new_states.insert(new_initial_state);

    /* ------ New alphabet ------ */

    new_alphabet = m_alphabet;

    for (auto symbol : machine.m_alphabet)
        new_alphabet.insert(symbol);


    /* ------ New states ------ */

    int i = 1;
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

    /* ------ New transitions ------ */

    for (auto trans : Deterministic::transition_map_type(m_transitions))
        for (auto target : trans.second)
            new_transitions[state_map_m1[trans.first]][target.first].insert(state_map_m1[target.second]);

    for (auto trans : Deterministic::transition_map_type(machine.m_transitions))
        for (auto target : trans.second)
            new_transitions[state_map_m2[trans.first]][target.first].insert(state_map_m2[target.second]);

    /* ------ New final states ------ */

    for (auto state : m_final_states)
        new_final_states.insert(state_map_m1[state]);
    
    for (auto state : machine.m_final_states)
        new_final_states.insert(state_map_m2[state]);

    /* ------ Transitions of new initial state ------ */

    Deterministic::transition_map_type copy = m_transitions;
    for (auto target : copy[m_initial_state])
        new_transitions[new_initial_state][target.first].insert(state_map_m1[target.second]);

    copy = machine.m_transitions;
    for (auto target : copy[machine.m_initial_state])
        new_transitions[new_initial_state][target.first].insert(state_map_m2[target.second]);

    /* ------ Checks if new initial state is a final state ------ */

    if (m_final_states.find(m_initial_state) != m_final_states.end() || 
        machine.m_final_states.find(machine.m_initial_state) != machine.m_final_states.end())
        new_final_states.insert(new_initial_state);

    return NonDeterministic(std::move(new_alphabet),
                         std::move(new_states),
                         std::move(new_transitions),
                         std::move(new_final_states),
                         std::move(new_initial_state));
}

NonDeterministic Deterministic::operator+(const Deterministic &machine) const
{
    NonDeterministic::symbol_set_type     new_alphabet;
    NonDeterministic::state_set_type      new_states;
    NonDeterministic::transition_map_type new_transitions;
    NonDeterministic::state_set_type      new_final_states;

    Deterministic::map_type<state_type, state_type> state_map_m1, state_map_m2;

    /* ------ New initial state ------ */

    NonDeterministic::state_type new_initial_state("q0");
    state_map_m1[m_initial_state] = new_initial_state;

    new_states.insert(new_initial_state);

    /* ------ New alphabet ------ */

    new_alphabet = m_alphabet;

    for (auto symbol : machine.m_alphabet)
        new_alphabet.insert(symbol);

    /* ------ New states ------ */

    int i = 1;
    for (auto state : m_states) {
        if (state == m_initial_state)
            continue;

        state_type q{ "q" + std::to_string(i++) };
        state_map_m1[state] = q;
        new_states.insert(q);
    }

    for (auto state : machine.m_states) {
        state_type q{ "q" + std::to_string(i++) };
        state_map_m2[state] = q;
        new_states.insert(q);
    }

    /* ------ New transitions ------ */

    for (auto trans : Deterministic::transition_map_type(m_transitions))
        for (auto target : trans.second)
            new_transitions[state_map_m1[trans.first]][target.first].insert(state_map_m1[target.second]);

    for (auto trans : Deterministic::transition_map_type(machine.m_transitions))
        for (auto target : trans.second)
            new_transitions[state_map_m2[trans.first]][target.first].insert(state_map_m2[target.second]);

    /* ------ Transitions of final states of M1 to initial state of M2 ------ */

    for (auto f : m_final_states)
    {
        auto final_state = state_map_m1[f];
        NonDeterministic::transition_map_type copy = new_transitions;

        for (auto target : copy[state_map_m2[machine.m_initial_state]])
            for (auto target_state : target.second)
                new_transitions[final_state][target.first].insert(target_state);
    }

    /* ------ New final states ------ */

    if (machine.m_final_states.find(machine.m_initial_state) != machine.m_final_states.end())
        for (auto state : m_final_states)
            new_final_states.insert(state_map_m1[state]);

    for (auto state : machine.m_final_states)
        new_final_states.insert(state_map_m2[state]);

    return NonDeterministic(std::move(new_alphabet),
                         std::move(new_states),
                         std::move(new_transitions),
                         std::move(new_final_states),
                         std::move(new_initial_state));
}

NonDeterministic Deterministic::operator&(const Deterministic &machine) const
{
    return !(!(*this) | !machine);
}

NonDeterministic Deterministic::operator-(const Deterministic &machine) const
{
    return *this & !machine;
}

NonDeterministic Deterministic::operator^(const Operation &op) const
{
    switch (op)
    {
    case Operation::Reflexive:
        return reflexive();

    case Operation::Transitive:
        return transitive();

    case Operation::Optional:
        return optional();

    case Operation::Reverse:
        return reverse();

    default:
        return NonDeterministic();
    }
}

NonDeterministic Deterministic::reflexive() const
{
    NonDeterministic::symbol_set_type     new_alphabet = m_alphabet;
    NonDeterministic::state_set_type      new_states = m_states;
    NonDeterministic::state_set_type      new_final_states = m_final_states;
    NonDeterministic::state_type          new_initial_state = m_initial_state;

    /* ------ New transitions ------ */

    NonDeterministic::transition_map_type new_transitions;
    for (auto trans : Deterministic::transition_map_type(m_transitions))
        for (auto target : trans.second)
            new_transitions[trans.first][target.first].insert(target.second);

    /* ------ Transitions of final states of M1 to initial state of M2 ------ */

    for (auto final_state : m_final_states)
    {
        NonDeterministic::transition_map_type copy = new_transitions;

        for (auto target : copy[m_initial_state])
            for (auto target_state : target.second)
                new_transitions[final_state][target.first].insert(target_state);
    }

    /* ------ New final states ------ */

    new_final_states.insert(new_initial_state);

    return NonDeterministic(std::move(new_alphabet),
                         std::move(new_states),
                         std::move(new_transitions),
                         std::move(new_final_states),
                         std::move(new_initial_state));
}

NonDeterministic Deterministic::transitive() const
{
    return NonDeterministic(*this) + (*this)^Operation::Reflexive;
}

NonDeterministic Deterministic::optional() const
{
    state_type                            q0{"q0"};
    NonDeterministic::symbol_set_type     new_alphabet;
    NonDeterministic::state_set_type      new_states{q0};
    NonDeterministic::transition_map_type new_transitions;
    NonDeterministic::state_set_type      new_final_states{q0};
    NonDeterministic::state_type          new_initial_state{q0};

    return NonDeterministic(*this) | NonDeterministic(std::move(new_alphabet),
                                                      std::move(new_states),
                                                      std::move(new_transitions),
                                                      std::move(new_final_states),
                                                      std::move(new_initial_state));
}

NonDeterministic Deterministic::reverse() const
{
    NonDeterministic::symbol_set_type     new_alphabet = m_alphabet;
    NonDeterministic::state_set_type      new_final_states;
    NonDeterministic::transition_map_type new_transitions;
    NonDeterministic::state_set_type      new_states;

    Deterministic::map_type<state_type, state_type> state_map;

    /* ------ New initial state ------ */

    NonDeterministic::state_type new_initial_state("q0");

    new_states.insert(new_initial_state);

    /* ------ New states ------ */

    int i = 1;
    for (auto state : m_states) {
        state_type q{ "q" + std::to_string(i++) };
        state_map[state] = q;
        new_states.insert(q);
    }

    /* ------ New transitions ------ */

    for (auto trans : Deterministic::transition_map_type(m_transitions))
        for (auto target : trans.second)
            new_transitions[state_map[target.second]][target.first].insert(state_map[trans.first]);

    /* ------ Copy of transitions from old final states to new initial states ------ */

    for (auto f : m_final_states)
    {
        auto final_state = state_map[f];
        NonDeterministic::transition_map_type copy = new_transitions;

        for (auto target : copy[final_state])
            for (auto target_state : target.second)
                new_transitions[new_initial_state][target.first].insert(target_state);
    }

    /* ------ New final states ------ */

    new_final_states.insert(state_map[m_initial_state]);

    return NonDeterministic(std::move(new_alphabet),
                         std::move(new_states),
                         std::move(new_transitions),
                         std::move(new_final_states),
                         std::move(new_initial_state));
}

Deterministic Deterministic::complete() const
{
    return Deterministic();
}

NonDeterministic Deterministic::remove_epsilon_transition() const
{
    return NonDeterministic();
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

bool Deterministic::is_complete() const
{
    return false;
}

bool Deterministic::contains_epsilon_transition() const
{
    return false;
}

bool Deterministic::operator==(const Deterministic & machine) const
{
    return m_alphabet      == machine.m_alphabet
        && m_states        == machine.m_states
        && m_transitions   == machine.m_transitions
        && m_final_states  == machine.m_final_states
        && m_initial_state == machine.m_initial_state;
}

/* ------------------- NonDeterministic -------------------------- */

NonDeterministic::NonDeterministic(const Deterministic &machine) :
    m_alphabet(machine.m_alphabet),
    m_states(machine.m_states),
    m_final_states(machine.m_final_states),
    m_initial_state(machine.m_initial_state)
{
    for (auto trans : Deterministic::transition_map_type(machine.m_transitions))
        for (auto target : trans.second)
            m_transitions[trans.first][target.first].insert(target.second);
}

NonDeterministic NonDeterministic::operator!() const
{
    symbol_set_type     new_alphabet      = m_alphabet;
    state_set_type      new_states        = m_states;
    transition_map_type new_transitions   = m_transitions;
    state_set_type      new_final_states;
    state_type          new_initial_state = m_initial_state;

   state_type error;

   new_states.insert(error);

   for (auto symbol : m_alphabet)
       new_transitions[error][symbol].insert(error);

   for (auto state : m_states)
       for (auto symbol : m_alphabet)
           if (new_transitions[state][symbol].empty())
               new_transitions[state][symbol].insert(error);

   auto not_final = m_final_states.end();

   for(auto state : m_states)
       if (m_final_states.find(state) == not_final)
           new_final_states.insert(state);

   new_final_states.insert(error);

   return NonDeterministic(std::move(new_alphabet),
                           std::move(new_states),
                           std::move(new_transitions),
                           std::move(new_final_states),
                           std::move(new_initial_state));
}

NonDeterministic NonDeterministic::operator|(const NonDeterministic & machine) const
{
    NonDeterministic::symbol_set_type     new_alphabet;
    NonDeterministic::state_set_type      new_states;
    NonDeterministic::transition_map_type new_transitions;
    NonDeterministic::state_set_type      new_final_states;
    NonDeterministic::map_type<state_type, state_type> state_map_m1, state_map_m2;

    /* ------ New initial state ------ */

    NonDeterministic::state_type new_initial_state("q0");
    new_states.insert(new_initial_state);

    /* ------ New alphabet ------ */

    new_alphabet = m_alphabet;

    for (auto symbol : machine.m_alphabet)
        new_alphabet.insert(symbol);


    /* ------ New states ------ */

    int i = 1;
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

    /* ------ New transitions ------ */

    for (auto trans : NonDeterministic::transition_map_type(m_transitions))
        for (auto target : trans.second)
            for (auto state_target : target.second)
                new_transitions[state_map_m1[trans.first]][target.first].insert(state_map_m1[state_target]);

    for (auto trans : NonDeterministic::transition_map_type(machine.m_transitions))
        for (auto target : trans.second)
            for (auto state_target : target.second)
                new_transitions[state_map_m2[trans.first]][target.first].insert(state_map_m2[state_target]);

    /* ------ New final states ------ */

    for (auto state : m_final_states)
        new_final_states.insert(state_map_m1[state]);

    for (auto state : machine.m_final_states)
        new_final_states.insert(state_map_m2[state]);

    /* ------ Transitions of new initial state ------ */

    NonDeterministic::transition_map_type copy = m_transitions;
    for (auto target : copy[m_initial_state])
        for (auto state_target : target.second)
            new_transitions[new_initial_state][target.first].insert(state_map_m1[state_target]);

    copy = machine.m_transitions;
    for (auto target : copy[machine.m_initial_state])
        for (auto state_target : target.second)
            new_transitions[new_initial_state][target.first].insert(state_map_m2[state_target]);

    /* ------ Checks if new initial state is a final state ------ */

    if (m_final_states.find(m_initial_state) != m_final_states.end() ||
        machine.m_final_states.find(machine.m_initial_state) != machine.m_final_states.end())
        new_final_states.insert(new_initial_state);

    return NonDeterministic(std::move(new_alphabet),
                            std::move(new_states),
                            std::move(new_transitions),
                            std::move(new_final_states),
                            std::move(new_initial_state));
}

NonDeterministic NonDeterministic::operator+(const NonDeterministic & machine) const
{
    NonDeterministic::symbol_set_type     new_alphabet;
    NonDeterministic::state_set_type      new_states;
    NonDeterministic::transition_map_type new_transitions;
    NonDeterministic::state_set_type      new_final_states;

    NonDeterministic::map_type<state_type, state_type> state_map_m1, state_map_m2;

    /* ------ New initial state ------ */

    NonDeterministic::state_type new_initial_state("q0");
    state_map_m1[m_initial_state] = new_initial_state;

    new_states.insert(new_initial_state);

    /* ------ New alphabet ------ */

    new_alphabet = m_alphabet;

    for (auto symbol : machine.m_alphabet)
        new_alphabet.insert(symbol);

    /* ------ New states ------ */

    int i = 1;
    for (auto state : m_states) {
        if (state == m_initial_state)
            continue;

        state_type q{ "q" + std::to_string(i++) };
        state_map_m1[state] = q;
        new_states.insert(q);
    }

    for (auto state : machine.m_states) {
        state_type q{ "q" + std::to_string(i++) };
        state_map_m2[state] = q;
        new_states.insert(q);
    }

    /* ------ New transitions ------ */

    for (auto trans : NonDeterministic::transition_map_type(m_transitions))
        for (auto target : trans.second)
            for (auto state_target : target.second)
                new_transitions[state_map_m1[trans.first]][target.first].insert(state_map_m1[state_target]);

    for (auto trans : NonDeterministic::transition_map_type(machine.m_transitions))
        for (auto target : trans.second)
            for (auto state_target : target.second)
                new_transitions[state_map_m2[trans.first]][target.first].insert(state_map_m2[state_target]);

    /* ------ Transitions of final states of M1 to initial state of M2 ------ */

    for (auto f : m_final_states)
    {
        auto final_state = state_map_m1[f];
        NonDeterministic::transition_map_type copy = new_transitions;

        for (auto target : copy[state_map_m2[machine.m_initial_state]])
            for (auto target_state : target.second)
                new_transitions[final_state][target.first].insert(target_state);
    }

    /* ------ New final states ------ */

    if (machine.m_final_states.find(machine.m_initial_state) != machine.m_final_states.end())
        for (auto state : m_final_states)
            new_final_states.insert(state_map_m1[state]);

    for (auto state : machine.m_final_states)
        new_final_states.insert(state_map_m2[state]);

    return NonDeterministic(std::move(new_alphabet),
                            std::move(new_states),
                            std::move(new_transitions),
                            std::move(new_final_states),
                            std::move(new_initial_state));
}

NonDeterministic NonDeterministic::operator&(const NonDeterministic & machine) const
{
    return NonDeterministic();
}

NonDeterministic NonDeterministic::operator-(const NonDeterministic & machine) const
{
    return NonDeterministic();
}

NonDeterministic NonDeterministic::operator^(const Operation & op) const
{
    return NonDeterministic();
}

bool NonDeterministic::operator==(const NonDeterministic & machine) const
{
    return m_alphabet      == machine.m_alphabet
        && m_states        == machine.m_states
        && m_transitions   == machine.m_transitions
        && m_final_states  == machine.m_final_states
        && m_initial_state == machine.m_initial_state;
}

NonDeterministic NonDeterministic::reflexive() const
{
    return NonDeterministic();
}

NonDeterministic NonDeterministic::transitive() const
{
    return NonDeterministic();
}

NonDeterministic NonDeterministic::optional() const
{
    return NonDeterministic();
}

NonDeterministic NonDeterministic::reverse() const
{
    return NonDeterministic();
}

}  // namespace finite_automaton
}  // namespace formal_device

