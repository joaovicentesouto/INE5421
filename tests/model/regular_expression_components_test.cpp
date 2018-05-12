#include "../catch.hpp"

#include <src/model/RegularExpressionComponents.hpp>

using namespace formal_device::expression;

TEST_CASE("Regular Expression: Construction of types", "[regular_expression][types]")
{
    SECTION("Regular Expression: Empty", "[regular_expression][empty]"){
        Empty a;

        CHECK(a == new Empty());
    }

    SECTION("Regular Expression: RegularPointer", "[regular_expression][regularpointer]")
    {
        RegularPointer p(new Empty());

        CHECK(p == new Empty());
    }

    SECTION("Regular Expression: Epsilon", "[regular_expression][epsilon]")
    {
        Epsilon a;

        CHECK(a == new Epsilon());
    }

    SECTION("Regular Expression: Unit", "[regular_expression][unit]")
    {
        Unit a("a");

        CHECK(a == new Unit("a"));
    }

    SECTION("Regular Expression: Union", "[regular_expression][union]")
    {
        RegularPointer a(new Unit("a"));
        RegularPointer b(new Unit("b"));

        Union un(a, b);

        CHECK( un == new Union(new Unit("a"), new Unit("b")) );
    }

    SECTION("Regular Expression: Concatenation", "[regular_expression][concatenation]")
    {
        RegularPointer a(new Unit("a"));
        RegularPointer b(new Unit("b"));

        Concatenation con(a, b);

        CHECK( con == new Concatenation(new Unit("a"), new Unit("b")) );
    }

    SECTION("Regular Expression: ReflexiveClosure", "[regular_expression][reflexive][closure]")
    {
        RegularPointer a(new Unit("a"));

        ReflexiveClosure reflex(a);

        CHECK( reflex == new ReflexiveClosure(new Unit("a")) );
    }

    SECTION("Regular Expression: TransitiveClosure", "[regular_expression][transitive][closure]")
    {
        RegularPointer a(new Unit("a"));

        TransitiveClosure reflex(a);

        CHECK( reflex == new TransitiveClosure(new Unit("a")) );
    }

    SECTION("Regular Expression: Optional", "[regular_expression][optional]")
    {
        RegularPointer a(new Unit("a"));

        Optional reflex(a);

        CHECK( reflex == new Optional(new Unit("a")) );
    }
}

TEST_CASE("Regular Expression: Empty", "[regular_expression][empty]")
{
    SECTION("Empty: Union", "[regular_expression][empty]"){
        RegularPointer empty(new Empty());
        RegularPointer unit(new Unit("a"));

        RegularPointer ptr = empty | unit;

        CHECK(ptr == unit);
    }

    SECTION("Empty: Concatenation", "[regular_expression][empty]")
    {
        RegularPointer empty(new Empty());
        RegularPointer unit(new Unit("a"));

        RegularPointer ptr = empty + unit;

        CHECK(ptr == unit);
    }

    SECTION("Empty: Operation", "[regular_expression][empty]")
    {
        RegularPointer empty(new Empty());

        RegularPointer ptr = empty ^ Operation::Star;

        CHECK(ptr == empty);

        CHECK((empty ^ Operation::Plus) == empty);
        CHECK((empty ^ Operation::Optional) == empty);
    }
}

TEST_CASE("Regular Expression: Unit", "[regular_expression][unit]")
{
    SECTION("Unit: Union", "[regular_expression][empty]"){
        RegularPointer a(new Unit("a"));
        RegularPointer b(new Unit("b"));

        RegularPointer ptr = a | b;

        CHECK(ptr == new Union(a, b));

        CHECK((a | new Empty())   == a);
        CHECK((a | new Epsilon()) == new Optional(a));
    }

    SECTION("Unit: Concatenation", "[regular_expression][unit]")
    {
        RegularPointer a(new Unit("a"));
        RegularPointer b(new Unit("b"));

        RegularPointer ptr = a + b;

        CHECK(ptr == new Concatenation(a, b));

        CHECK((a + new Empty())   == a);
        CHECK((a + new Epsilon()) == a);
    }

    SECTION("Empty: Operation", "[regular_expression][empty]")
    {
        RegularPointer a(new Unit("a"));

        CHECK((a ^ Operation::Star) == new ReflexiveClosure(a));
        CHECK((a ^ Operation::Plus) == new TransitiveClosure(a));
        CHECK((a ^ Operation::Optional) == new Optional(a));
    }
}
