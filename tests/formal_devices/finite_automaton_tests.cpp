#include "../catch.hpp"

#include <formal_languages/devices/FiniteAutomaton.hpp>

using namespace formal_device::finite_automaton;

using state_type          = Deterministic::state_type;
using symbol_type         = Deterministic::symbol_type;
using state_set_type      = Deterministic::state_set_type;
using symbol_set_type     = Deterministic::symbol_set_type;
using transition_map_type = Deterministic::transition_map_type;

TEST_CASE("Finite Automaton", "[finite_automaton][symbol]")
{
    symbol_type a("a");
    symbol_type b("b");
    state_type q0("q0"), q1("q1"), q2("q2"), q3("q3");

    symbol_set_type alphabet{a, b};
    state_set_type  states{q0, q1, q2, q3};
    state_set_type  final_states{q1, q2};

    transition_map_type transitions;
    transitions[q0][a] = q2;
    transitions[q0][b] = q1;
    transitions[q1][a] = q2;
    transitions[q2][a] = q0;
    transitions[q2][b] = q3;
    transitions[q3][a] = q0;

    state_type initial = q0;

    Deterministic machine(alphabet, states, transitions, final_states, initial);

    SECTION("Complement", "[finite_automaton][fa]")
    {
        symbol_type a("a");
        symbol_type b("b");
        state_type q0("q0"), q1("q1"), q2("q2"), q3("q3"), error("Error");

        symbol_set_type alphabet{a, b};
        state_set_type  states{q0, q1, q2, q3, error};
        state_set_type  final_states{q0, q3, error};

        transition_map_type transitions;
        transitions[q0][a] = q2;
        transitions[q0][b] = q1;
        transitions[q1][a] = q2;
        transitions[q1][b] = error;
        transitions[q2][a] = q0;
        transitions[q2][b] = q3;
        transitions[q3][a] = q0;
        transitions[q3][b] = error;
        transitions[error][a] = error;
        transitions[error][b] = error;

        state_type initial = q0;

        Deterministic complement(alphabet, states, transitions, final_states, initial);

        CHECK((!machine == complement));
    }
}

TEST_CASE("Finite Automaton: Union", "[finite_automaton][symbol]")
{
    symbol_type a("a");
    symbol_type b("b");
    state_type q0("q0"), q1("q1");

    symbol_set_type m1_alphabet{a};
    symbol_set_type m2_alphabet{b};

    state_set_type  states{q0, q1};
    state_set_type  final_states{q1};

    transition_map_type m1_transitions;
    m1_transitions[q0][a] = q1;

    transition_map_type m2_transitions;
    m2_transitions[q0][b] = q1;

    Deterministic m1(m1_alphabet, states, m1_transitions, final_states, q0);
    Deterministic m2(m2_alphabet, states, m2_transitions, final_states, q0);

    SECTION("Union", "[finite_automaton][fa]")
    {
        symbol_type a("a");
        symbol_type b("b");
        state_type q0q0("q0q0"), q0("q0"), q1("q1"), q0_M2("q0_M2"), q1_M2("q1_M2");

        symbol_set_type alphabet{a, b};
        state_set_type  states{q0q0, q0, q1, q0_M2, q1_M2};
        state_set_type  final_states{q1, q1_M2};

        NonDeterministic::transition_map_type transitions;
        transitions[q0q0][a].insert(q1);
        transitions[q0q0][b].insert(q1_M2);
        transitions[q0][a].insert(q1);
        transitions[q0_M2][b].insert(q1_M2);

        NonDeterministic union_(alphabet, states, transitions, final_states, q0q0);

        CHECK(((m1 | m2) == union_));
    }
}
