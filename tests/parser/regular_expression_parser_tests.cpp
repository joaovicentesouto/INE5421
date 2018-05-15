#include "../catch.hpp"

#include <formal_languages/parsers/ExpressionParser.hpp>

using namespace formal_device::parser;

TEST_CASE("Regular Expression Parser: Simple String", "[expression][parser]")
{
    SECTION("Unit a", "[expression][parser]")
    {
        string_type str =  "a";
        string_iterator_type f(str.begin()), l(str.end());
        CHECK(parse(f, l) == regular_ptr(new unit_type("a")));
    }

    SECTION("Unit 0", "[expression][parser]")
    {
        string_type str =  "0";
        string_iterator_type f(str.begin()), l(str.end());
        CHECK(parse(f, l) == regular_ptr(new unit_type("0")));
    }

    SECTION("Unit (", "[expression][parser]")
    {
        string_type str =  "*";
        string_iterator_type f(str.begin()), l(str.end());
        CHECK_THROWS(parse(f, l));
    }
}

TEST_CASE("Regular Expression Parser: Complex String", "[expression][parser]")
{
    SECTION("Unit abc", "[expression][parser]")
    {
        string_type str =  "abc";
        string_iterator_type f(str.begin()), l(str.end());

        auto exp = regular_ptr(new unit_type("a")) + (regular_ptr(new unit_type("b")) + regular_ptr(new unit_type("c")));
        CHECK(parse(f, l) == exp);
    }
}

