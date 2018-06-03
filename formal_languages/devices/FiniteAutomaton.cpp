#include "FiniteAutomaton.hpp"

namespace formal_device
{
namespace finite_automaton
{

Deterministic::Deterministic(const symbol_set_type& alphabet) :
    m_alphabet(alphabet)
{
    for (auto symbol : m_alphabet)
        m_transitions[m_initial_state][symbol] = m_initial_state;
}

Deterministic::Deterministic(symbol_set_type&& alphabet) :
    m_alphabet(std::move(alphabet))
{
    for (auto symbol : m_alphabet)
        m_transitions[m_initial_state][symbol] = m_initial_state;
}

const Deterministic::symbol_set_type& Deterministic::alphabet() const
{
    return m_alphabet;
}

const Deterministic::state_set_type& Deterministic::states() const
{
    return m_states;
}

const Deterministic::transition_map_type& Deterministic::transitions() const
{
    return m_transitions;
}

const Deterministic::state_set_type& Deterministic::final_states() const
{
    return m_final_states;
}

const Deterministic::state_type& Deterministic::initial_state() const
{
    return m_initial_state;
}

Deterministic Deterministic::operator!() const
{
    Deterministic::state_set_type new_final_states;

    Deterministic complement = complete();

    auto not_final = complement.m_final_states.end();

    for(auto state : complement.m_states)
        if (complement.m_final_states.find(state) == not_final)
            new_final_states.insert(state);

    complement.m_final_states = new_final_states;

    state_type error;

    //! If the error state belonged to the M1 in the final states,
    //! at !M1 It should be Implicit and not explicit.
    if (complement.m_final_states.find(error) == complement.m_final_states.end())
    {
        complement.m_states.erase(error);
        for (auto state : complement.m_states)
            for (auto symbol : complement.m_alphabet)
                if (complement.m_transitions[state][symbol] == error)
                    complement.m_transitions[state].erase(symbol);
        complement.m_transitions.erase(error);
    }

    return complement;
}

NonDeterministic Deterministic::operator|(const Deterministic &machine) const
{
    return NonDeterministic(*this) | NonDeterministic(machine);
}

NonDeterministic Deterministic::operator+(const Deterministic &machine) const
{
    return NonDeterministic(*this) + NonDeterministic(machine);
}

Deterministic Deterministic::operator&(const Deterministic &machine) const
{
    return ! ( !*this | !machine );
}

Deterministic Deterministic::operator-(const Deterministic &machine) const
{
    return *this & !machine;
}

NonDeterministic Deterministic::operator^(const Operation &op) const
{
    return NonDeterministic(*this)^op;
}

bool Deterministic::operator==(const Deterministic & machine) const
{
    return m_alphabet      == machine.m_alphabet
        && m_states        == machine.m_states
        && m_transitions   == machine.m_transitions
        && m_final_states  == machine.m_final_states
        && m_initial_state == machine.m_initial_state;
}

Deterministic Deterministic::complete() const
{
    if (is_complete())
        return *this;

    symbol_set_type     new_alphabet = m_alphabet;
    state_set_type      new_states = m_states;
    transition_map_type new_transitions = m_transitions;
    state_set_type      new_final_states = m_final_states;
    state_type          new_initial_state = m_initial_state;

    new_states.insert(state_type("Error"));

    //! If the transition was implicit (did not exist), for the error state,
    //! it is now explicit by creating the error state by default.
    for (auto state : new_states)
        for (auto symbol : new_alphabet)
            new_transitions[state][symbol];

    return Deterministic(std::move(new_alphabet),
                         std::move(new_states),
                         std::move(new_transitions),
                         std::move(new_final_states),
                         std::move(new_initial_state));
}

Deterministic Deterministic::minimization() const
{
    Deterministic assistant = remove_unreachable_states();
    assistant = assistant.remove_dead_states();

    symbol_set_type     new_alphabet = assistant.m_alphabet;
    state_set_type      new_states;
    transition_map_type new_transitions;
    state_set_type      new_final_states;

    /* ------ Defines equivalence classes ------- */

    state_set_type not_final_states;
    state_set_type final_states = assistant.m_final_states;

    for (auto state : assistant.m_states)
        if (final_states.find(state) == final_states.end())
            not_final_states.insert(state);

    not_final_states.insert(state_type("Error"));

    set_type<state_set_type> equivalent_classes{not_final_states};
    if (!final_states.empty())
        equivalent_classes.insert(final_states);

    auto complet = assistant.complete();

    complet.equivalence_classes(equivalent_classes);

    /* ------ New initial state ------ */

    Deterministic::state_type new_initial_state;

    map_type<state_set_type, state_type> class_to_new_state;
    map_type<state_type, state_set_type> old_state_to_class;

    int i = 1;
    for (auto set : equivalent_classes)
    {
        if(set.find(state_type("Error")) != set.end())
            continue;

        if (set.find(complet.m_initial_state) != set.end())
        {
            new_initial_state = state_type("q0");
            class_to_new_state[set] = new_initial_state;
        }
        else
        {
            state_type q{ "q" + std::to_string(i++) };
            class_to_new_state[set] = q;
        }

        new_states.insert(class_to_new_state[set]);

        for (auto state : set)
        {
            old_state_to_class[state] = set;
            if (complet.m_final_states.find(state) != complet.m_final_states.end())
                new_final_states.insert(class_to_new_state[old_state_to_class[state]]);
        }
    }

    /* ------ New states and New transitions ------ */

    for (auto set : equivalent_classes)
    {
        auto state = *set.begin();

        for (auto trans : complet.m_transitions[state])
            if (!(trans.second == "Error"))
                new_transitions[ class_to_new_state[ old_state_to_class[state] ] ][trans.first]
                        = class_to_new_state[old_state_to_class[trans.second]];
    }

    if (new_states.empty())
    {
        new_initial_state = state_type("q0");
        new_states.insert(new_initial_state);

        for (auto symbol : new_alphabet)
            new_transitions[new_initial_state][symbol] = new_initial_state;
    }

    return Deterministic(std::move(new_alphabet),
                         std::move(new_states),
                         std::move(new_transitions),
                         std::move(new_final_states),
                         std::move(new_initial_state));
}

Deterministic Deterministic::remove_dead_states() const
{
    symbol_set_type     new_alphabet = m_alphabet;
    state_set_type      new_states;
    transition_map_type new_transitions;
    state_set_type      new_final_states = m_final_states;

    NonDeterministic::transition_map_type inverted_transitions;

    for (auto state : m_states)
    {
        transition_map_type transitions(m_transitions);
        for (auto trans : transitions[state])
            inverted_transitions[trans.second][trans.first].insert(state);
    }

    std::deque<state_type> reachable(m_final_states.begin(), m_final_states.end());

    while (!reachable.empty())
    {
        auto current = reachable.front();
        reachable.pop_front();

        new_states.insert(current);

        for (auto trans : inverted_transitions[current])
            for (auto target_state : trans.second)
            {
                if (new_states.find(target_state) == new_states.end())
                    reachable.push_back(target_state);

                new_transitions[target_state][trans.first] = current;
            }
    }

    if (new_states.find(m_initial_state) == new_states.end())
        return Deterministic(std::move(new_alphabet)); //! Empty language
    else
        return Deterministic(std::move(new_alphabet),
                             std::move(new_states),
                             std::move(new_transitions),
                             std::move(new_final_states),
                             m_initial_state);
}

Deterministic Deterministic::remove_unreachable_states() const
{
    symbol_set_type     new_alphabet{m_alphabet};
    state_set_type      new_states{m_initial_state};
    transition_map_type new_transitions;
    state_set_type      new_final_states;
    state_type          new_initial_state{m_initial_state};

    std::deque<state_type> reachable{new_initial_state};
    state_set_type marked;

    while (!reachable.empty())
    {
        auto current = reachable.front();
        reachable.pop_front();

        marked.insert(current);

        if (m_final_states.find(current) != m_final_states.end())
            new_final_states.insert(current);

        transition_map_type trans_copy(m_transitions);
        if (trans_copy.find(current) != trans_copy.end())
            new_transitions[current] = trans_copy[current];
        else
            continue;

        for (auto trans : trans_copy[current])
            if (marked.find(trans.second) == marked.end())
            {
                reachable.push_back(trans.second);
                new_states.insert(trans.second);
            }
    }

    return Deterministic(std::move(new_alphabet),
                         std::move(new_states),
                         std::move(new_transitions),
                         std::move(new_final_states),
                         std::move(new_initial_state));
}

Deterministic Deterministic::remove_epsilon_transition() const
{
    return NonDeterministic(*this).determination();
}

void Deterministic::equivalence_classes(set_type<state_set_type> & set) const
{
    set_type<state_set_type> aux_set;

    for (auto equivalent_class : set)
    {
        state_set_type equal;
        state_set_type not_equal;

        auto first_state = *equivalent_class.begin();
        equal.insert(first_state);

        for (auto state : equivalent_class)
        {
            if (first_state == state)
                continue;

            bool different = false;
            for (auto symbol : m_alphabet)
            {
                transition_map_type trans(m_transitions);
                auto target_first = trans[first_state][symbol];
                auto target_state = trans[state][symbol];

                if (target_first == target_state)
                    continue;

                for (auto eq_class : set)
                    different |= (eq_class.find(target_first) != eq_class.end()) ^ (eq_class.find(target_state) != eq_class.end());

                if (different)
                    break;
            }

            if (different)
                not_equal.insert(state);
            else
                equal.insert(state);
        }

        aux_set.insert(equal);
        if (!not_equal.empty())
            aux_set.insert(not_equal);
    }

    if (aux_set != set)
    {
        set = aux_set;
        equivalence_classes(set);
    }
}

bool Deterministic::membership(const string_type &sentence) const
{
    auto machine = contains_epsilon_transition()?
                remove_epsilon_transition().complete() : complete();

    auto current = machine.m_initial_state;

    if (sentence != "&")
        for (auto symbol : sentence)
        {
            string_type caracter(&symbol, (&symbol)+1);
            current = machine.m_transitions[current][caracter];
        }

    return machine.m_final_states.find(current) != machine.m_final_states.end();
}

bool Deterministic::emptiness() const
{
    return minimization() == Deterministic(m_alphabet);
}

bool Deterministic::finiteness() const
{
    auto minimum = minimization();

    if (minimum.m_final_states.empty())
        return true;

    state_set_type temporary;
    state_set_type permanent;
    
    return !minimum.contains_cycle(minimum.m_initial_state, temporary, permanent);
}

bool Deterministic::contains_cycle(state_type state, state_set_type & temporary, state_set_type & permanent)
{
    if (permanent.find(state) != permanent.end())
        return false;

    if (temporary.find(state) != temporary.end())
        return true;

    temporary.insert(state);

    transition_map_type trans_copy(m_transitions);
    for (auto trans : trans_copy[state])
        if (contains_cycle(trans.second, temporary, permanent))
            return true;

    temporary.erase(state);
    permanent.insert(state);

    return false;
}

bool Deterministic::containment(const Deterministic &machine) const
{
    return (machine - *this).emptiness();
}

bool Deterministic::equivalence(const Deterministic &machine) const
{
    return containment(machine) && machine.containment(*this);
}

bool Deterministic::is_complete() const
{
    int symbol_amount = m_alphabet.size();

    transition_map_type trans(m_transitions);
    for (auto state : m_states)
        if (trans[state].size() != symbol_amount)
            return false;

    return true;
}

bool Deterministic::contains_epsilon_transition() const
{
    return m_alphabet.find(symbol_type("&")) != m_alphabet.end();
}

Deterministic::string_type Deterministic::to_string() const
{
    string_type string{"   +   "};

    for (auto symbol : m_alphabet)
        string += "|   " + symbol.value() + "   ";

    string += "\n";

    for (auto state : m_states)
    {
        if (m_final_states.find(state) != m_final_states.end())
            string += "*";
        else
            string += " ";

        if (state == m_initial_state)
            string += "->" + state.value();
        else
            string += "  " + state.value();

        for (int i = 4 - state.value().size(); i > 0; --i)
            string += " ";

        auto trans{m_transitions};
        for (auto symbol : m_alphabet)
        {
            string += "|   ";
            auto target = trans[state][symbol];

            if (target == "Error")
                string += "-   ";
            else
            {
                string += target.value();
                for (int i = 4 - state.value().size(); i > 0; --i)
                    string += " ";
            }
        }

        string += "\n";
    }

    return string;
}

/* --------------------------------------------------------------- */
/* ------------------- NonDeterministic -------------------------- */
/* --------------------------------------------------------------- */

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

NonDeterministic::NonDeterministic(const symbol_set_type& alphabet)
{
    *this = Deterministic(alphabet);
}

NonDeterministic::NonDeterministic(symbol_set_type&& alphabet)
{
    *this = Deterministic(std::move(alphabet));
}

const NonDeterministic::symbol_set_type& NonDeterministic::alphabet() const
{
    return m_alphabet;
}

const NonDeterministic::state_set_type& NonDeterministic::states() const
{
    return m_states;
}

const NonDeterministic::transition_map_type& NonDeterministic::transitions() const
{
    return m_transitions;
}

const NonDeterministic::state_set_type& NonDeterministic::final_states() const
{
    return m_final_states;
}

const NonDeterministic::state_type& NonDeterministic::initial_state() const
{
    return m_initial_state;
}

Deterministic NonDeterministic::operator!() const
{
    return !determination();
}

NonDeterministic NonDeterministic::operator|(const NonDeterministic & machine) const
{
    symbol_set_type     new_alphabet;
    state_set_type      new_states;
    transition_map_type new_transitions;
    state_set_type      new_final_states;

    map_type<state_type, state_type> state_map_m1, state_map_m2;

    /* ------ New initial state ------ */

    state_type new_initial_state("q0");
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

    bool contains_error = m_states.find(state_type()) != m_states.end();

    for (auto state : m_states)
        for (auto symbol : new_alphabet)
            if (m_alphabet.find(symbol) != m_alphabet.end())
            {
                transition_map_type trans(m_transitions);
                for (auto target_state : trans[state][symbol])
                    new_transitions[state_map_m1[state]][symbol].insert(state_map_m1[target_state]);
            } else {
                if (contains_error)
                    new_transitions[state_map_m1[state]][symbol].insert(state_map_m1[state_type()]);
            }

    contains_error = machine.m_states.find(state_type()) != machine.m_states.end();

    for (auto state : machine.m_states)
        for (auto symbol : new_alphabet)
            if (machine.m_alphabet.find(symbol) != machine.m_alphabet.end())
            {
                transition_map_type trans(machine.m_transitions);
                for (auto target_state : trans[state][symbol])
                    new_transitions[state_map_m2[state]][symbol].insert(state_map_m2[target_state]);
            } else {
                if (contains_error)
                    new_transitions[state_map_m2[state]][symbol].insert(state_map_m2[state_type()]);
            }

    /* ------ New final states ------ */

    for (auto state : m_final_states)
        new_final_states.insert(state_map_m1[state]);

    for (auto state : machine.m_final_states)
        new_final_states.insert(state_map_m2[state]);

    /* ------ Transitions of new initial state ------ */

    new_transitions[new_initial_state] = new_transitions[state_map_m1[m_initial_state]];
    transition_map_type trans{new_transitions};
    for (auto target : trans[state_map_m2[machine.m_initial_state]])
        for (auto target_state : target.second)
            new_transitions[new_initial_state][target.first].insert(target_state);

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
    symbol_set_type     new_alphabet;
    state_set_type      new_states;
    transition_map_type new_transitions;
    state_set_type      new_final_states;

    map_type<state_type, state_type> state_map_m1, state_map_m2;

    /* ------ New initial state ------ */

    state_type new_initial_state("q0");
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

    for (auto trans : transition_map_type(m_transitions))
        for (auto target : trans.second)
            for (auto target_state : target.second)
                new_transitions[state_map_m1[trans.first]][target.first].insert(state_map_m1[target_state]);

    for (auto trans : transition_map_type(machine.m_transitions))
        for (auto target : trans.second)
            for (auto target_state : target.second)
                new_transitions[state_map_m2[trans.first]][target.first].insert(state_map_m2[target_state]);

    /* ------ Transitions of final states of M1 to initial state of M2 ------ */

    for (auto f : m_final_states)
    {
        auto final_state = state_map_m1[f];
        transition_map_type trans{new_transitions};

        for (auto target : trans[state_map_m2[machine.m_initial_state]])
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

Deterministic NonDeterministic::operator&(const NonDeterministic & machine) const
{
    return determination() & machine.determination();
}

Deterministic NonDeterministic::operator-(const NonDeterministic & machine) const
{
    return *this & !machine;
}

NonDeterministic NonDeterministic::operator^(const Operation & op) const
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
    symbol_set_type     new_alphabet = m_alphabet;
    state_set_type      new_states = m_states;
    state_set_type      new_final_states = m_final_states;
    transition_map_type new_transitions = m_transitions;
    state_type          new_initial_state = m_initial_state;

    /* ------ Copy of transitions from initial states to final states ------ */

    for (auto final_state : m_final_states)
    {
        transition_map_type trans = new_transitions;

        for (auto target : trans[m_initial_state])
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

NonDeterministic NonDeterministic::transitive() const
{
    return *this + ((*this)^Operation::Reflexive);
}

NonDeterministic NonDeterministic::optional() const
{
    state_type          new_initial_state{"q0"};
    symbol_set_type     new_alphabet;
    state_set_type      new_states{new_initial_state};
    transition_map_type new_transitions;
    state_set_type      new_final_states{new_initial_state};

    return *this | NonDeterministic(std::move(new_alphabet),
                                    std::move(new_states),
                                    std::move(new_transitions),
                                    std::move(new_final_states),
                                    std::move(new_initial_state));
}

NonDeterministic NonDeterministic::reverse() const
{
    symbol_set_type     new_alphabet{m_alphabet};
    state_set_type      new_final_states;
    transition_map_type new_transitions;
    state_set_type      new_states;

    map_type<state_type, state_type> state_map;

    /* ------ New initial state ------ */

    state_type new_initial_state("q0");

    new_states.insert(new_initial_state);

    /* ------ New states ------ */

    int i = 1;
    for (auto state : m_states) {
        state_type q{ "q" + std::to_string(i++) };
        state_map[state] = q;
        new_states.insert(q);
    }

    /* ------ New transitions ------ */

    for (auto trans : transition_map_type(m_transitions))
        for (auto target : trans.second)
            for (auto target_state : target.second)
                new_transitions[state_map[target_state]][target.first].insert(state_map[trans.first]);

    /* ------ Copy of transitions from old final states to new initial state ------ */

    for (auto f : m_final_states)
    {
        auto final_state = state_map[f];

        transition_map_type trans(new_transitions);
        for (auto target : trans[final_state])
            for (auto target_state : target.second)
                new_transitions[new_initial_state][target.first].insert(target_state);
    }

    /* ------ New final states ------ */

    new_final_states.insert(state_map[m_initial_state]);

    if (m_final_states.find(m_initial_state) != m_final_states.end())
        new_final_states.insert(new_initial_state);

    return NonDeterministic(std::move(new_alphabet),
                            std::move(new_states),
                            std::move(new_transitions),
                            std::move(new_final_states),
                            std::move(new_initial_state));
}

Deterministic NonDeterministic::determination() const
{
    using map_of_states_set_type = std::map<state_set_type, state_type>;
    using deque_of_states_set_type = std::deque<state_set_type>;
    using vector_of_states_set_type = std::vector<state_set_type>;

    // Se contém '&' transição => elimina '&' transição;

    NonDeterministic current_machine = contains_epsilon_transition()?
                                       remove_epsilon() : *this;

    Deterministic::symbol_set_type     new_alphabet = current_machine.m_alphabet;
    Deterministic::state_set_type      new_final_states;
    Deterministic::transition_map_type new_transitions;
    Deterministic::state_set_type      new_states;

    map_of_states_set_type new_states_map;
    deque_of_states_set_type queue;
    vector_of_states_set_type created_sets;

    /* ------ New initial state ------ */

    Deterministic::state_type new_initial_state("q0");
    NonDeterministic::state_set_type initial_set{current_machine.m_initial_state};

    new_states_map[initial_set] = new_initial_state;
    new_states.insert(new_initial_state);

    queue.push_back(initial_set);
    created_sets.push_back(initial_set);

    /* ------ New states and New transitions ------ */

    int i = 1;
    while (!queue.empty())
    {
        auto current_set = queue.front();
        queue.pop_front();

        for (auto symbol : current_machine.m_alphabet)
        {
            state_set_type target_set;

            for (auto state : current_set)
            {
                transition_map_type trans(current_machine.m_transitions);
                for (auto target_state : trans[state][symbol])
                    target_set.insert(target_state);
            }

            if (target_set.empty())
                continue;

            if (new_states_map[target_set] == "Error")
            {
                state_type q{ "q" + std::to_string(i++) };
                new_states_map[target_set] = q;
                new_states.insert(q);

                queue.push_back(target_set);
                created_sets.push_back(target_set);
            }

            new_transitions[new_states_map[current_set]][symbol] = new_states_map[target_set];
        }
    }

    /* ------ New final states ------ */

    for (auto set : created_sets)
        for (auto state : set)
            if (current_machine.m_final_states.find(state) != current_machine.m_final_states.end())
                new_final_states.insert(new_states_map[set]);

    return Deterministic(std::move(new_alphabet),
                         std::move(new_states),
                         std::move(new_transitions),
                         std::move(new_final_states),
                         std::move(new_initial_state));
}

Deterministic NonDeterministic::minimization() const
{
    return determination().minimization();
}

Deterministic NonDeterministic::remove_epsilon() const
{
    if (!contains_epsilon_transition())
        return determination();

    using map_of_states_set_type = std::map<state_set_type, state_type>;
    using state_to_states_set_type = std::map<state_type, state_set_type>;
    using deque_of_states_set_type = std::deque<state_set_type>;
    using vector_of_states_set_type = std::vector<state_set_type>;

    Deterministic::symbol_set_type     new_alphabet;
    Deterministic::state_set_type      new_final_states;
    Deterministic::transition_map_type new_transitions;
    Deterministic::state_set_type      new_states;

    for (auto symbol : m_alphabet)
        if (!(symbol == "&"))
            new_alphabet.insert(symbol);


    /* ------ Parcial Epsilon Closure ------ */

    state_to_states_set_type epsilon_closure;

    for (auto state : state_set_type(m_states))
    {
        state_set_type set;
        build_closure(set, state);
        epsilon_closure[state] = set;
    }

    /* ------ Determination ------ */

    map_of_states_set_type new_states_map;
    deque_of_states_set_type queue;
    vector_of_states_set_type created_sets;

    /* ------ New initial state ------ */

    Deterministic::state_type new_initial_state("q0");
    state_set_type initial_set{epsilon_closure[m_initial_state]};

    new_states_map[initial_set] = new_initial_state;
    new_states.insert(new_initial_state);

    queue.push_back(initial_set);
    created_sets.push_back(initial_set);

    /* ------ New states and New transitions ------ */

    int i = 1;
    while (!queue.empty())
    {
        auto current_set = queue.front();
        queue.pop_front();

        for (auto symbol : m_alphabet)
        {
            if (symbol == "&")
                continue;

            state_set_type target_set;

            for (auto state : current_set)
            {
                transition_map_type trans(m_transitions);
                for (auto target_state : trans[state][symbol])
                {
                    target_set.insert(target_state);

                    for (auto epsilon_state : epsilon_closure[target_state])
                        target_set.insert(epsilon_state);
                }
            }

            if (target_set.empty())
                continue;

            if (new_states_map[target_set] == "Error")
            {
                state_type q{ "q" + std::to_string(i++) };
                new_states_map[target_set] = q;
                new_states.insert(q);

                queue.push_back(target_set);
                created_sets.push_back(target_set);
            }

            new_transitions[new_states_map[current_set]][symbol] = new_states_map[target_set];
        }
    }

    /* ------ New final states ------ */

    for (auto set : created_sets)
        for (auto state : set)
            if (m_final_states.find(state) != m_final_states.end())
                new_final_states.insert(new_states_map[set]);

    return Deterministic(std::move(new_alphabet),
                         std::move(new_states),
                         std::move(new_transitions),
                         std::move(new_final_states),
                         std::move(new_initial_state));
}

void NonDeterministic::build_closure(state_set_type& set, state_type state) const
{
    if (set.find(state) == set.end())
        set.insert(state);

    transition_map_type trans(m_transitions);
    for (auto target_state : trans[state][symbol_type("&")])
        if (set.find(target_state) == set.end())
            build_closure(set, target_state);
}

bool NonDeterministic::membership(const string_type& sentence) const
{
    return determination().membership(sentence);
}

bool NonDeterministic::emptiness() const
{
    return determination().emptiness();
}
bool NonDeterministic::finiteness() const
{
    return determination().finiteness();
}
bool NonDeterministic::containment(const NonDeterministic & machine) const
{
    return determination().containment(machine.determination());
}
bool NonDeterministic::equivalence(const NonDeterministic & machine) const
{
    return determination().equivalence(machine.determination());
}

bool NonDeterministic::contains_epsilon_transition() const
{
    return m_alphabet.find(symbol_type("&")) != m_alphabet.end();
}

NonDeterministic::string_type NonDeterministic::to_string() const
{
    string_type string{"   +   "};

    for (auto symbol : m_alphabet)
        string += "|   " + symbol.value() + "   ";

    string += "\n";

    for (auto state : m_states)
    {
        if (m_final_states.find(state) != m_final_states.end())
            string += "*";
        else
            string += " ";

        if (state == m_initial_state)
            string += "->" + state.value();
        else
            string += "  " + state.value();

        for (int i = 4 - state.value().size(); i > 0; --i)
            string += " ";

        auto trans{m_transitions};
        for (auto symbol : m_alphabet)
        {
            auto target_set = trans[state][symbol];

            if (target_set.empty())
                string += "|   -   ";
            else
            {
                string += "|{" + target_set.begin()->value();

                for (auto target_state : target_set)
                {
                    if (target_state == (*target_set.begin()))
                        continue;

                    string += ", " + target_state.value();
                }

                string += "}";
            }
        }

        string += "\n";
    }

    return string;
}

}  // namespace finite_automaton
}  // namespace formal_device

