//! João Vicente Souto e Bruno Izaias Bonotto

#include "../catch.hpp"

#include <formal_languages/manipulators/Printer.hpp>
#include <sstream>

using namespace formal_device;

TEST_CASE("Printer: FA Deterministic", "[printer][finite_automaton]")
{
    finite_automaton::NonDeterministic non_det;

    std::cout << "FROM cout: " << non_det << std::endl;

    grammar::Regular::symbol_type S("S"), A("A"), B("B"), a("a"), b("b"), c("c");
    grammar::Regular::vocabulary_set_type vn{S, A, B}, vt{a, b, c};

    grammar::Regular::production_type_ptr p1(new grammar::NonTerminalProduction(a, A)),
                                 p2(new grammar::NonTerminalProduction(c, B)),
                                 p3(new grammar::NonTerminalProduction(b, B)),
                                 p4(new grammar::TerminalProduction(c));

    grammar::Regular::production_map_type productions;
    productions[S] = {p1, p2};
    productions[A] = {p3};
    productions[B] = {p4};

    grammar::Regular reg_grammar(vn, vt, productions, S);

    std::cout << "\nGrammar Printer:\n" << reg_grammar;

    finite_automaton::Deterministic::symbol_type a_FA("a");
    finite_automaton::Deterministic::symbol_type b_FA("b");
    finite_automaton::Deterministic::state_type q0("q0"), q1("q1"), q2("q2"), q3("q3");

    finite_automaton::Deterministic::symbol_set_type alphabet{a_FA, b_FA};
    finite_automaton::Deterministic::state_set_type  states{q0, q1, q2, q3};
    finite_automaton::Deterministic::state_set_type  final_states{q1, q2};

    finite_automaton::Deterministic::transition_map_type transitions;
    transitions[q0][a_FA] = q2;
    transitions[q0][b_FA] = q1;
    transitions[q1][a_FA] = q2;
    transitions[q2][a_FA] = q0;
    transitions[q2][b_FA] = q3;
    transitions[q3][a_FA] = q0;

    finite_automaton::Deterministic machine(alphabet, states, transitions, final_states, q0);

    std::cout << "\nFinite Automaton Deterministic Printer:\n" << machine;

    finite_automaton::NonDeterministic::state_set_type  final_states_reverse{q1};

    finite_automaton::NonDeterministic::transition_map_type transitions_reverse;
    transitions_reverse[q0][a_FA].insert(q1);
    transitions_reverse[q0][a_FA].insert(q2);
    transitions_reverse[q0][a_FA].insert(q3);

    transitions_reverse[q2][a_FA].insert(q1);
    transitions_reverse[q3][b_FA].insert(q1);
    transitions_reverse[q2][a_FA].insert(q2);
    transitions_reverse[q3][b_FA].insert(q2);
    transitions_reverse[q2][a_FA].insert(q3);
    transitions_reverse[q3][b_FA].insert(q3);

    finite_automaton::NonDeterministic reverse(alphabet, states, transitions_reverse, final_states_reverse, q0);

    std::cout << "\nFinite Automaton NonDeterministic Printer:\n" << reverse;

    CHECK(true);
}
