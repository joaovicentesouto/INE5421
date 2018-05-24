#include "../catch.hpp"

#include <formal_languages/manipulators/Printer.hpp>
#include <sstream>

using namespace formal_device;

TEST_CASE("Printer: FA Deterministic", "[printer][finite_automaton]")
{
    finite_automaton::Deterministic det;
    finite_automaton::NonDeterministic non_det;

    std::cout << "FROM cout: " << det << ", " << non_det << std::endl;

    std::stringstream ss;

    ss << det;
    std::cout << "FROM stringstream: " << ss.str() << std::endl;

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

    std::cout << reg_grammar;

    CHECK(true);
}
