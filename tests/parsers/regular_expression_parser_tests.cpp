#include "../catch.hpp"

#include <formal_languages/parsers/ExpressionParser.hpp>

using namespace formal_device::parser;

TEST_CASE("Regular Expression Parser: Simple String", "[expression][parser]")
{
    SECTION("Unit a", "[expression][parser]")
    {
        string_type str =  "a";
        IteratorWrapper f(str.begin()), l(str.end());
        CHECK(parse(f, l) == regular_ptr(new unit_type("a")));
    }

    SECTION("Unit 0", "[expression][parser]")
    {
        string_type str =  "0";
        IteratorWrapper f(str.begin()), l(str.end());
        CHECK(parse(f, l) == regular_ptr(new unit_type("0")));
    }

    SECTION("Unit (", "[expression][parser]")
    {
        string_type str =  "*";
        IteratorWrapper f(str.begin()), l(str.end());
        CHECK_THROWS(parse(f, l));
    }
}

TEST_CASE("Regular Expression Parser: Complex String", "[expression][parser]")
{
    SECTION("Unit abc", "[expression][parser]")
    {
        string_type str =  "abc";
        IteratorWrapper f(str.begin()), l(str.end());

        auto exp = regular_ptr(new unit_type("a")) + (regular_ptr(new unit_type("b")) + regular_ptr(new unit_type("c")));
        CHECK(parse(f, l) == exp);
    }

    SECTION("Exp: (ab?|c)*", "[expression][parser]")
    {
        string_type str =  "(ab?|c)*";
        IteratorWrapper f(str.begin()), l(str.end());

        auto exp = regular_ptr(
                    new reflexive_type(
                        new union_type(
                            new concatenation_type(
                                new unit_type("a"),
                                new optional_type(new unit_type("b"))
                            ),
                            new unit_type("c")
                        )
                    )
                   );
        CHECK((parse(f, l) == exp));
    }

    SECTION("Exp: ab?|c|d", "[expression][parser]")
    {
        string_type str =  "ab?|c|d";
        IteratorWrapper f(str.begin()), l(str.end());

        auto exp = regular_ptr(
                        new union_type(
                            new concatenation_type(
                                new unit_type("a"),
                                new optional_type(new unit_type("b"))
                            ),
                            new union_type(
                                new unit_type("c"),
                                new unit_type("d")
                            )
                        )
                    );

        regular_ptr current_exp(new empty_type());

        while (f.iterator() != l.iterator())
            if (*f.iterator() == '|')
            {
                f.next();
                current_exp = current_exp | union_parser(f, l);
            }
            else
                current_exp = current_exp + parse(f, l);

        CHECK((current_exp == exp));
    }

    SECTION("Exp: ab?|c|d", "[expression][parser]")
    {
        string_type str =  "ab?|c|d";
        regular_ptr current_exp = make_regular_expression(str);

        auto exp = regular_ptr(
                        new union_type(
                            new concatenation_type(
                                new unit_type("a"),
                                new optional_type(new unit_type("b"))
                            ),
                            new union_type(
                                new unit_type("c"),
                                new unit_type("d")
                            )
                        )
                    );



        CHECK((current_exp == exp));
        
        //CHECK_NOTHROW(make_regular_expression("(ab?)*"));
    }
}

TEST_CASE("Regular Expression Parser: Valid expressions", "[expression][parser]")
{
    CHECK_NOTHROW(make_regular_expression(""));
    CHECK_NOTHROW(make_regular_expression("a"));
    CHECK_NOTHROW(make_regular_expression("&"));
    CHECK_NOTHROW(make_regular_expression("a*"));
    CHECK_NOTHROW(make_regular_expression("a+"));
    CHECK_NOTHROW(make_regular_expression("a?"));

    CHECK_NOTHROW(make_regular_expression("(a)"));
    CHECK_NOTHROW(make_regular_expression("(&)"));
    CHECK_NOTHROW(make_regular_expression("(a)*"));
    CHECK_NOTHROW(make_regular_expression("(a)+"));
    CHECK_NOTHROW(make_regular_expression("(a)?"));
    CHECK_NOTHROW(make_regular_expression("(a*)"));
    CHECK_NOTHROW(make_regular_expression("(a+)"));
    CHECK_NOTHROW(make_regular_expression("(a?)"));

    CHECK_NOTHROW(make_regular_expression("ab*"));
    CHECK_NOTHROW(make_regular_expression("a*b"));
    CHECK_NOTHROW(make_regular_expression("a*b*"));
    CHECK_NOTHROW(make_regular_expression("ab+"));
    CHECK_NOTHROW(make_regular_expression("a+b"));
    CHECK_NOTHROW(make_regular_expression("a?b?"));
    CHECK_NOTHROW(make_regular_expression("ab?"));
    CHECK_NOTHROW(make_regular_expression("a?b"));
    CHECK_NOTHROW(make_regular_expression("a*b+"));
    CHECK_NOTHROW(make_regular_expression("a*b?"));
    CHECK_NOTHROW(make_regular_expression("a+b*"));
    CHECK_NOTHROW(make_regular_expression("a+b?"));
    CHECK_NOTHROW(make_regular_expression("a?b*"));
    CHECK_NOTHROW(make_regular_expression("a?b+"));

    CHECK_NOTHROW(make_regular_expression("a | b"));
    CHECK_NOTHROW(make_regular_expression("a* | b"));
    CHECK_NOTHROW(make_regular_expression("a | b*"));
    CHECK_NOTHROW(make_regular_expression("a* | b*"));

    CHECK_NOTHROW(make_regular_expression("(ab)*"));
    CHECK_NOTHROW(make_regular_expression("(ab)+"));
    CHECK_NOTHROW(make_regular_expression("(ab)?"));

    CHECK_NOTHROW(make_regular_expression("(a | b)*"));
    CHECK_NOTHROW(make_regular_expression("(a | b)+"));
    CHECK_NOTHROW(make_regular_expression("(a | b)?"));

    CHECK_NOTHROW(make_regular_expression("(ab*)?"));
    CHECK_NOTHROW(make_regular_expression("(ab?)*"));
    CHECK_NOTHROW(make_regular_expression("(ab? | c)*"));

    CHECK_NOTHROW(make_regular_expression("b?(ac)?c+"));
    CHECK_NOTHROW(make_regular_expression("(abc)(abc)"));
    CHECK_NOTHROW(make_regular_expression("a+(b*)b?"));
    CHECK_NOTHROW(make_regular_expression("(b?(ac)?c+ | b?(ac)?c+)+ab*c((a)(b*)?)"));
    CHECK_NOTHROW(make_regular_expression("(ab? | c | b?(ac)?c+ | d)*"));
    CHECK_NOTHROW(make_regular_expression("(ab? | c | b?(ac)?c+ | d)* | (a+(b*)b? | c | b?(ac)?c+ | d)?"));
}



