#include "../catch.hpp"

#include <formal_languages/parsers/ExpressionParser.hpp>
#include <formal_languages/manipulators/DeSimoneTree.cpp>

using namespace formal_device;

TEST_CASE("DeSimoneTree: Build (ab?|c)*", "[expression][parser]")
{
    auto exp = parser::regular_ptr(
        new parser::reflexive_type(
            new parser::union_type(
                new parser::concatenation_type(
                    new parser::unit_type("a"),
                    new parser::optional_type(
                        new parser::unit_type("b"))),
                new parser::unit_type("c")))); // (ab?|c)*

    expression::DeSimoneTree tree(exp);

    using dfa_type = finite_automaton::Deterministic;

    dfa_type::symbol_type a{"a"}, b{"b"}, c{"c"};
    dfa_type::state_type q0{"q0"}, q1{"q1"};
    dfa_type::symbol_set_type alphabet{a, b, c};
    dfa_type::state_set_type  states{q0, q1};
    dfa_type::transition_map_type transitions;
    transitions[q0][a] = q1;
    transitions[q0][c] = q0;
    transitions[q1][a] = q1;
    transitions[q1][b] = q0;
    transitions[q1][c] = q0;

    dfa_type machine(alphabet, states, transitions, states, q0);

    auto simone = tree.execute();

    CHECK((simone == machine));
}
