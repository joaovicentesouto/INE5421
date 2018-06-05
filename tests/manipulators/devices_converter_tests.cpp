//! João Vicente Souto e Bruno Izaias Bonotto

#include "../catch.hpp"

#include <formal_languages/manipulators/DevicesConverter.hpp>

using namespace formal_device;

TEST_CASE("Devices manipulator: Grammar to NDFA", "[expression][parser]")
{
    grammar::Regular::symbol_type S("S"), A("A"), B("B"), C("C"), a("a"), b("b");
    grammar::Regular::vocabulary_set_type vn{S, A, B, C}, vt{a, b};

    grammar::Regular::production_type_ptr p1(new grammar::NonTerminalProduction(a, A)),
                                 p2(new grammar::NonTerminalProduction(b, B)),
                                 p3(new grammar::NonTerminalProduction(a, S)),
                                 p4(new grammar::NonTerminalProduction(b, C)),
                                 p5(new grammar::TerminalProduction(a));

    grammar::Regular::production_map_type productions;
    productions[S] = {p1, p5, p2};
    productions[A] = {p3, p4};
    productions[B] = {p1, p5};
    productions[C] = {p3};

    grammar::Regular regular(vn, vt, productions, S);

    // ----------------------

    finite_automaton::NonDeterministic::symbol_type a_f("a"), b_f("b");
    finite_automaton::NonDeterministic::state_type q0("S"), q1("A"), q2("B"), q3("C"), q4("FIM");

    finite_automaton::NonDeterministic::symbol_set_type alphabet{a_f, b_f};
    finite_automaton::NonDeterministic::state_set_type  states{q0, q1, q2, q3, q4};
    finite_automaton::NonDeterministic::state_set_type  final_states{q4};

    finite_automaton::NonDeterministic::transition_map_type transitions;
    transitions[q0][a_f].insert(q1);
    transitions[q0][a_f].insert(q4);
    transitions[q0][b_f].insert(q2);
    transitions[q1][a_f].insert(q0);
    transitions[q1][b_f].insert(q3);
    transitions[q2][a_f].insert(q1);
    transitions[q2][a_f].insert(q4);
    transitions[q3][a_f].insert(q0);

    finite_automaton::NonDeterministic machine(alphabet, states, transitions, final_states, q0);

    // -------------

    manipulator::DevicesConverter converter;
    auto ndfa = converter.convert(regular);

    CHECK((ndfa == machine));

    CHECK(ndfa.determination() == machine.determination());
}

TEST_CASE("Devices manipulator: NDFA to Grammar", "[expression][parser]")
{
    grammar::Regular::symbol_type S("Q0"), A("Q1"), a("a"), b("b");
    grammar::Regular::vocabulary_set_type vn{S, A}, vt{a, b};

    grammar::Regular::production_type_ptr p1(new grammar::NonTerminalProduction(a, A)),
                                            p2(new grammar::NonTerminalProduction(b, A)),
                                 p3(new grammar::TerminalProduction(a)),
                                 p4(new grammar::TerminalProduction(b));

    grammar::Regular::production_map_type productions;
    productions[S] = {p1, p3};
    productions[A] = {p2, p4};

    grammar::Regular regular(vn, vt, productions, S);

    // ----------------------

    finite_automaton::Deterministic::symbol_type a_("a");
    finite_automaton::Deterministic::symbol_type b_("b");
    finite_automaton::Deterministic::state_type q0("Q0"), q1("Q1");

    finite_automaton::Deterministic::symbol_set_type alphabet{a_, b_};

    finite_automaton::Deterministic::state_set_type  states{q0, q1};
    finite_automaton::Deterministic::state_set_type  final_states{q1};

    finite_automaton::Deterministic::transition_map_type transitions;
    transitions[q0][a_] = q1;
    transitions[q1][b_] = q1;

    finite_automaton::Deterministic machine(alphabet, states, transitions, final_states, q0);

    // -------------

    manipulator::DevicesConverter converter;
    auto gram = converter.convert(machine);

    CHECK((gram == regular));
}
