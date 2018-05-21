#include "../catch.hpp"

#include <formal_languages/devices/Grammar.hpp>

using namespace formal_device::grammar;

TEST_CASE("Grammar: init", "[grammar][symbol]")
{
    Regular::symbol_type S("S"), A("A"), B("B"), a("a"), b("b"), c("c");
    Regular::vocabulary_set_type vn{S, A, B}, vt{a, b, c};

    Regular::production_type_ptr p1(new NonTerminalProduction(A, a)),
                                 p2(new NonTerminalProduction(B, c)),
                                 p3(new NonTerminalProduction(B, b)),
                                 p4(new TerminalProduction(c));

    Regular::production_map_type productions;
    productions[S] = {p1, p2};
    productions[A] = {p3};
    productions[B] = {p4};

    Regular regular(vn, vt, productions, S);

    SECTION("Sentences generation of n size", "[grammar][fa]")
    {
        Regular::set_type<Regular::string_type> sentences{"ab", "cc"};

        CHECK(regular.sentences_generator(2) == sentences);
    }
}
