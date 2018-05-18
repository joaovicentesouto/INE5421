#include "../catch.hpp"

#include <formal_languages/devices/FiniteAutomaton.hpp>

using namespace formal_device::finite_automaton;

using state_type          = Deterministic::state_type;
using symbol_type         = Deterministic::symbol_type;
using state_set_type      = Deterministic::state_set_type;
using symbol_set_type     = Deterministic::symbol_set_type;
using det_transition_map_type     = Deterministic::transition_map_type;
using non_det_transition_map_type = NonDeterministic::transition_map_type;

TEST_CASE("Finite Automaton: Complement Deterministic", "[finite_automaton][symbol]")
{
    symbol_type a("a");
    symbol_type b("b");
    state_type q0("q0"), q1("q1"), q2("q2"), q3("q3");

    symbol_set_type alphabet{a, b};
    state_set_type  states{q0, q1, q2, q3};
    state_set_type  final_states{q1, q2};

    det_transition_map_type transitions;
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

        det_transition_map_type transitions;
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

    det_transition_map_type m1_transitions;
    m1_transitions[q0][a] = q1;

    det_transition_map_type m2_transitions;
    m2_transitions[q0][b] = q1;

    Deterministic m1(m1_alphabet, states, m1_transitions, final_states, q0);
    Deterministic m2(m2_alphabet, states, m2_transitions, final_states, q0);

    SECTION("Union", "[finite_automaton][fa]")
    {
        symbol_type a("a");
        symbol_type b("b");
        state_type q0("q0"), q1("q1"), q2("q2"), q3("q3"), q4("q4");

        symbol_set_type alphabet{a, b};
        state_set_type  states{q0, q1, q2, q3, q4};
        state_set_type  final_states{q1, q3};

        non_det_transition_map_type transitions;
        transitions[q0][a].insert(q1);
        transitions[q0][b].insert(q3);
        transitions[q2][a].insert(q1);
        transitions[q4][b].insert(q3);

        NonDeterministic union_(alphabet, states, transitions, final_states, q0);

        CHECK(((m1 | m2) == union_));
    }
}

TEST_CASE("Finite Automaton: Concatenation", "[finite_automaton][symbol]")
{
    SECTION("Concatenation 1", "[finite_automaton][fa]")
    {
        symbol_type a("a");
        symbol_type b("b");
        state_type q0("q0"), q1("q1");

        symbol_set_type m1_alphabet{a};
        symbol_set_type m2_alphabet{b};

        state_set_type  states{q0, q1};
        state_set_type  final_states{q1};

        det_transition_map_type m1_transitions;
        m1_transitions[q0][a] = q1;

        det_transition_map_type m2_transitions;
        m2_transitions[q0][b] = q1;

        Deterministic m1(m1_alphabet, states, m1_transitions, final_states, q0);
        Deterministic m2(m2_alphabet, states, m2_transitions, final_states, q0);

        state_type q2("q2"), q3("q3");

        symbol_set_type alphabet_m3{a, b};
        state_set_type  states_m3{q0, q1, q2, q3};
        state_set_type  final_states_m3{q2};

        non_det_transition_map_type transitions_m3;
        transitions_m3[q0][a].insert(q1);
        transitions_m3[q1][b].insert(q2);
        transitions_m3[q3][b].insert(q2);

        NonDeterministic concat(alphabet_m3, states_m3, transitions_m3, final_states_m3, q0);

        CHECK(((m1 + m2) == concat));
    }

    SECTION("Concatenation 2", "[finite_automaton][fa]")
    {
        symbol_type a("a");
        symbol_type b("b");
        state_type q0("q0"), q1("q1");

        symbol_set_type m1_alphabet{a};
        symbol_set_type m2_alphabet{b};

        state_set_type  states{q0, q1};
        state_set_type  final_states_m1{q1};
        state_set_type  final_states_m2{q0, q1};

        det_transition_map_type m1_transitions;
        m1_transitions[q0][a] = q1;

        det_transition_map_type m2_transitions;
        m2_transitions[q0][b] = q1;

        Deterministic m1(m1_alphabet, states, m1_transitions, final_states_m1, q0);
        Deterministic m2(m2_alphabet, states, m2_transitions, final_states_m2, q0);

        state_type q2("q2"), q3("q3");

        symbol_set_type alphabet_m3{a, b};
        state_set_type  states_m3{q0, q1, q2, q3};
        state_set_type  final_states_m3{q1, q2, q3};

        non_det_transition_map_type transitions_m3;
        transitions_m3[q0][a].insert(q1);
        transitions_m3[q1][b].insert(q2);
        transitions_m3[q3][b].insert(q2);

        NonDeterministic concat(alphabet_m3, states_m3, transitions_m3, final_states_m3, q0);

        CHECK(((m1 + m2) == concat));
    }
}

TEST_CASE("Finite Automaton: Operations", "[finite_automaton][symbol]")
{
    SECTION("Reflexive", "[finite_automaton][fa]")
    {
        symbol_type a("a");
        symbol_type b("b");
        state_type q0("q0"), q1("q1"), q2("q2");

        symbol_set_type alphabet{a, b};

        state_set_type  states{q0, q1, q2};
        state_set_type  final_states{q2};

        det_transition_map_type transitions;
        transitions[q0][a] = q1;
        transitions[q1][b] = q2;

        Deterministic machine(alphabet, states, transitions, final_states, q0);
        state_set_type  final_states_reflexive{q0, q2};

        non_det_transition_map_type transitions_reflexive;
        transitions_reflexive[q0][a].insert(q1);
        transitions_reflexive[q1][b].insert(q2);
        transitions_reflexive[q2][a].insert(q1);

        NonDeterministic reflexive(alphabet, states, transitions_reflexive, final_states_reflexive, q0);

         CHECK(((machine^Operation::Reflexive) == reflexive));
    }

    SECTION("Reverse", "[finite_automaton][fa]")
    {
        symbol_type a("0");
        symbol_type b("1");
        state_type q0("q0"), q1("q1"), q2("q2"), q3("q3");

        symbol_set_type alphabet{a, b};

        state_set_type  states{q0, q1, q2};
        state_set_type  final_states{q1};

        det_transition_map_type transitions;
        transitions[q0][a] = q1;
        transitions[q0][b] = q2;
        transitions[q1][a] = q1;
        transitions[q1][b] = q2;
        transitions[q2][a] = q1;
        transitions[q2][b] = q2;

        Deterministic machine(alphabet, states, transitions, final_states, q0);

        state_set_type  states_reverse{q0, q1, q2, q3};
        state_set_type  final_states_reverse{q2};

        non_det_transition_map_type transitions_reverse;
        transitions_reverse[q0][a].insert(q1);
        transitions_reverse[q0][a].insert(q2);
        transitions_reverse[q0][a].insert(q3);
        transitions_reverse[q1][b].insert(q1);
        transitions_reverse[q1][b].insert(q3);
        transitions_reverse[q1][b].insert(q2);
        transitions_reverse[q3][a].insert(q2);
        transitions_reverse[q3][a].insert(q1);
        transitions_reverse[q3][a].insert(q3);

        NonDeterministic reverse(alphabet, states_reverse, transitions_reverse, final_states_reverse, q0);

         CHECK(((machine^Operation::Reverse) == reverse));
    }
}

TEST_CASE("Finite Automaton: Complement NonDeterministic", "[finite_automaton][symbol]")
{
    symbol_type a("a");
    symbol_type b("b");
    state_type q0("q0"), q1("q1"), q2("q2"), q3("q3");

    symbol_set_type alphabet{a, b};
    state_set_type  states{q0, q1, q2, q3};
    state_set_type  final_states{q1, q2};

    non_det_transition_map_type transitions;
    transitions[q0][a].insert(q2);
    transitions[q0][b].insert(q1);
    transitions[q1][a].insert(q2);
    transitions[q2][a].insert(q0);
    transitions[q2][b].insert(q3);
    transitions[q3][a].insert(q0);

    state_type initial = q0;

    NonDeterministic machine(alphabet, states, transitions, final_states, initial);

    SECTION("Complement", "[finite_automaton][fa]")
    {
        symbol_type a("a");
        symbol_type b("b");
        state_type q0("q0"), q1("q1"), q2("q2"), q3("q3"), error("Error");

        symbol_set_type alphabet{a, b};
        state_set_type  states{q0, q1, q2, q3, error};
        state_set_type  final_states{q0, q3, error};

        non_det_transition_map_type transitions;
        transitions[q0][a].insert(q2);
        transitions[q0][b].insert(q1);
        transitions[q1][a].insert(q2);
        transitions[q1][b].insert(error);
        transitions[q2][a].insert(q0);
        transitions[q2][b].insert(q3);
        transitions[q3][a].insert(q0);
        transitions[q3][b].insert(error);
        transitions[error][a].insert(error);
        transitions[error][b].insert(error);

        state_type initial = q0;

        NonDeterministic complement(alphabet, states, transitions, final_states, initial);

        CHECK((!machine == complement));
    }
}

TEST_CASE("NonDeterministic: Determination", "[finite_automaton][symbol]")
{
    symbol_type a("a");
    symbol_type b("b");
    symbol_type c("c");
    state_type q0("q0"), q1("q1"), q2("q2");

    symbol_set_type alphabet{a, b, c};
    state_set_type  states{q0, q1, q2};
    state_set_type  final_states{q2};

    non_det_transition_map_type transitions;
    transitions[q0][a].insert(q0);
    transitions[q0][a].insert(q1);
    transitions[q0][b].insert(q0);
    transitions[q1][c].insert(q2);
    transitions[q2][c].insert(q2);

    NonDeterministic machine(alphabet, states, transitions, final_states, q0);

    SECTION("Determination", "[finite_automaton][fa]")
    {
        det_transition_map_type transitions_determination;
        transitions_determination[q0][a] = q1;
        transitions_determination[q0][b] = q0;
        transitions_determination[q1][a] = q1;
        transitions_determination[q1][b] = q0;
        transitions_determination[q1][c] = q2;
        transitions_determination[q2][c] = q2;

        Deterministic det(alphabet, states, transitions_determination, final_states, q0);

        CHECK((machine.determination() == det));
    }

    SECTION("Remove & transition", "[finite_automaton][fa]")
    {
        det_transition_map_type transitions_determination;
        transitions_determination[q0][a] = q1;
        transitions_determination[q0][b] = q0;
        transitions_determination[q1][a] = q1;
        transitions_determination[q1][b] = q0;
        transitions_determination[q1][c] = q2;
        transitions_determination[q2][c] = q2;

        Deterministic det(alphabet, states, transitions_determination, final_states, q0);

        CHECK((machine.remove_epsilon() == det));
    }
}

TEST_CASE("NonDeterministic: Remove & Epsilon", "[finite_automaton][symbol]")
{
    symbol_type a("a");
    symbol_type b("b");
    symbol_type epsilon("&");
    state_type q0("q0"), q1("q1"), q2("q2"), q3("q3"), q4("q4"), q5("q5");

    symbol_set_type alphabet{a, b, epsilon};
    state_set_type  states{q0, q1, q2, q3, q4, q5};
    state_set_type  final_states{q5};

    non_det_transition_map_type transitions;
    transitions[q0][epsilon].insert(q1);
    transitions[q0][epsilon].insert(q3);
    transitions[q1][a].insert(q2);
    transitions[q2][epsilon].insert(q5);
    transitions[q3][b].insert(q4);
    transitions[q4][epsilon].insert(q5);

    NonDeterministic machine(alphabet, states, transitions, final_states, q0);

    SECTION("Remove & transition", "[finite_automaton][fa]")
    {
        symbol_set_type alphabet_epsilon{a, b};
        state_set_type  states_epsilon{q0, q1, q2};
        state_set_type  final_states_epsilon{q1, q2};

        det_transition_map_type transitions_epsilon;
        transitions_epsilon[q0][a] = q1;
        transitions_epsilon[q0][b] = q2;

        Deterministic det(alphabet_epsilon, states_epsilon, transitions_epsilon, final_states_epsilon, q0);

        CHECK((machine.remove_epsilon() == det));
    }
}

TEST_CASE("Deterministic: Remove unreachable", "[finite_automaton][symbol]")
{
    symbol_type a("a");
    symbol_type b("b");
    symbol_type c("c");
    state_type q0("q0"), q1("q1"), q2("q2"), q3("q3"),
               q4("q4"), q5("q5"), q6("q6"), q7("q7"), q8("q8");

    symbol_set_type alphabet{a, b, c};
    state_set_type  states{q0, q1, q2, q3, q4, q5, q6, q7, q8};
    state_set_type  final_states{q2, q4, q8};

    det_transition_map_type transitions;
    transitions[q0][a] = q1;
    transitions[q0][b] = q3;
    transitions[q1][a] = q1;
    transitions[q1][b] = q5;
    transitions[q1][c] = q2;
    transitions[q3][a] = q0;
    transitions[q3][b] = q6;
    transitions[q3][c] = q4;
    transitions[q6][c] = q6;
    transitions[q7][b] = q8;

    Deterministic machine(alphabet, states, transitions, final_states, q0);

    state_set_type  states_r{q0, q1, q2, q3, q4, q5, q6};
    state_set_type  final_r{q2, q4};
    det_transition_map_type transitions_r;
    transitions_r[q0][a] = q1;
    transitions_r[q0][b] = q3;
    transitions_r[q1][a] = q1;
    transitions_r[q1][b] = q5;
    transitions_r[q1][c] = q2;
    transitions_r[q3][a] = q0;
    transitions_r[q3][b] = q6;
    transitions_r[q3][c] = q4;
    transitions_r[q6][c] = q6;

    Deterministic m_r(alphabet, states_r, transitions_r, final_r, q0);

    CHECK((machine.remove_unreachable_states() == m_r));

    SECTION("Remove dead states", "[finite_automaton][fa]")
    {
        state_set_type  states_alive{q0, q1, q2, q3, q4};
        state_set_type  final_alive{q2, q4};
        det_transition_map_type transitions_alive;
        transitions_alive[q0][a] = q1;
        transitions_alive[q0][b] = q3;
        transitions_alive[q1][a] = q1;
        transitions_alive[q1][c] = q2;
        transitions_alive[q3][a] = q0;
        transitions_alive[q3][c] = q4;

        Deterministic m_alive(alphabet, states_alive, transitions_alive, final_alive, q0);

        CHECK((machine.remove_unreachable_states().remove_dead_states() == m_alive));
    }
}

TEST_CASE("Deterministic: Remove dead states", "[finite_automaton][symbol]")
{
    symbol_type a("a");
    symbol_type b("b");
    symbol_type c("c");
    state_type q0("q0"), q1("q1"), q2("q2"), q3("q3"),
               q4("q4"), q5("q5"), q6("q6"), q7("q7"), q8("q8");

    symbol_set_type alphabet{a, b, c};
    state_set_type  states{q0, q1, q2, q3, q4, q5, q6, q7, q8};
    state_set_type  final_states{q2, q4, q8};

    det_transition_map_type transitions;
    transitions[q0][a] = q1;
    transitions[q0][b] = q3;
    transitions[q1][a] = q1;
    transitions[q1][b] = q5;
    transitions[q1][c] = q2;
    transitions[q3][a] = q0;
    transitions[q3][b] = q6;
    transitions[q3][c] = q4;
    transitions[q6][c] = q6;
    transitions[q7][b] = q8;

    Deterministic machine(alphabet, states, transitions, final_states, q0);

    state_set_type  states_alive{q0, q1, q2, q3, q4, q7, q8};
    state_set_type  final_alive{q2, q4, q8};
    det_transition_map_type transitions_alive;
    transitions_alive[q0][a] = q1;
    transitions_alive[q0][b] = q3;
    transitions_alive[q1][a] = q1;
    transitions_alive[q1][c] = q2;
    transitions_alive[q3][a] = q0;
    transitions_alive[q3][c] = q4;
    transitions_alive[q7][b] = q8;

    Deterministic m_alive(alphabet, states_alive, transitions_alive, final_alive, q0);

    CHECK((machine.remove_dead_states() == m_alive));
}
