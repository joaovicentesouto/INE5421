//! João Vicente Souto e Bruno Izaias Bonotto

#include "../catch.hpp"

#include <formal_languages/devices/Grammar.hpp>
#include <formal_languages/parsers/GrammarParser.hpp>

using namespace formal_device::parser;
using regular_type = formal_device::grammar::Regular;

TEST_CASE("Grammar Parser: Document Productions", "[regular_expression][empty]")
{
    std::string string("S -> aA | a | b\nA -> bS | b | c");

    regular_type::symbol_type S("S"), A("A"), a("a"), b("b"), c("c");
    regular_type::vocabulary_set_type vn{S, A}, vt{a, b, c};
    regular_type::production_type_ptr p1(new regular_type::non_terminal_production_type(a, A)),
                                 p2(new regular_type::non_terminal_production_type(b, S)),
                                 p3(new regular_type::terminal_production_type(a)),
                                 p4(new regular_type::terminal_production_type(b)),
                                 p5(new regular_type::terminal_production_type(c));

    regular_type::production_map_type productions;
    productions[S] = {p1, p3, p4};
    productions[A] = {p2, p4, p5};

    regular_type grammar_r(vn, vt, productions, S);

    regular_type regular = make_regular_grammar(string);

    CHECK((regular == grammar_r));
}

TEST_CASE("Grammar Parser: valid Grammar", "[grammar][parser]")
{
    CHECK_NOTHROW(make_regular_grammar("S ->"));
    CHECK_NOTHROW(make_regular_grammar("S -> a"));
    CHECK_NOTHROW(make_regular_grammar("S -> aA"));
    CHECK_NOTHROW(make_regular_grammar("S -> aA\nA"));
    CHECK_NOTHROW(make_regular_grammar("S -> a\nS -> b"));
    CHECK_NOTHROW(make_regular_grammar("S -> a\nA-> a | bB"));
    CHECK_NOTHROW(make_regular_grammar("S -> aA | aB | c\nA-> a | b"));
    CHECK_NOTHROW(make_regular_grammar("S -> aA | b\nA -> aC | b\nC -> bS | c"));
}

TEST_CASE("Grammar Parser: Invalid Grammar", "[grammar][parser]")
{
    CHECK_THROWS(make_regular_grammar("a -> a"));
    CHECK_THROWS(make_regular_grammar("S - A"));
    CHECK_THROWS(make_regular_grammar("S > A"));
    CHECK_THROWS(make_regular_grammar("-> a"));
    CHECK_THROWS(make_regular_grammar("S -> aA | B"));
    CHECK_THROWS(make_regular_grammar("a -> aA | b"));
    CHECK_THROWS(make_regular_grammar("S -> aA | A | b"));
}

//TEST_CASE("Grammar Parser: File", "[regular_expression][empty]")
//{
//    std::ifstream ifs("./files/grammar.txt");
//    CHECK(ifs.is_open());
//    ifs >> std::noskipws;

//    boost::spirit::istream_iterator f(ifs), l;

//    ast::GrammarDocument doc;
//    CHECK(phrase_parse(f, l, parser::grammar_document, parser::ascii::blank, doc));
//    CHECK(doc.m_lines.size() == 2);

//    ast::GrammarLine line = doc.m_lines.front();
//    CHECK(line.m_symbol == "S");
//    CHECK(line.m_productions.size() == 3);

//    for (auto prod : line.m_productions)
//        CHECK((prod.m_production == "aA" ||
//               prod.m_production == "a"  ||
//               prod.m_production == "b" ));

//    line = doc.m_lines.back();
//    CHECK(line.m_symbol == "A");
//    CHECK(line.m_productions.size() == 3);

//    for (auto prod : line.m_productions)
//        CHECK((prod.m_production == "bS" ||
//               prod.m_production == "b"  ||
//               prod.m_production == "c" ));
//}
