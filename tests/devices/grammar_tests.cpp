//! João Vicente Souto e Bruno Izaias Bonotto

#include "../catch.hpp"

#include <formal_languages/devices/Grammar.hpp>

using namespace formal_device::grammar;

TEST_CASE("Grammar: finite language", "[grammar][symbol]")
{
    Regular::symbol_type S("S"), A("A"), B("B"), a("a"), b("b"), c("c");
    Regular::vocabulary_set_type vn{S, A, B}, vt{a, b, c};

    Regular::production_type_ptr p1(new NonTerminalProduction(a, A)),
                                 p2(new NonTerminalProduction(c, B)),
                                 p3(new NonTerminalProduction(b, B)),
                                 p4(new TerminalProduction(c));

    Regular::production_map_type productions;
    productions[S] = {p1, p2};
    productions[A] = {p3};
    productions[B] = {p4};

    Regular regular(vn, vt, productions, S);

    SECTION("Sentences generation of 1 size", "[grammar][fa]")
    {
        Regular::set_type<Regular::string_type> sentences;
        CHECK(regular.sentences_generator(1) == sentences);
    }

    SECTION("Sentences generation of 2 size", "[grammar][fa]")
    {
        Regular::set_type<Regular::string_type> sentences{"cc"};
        CHECK(regular.sentences_generator(2) == sentences);
    }

    SECTION("Sentences generation of 3 size", "[grammar][fa]")
    {
        Regular::set_type<Regular::string_type> sentences{"abc"};
        CHECK(regular.sentences_generator(3) == sentences);
    }
}

TEST_CASE("Grammar: infinit grammar", "[grammar][symbol]")
{
    Regular::symbol_type S("S"), A("A"), a("a"), b("b");
    Regular::vocabulary_set_type vn{S, A}, vt{a, b};

    Regular::production_type_ptr p1(new NonTerminalProduction(a, A)),
                                 p2(new NonTerminalProduction(b, S)),
                                 p3(new NonTerminalProduction(a, S)),
                                 p4(new TerminalProduction(a));

    Regular::production_map_type productions;
    productions[S] = {p1, p2, p4};
    productions[A] = {p3};

    Regular regular(vn, vt, productions, S);

    SECTION("Sentences generation of 1 size", "[grammar][fa]")
    {
        Regular::set_type<Regular::string_type> sentences{"a"};
        CHECK(regular.sentences_generator(1) == sentences);
    }

    SECTION("Sentences generation of 2 size", "[grammar][fa]")
    {
        Regular::set_type<Regular::string_type> sentences{"ba"};
        CHECK(regular.sentences_generator(2) == sentences);
    }

    SECTION("Sentences generation of 3 size", "[grammar][fa]")
    {
        Regular::set_type<Regular::string_type> sentences{"aaa", "bba"};
        CHECK(regular.sentences_generator(3) == sentences);
    }

    SECTION("Sentences generation of 12 size", "[grammar][fa]")
    {
        auto set = regular.sentences_generator(12);
        CHECK(set.find("aabaabaaaaba") != set.end());
    }
}
