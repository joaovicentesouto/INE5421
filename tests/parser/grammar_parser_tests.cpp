#include "../catch.hpp"

#include <src/parser/GrammarParser.hpp>

TEST_CASE("Grammar Parser", "[grammar][parser]")
{
    SECTION("Production and Symbol", "[grammar][parser]")
    {
        std::string str =  "a";
        auto f = str.begin();
        auto l = str.end();

        SECTION("Production and Symbol", "[grammar][parser]")
        {
            ast::Production prod;
            CHECK(phrase_parse(f, l, parser::production, parser::ascii::space, prod));
            CHECK(prod.m_production == "a");
        }

        SECTION("Production and Symbol", "[grammar][parser]")
        {
            str = "A";
            f = str.begin();
            l = str.end();

            ast::Production prod;
            CHECK(phrase_parse(f, l, parser::production, parser::ascii::space, prod));
            CHECK(prod.m_production == "A");
        }

        SECTION("Production and Symbol", "[grammar][parser]")
        {
            str = "aA";
            f = str.begin();
            l = str.end();

            ast::Production prod;
            CHECK(phrase_parse(f, l, parser::production, parser::ascii::space, prod));
            CHECK(prod.m_production == "aA");
        }
    }

    SECTION("Regular Expression: Empty", "[regular_expression][empty]")
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
}
