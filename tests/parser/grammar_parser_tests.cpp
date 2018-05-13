#include "../catch.hpp"

#include <src/parser/GrammarParser.hpp>

using namespace formal_devices::grammar;

TEST_CASE("Grammar Parser", "[grammar][parser]")
{
    SECTION("Production and Symbol", "[grammar][parser]")
    {
        std::string str =  "a";
        auto f = str.begin();
        auto l = str.end();

        SECTION("Terminal", "[grammar][parser]")
        {
            ast::Production prod;
            CHECK(phrase_parse(f, l, parser::production, parser::ascii::space, prod));
            CHECK(prod.m_production == "a");
        }

        SECTION("Non Terminal", "[grammar][parser]")
        {
            str = "A";
            f = str.begin();
            l = str.end();

            ast::Production prod;
            CHECK(phrase_parse(f, l, parser::production, parser::ascii::space, prod));
            CHECK(prod.m_production == "A");
        }

        SECTION("Production", "[grammar][parser]")
        {
            str = "aA";
            f = str.begin();
            l = str.end();

            ast::Production prod;
            CHECK(phrase_parse(f, l, parser::production, parser::ascii::space, prod));
            CHECK(prod.m_production == "aA");
        }
    }

    SECTION("Line productions", "[regular_expression][empty]")
    {
        std::string str =  "S -> aA | a | b";
        auto f = str.begin(), l = str.end();

        ast::Line line;
        CHECK(phrase_parse(f, l, parser::line, parser::ascii::space, line));
        CHECK(line.m_symbol == "S");
        CHECK(line.m_productions.size() == 3);

        for (auto prod : line.m_productions)
            CHECK((prod.m_production == "aA" ||
                   prod.m_production == "a"  ||
                   prod.m_production == "b" ));
    }

    SECTION("Document Productions", "[regular_expression][empty]")
    {
        std::istringstream iss("S -> aA | a | b\nA -> bS | b | c");
        boost::spirit::istream_iterator f(iss), l;

        ast::Document doc;
        CHECK(phrase_parse(f, l, parser::document, parser::ascii::space, doc));
//        CHECK(doc.m_lines.size() == 2);

//        ast::Line line = doc.m_lines.front();
//        CHECK(line.m_symbol == "S");
//        CHECK(line.m_productions.size() == 3);

//        for (auto prod : line.m_productions)
//            CHECK((prod.m_production == "aA" ||
//                   prod.m_production == "a"  ||
//                   prod.m_production == "b" ));

//        line = doc.m_lines.back();
//        CHECK(line.m_symbol == "A");
//        CHECK(line.m_productions.size() == 3);

//        for (auto prod : line.m_productions)
//            CHECK((prod.m_production == "bS" ||
//                   prod.m_production == "b"  ||
//                   prod.m_production == "c" ));
    }
}
