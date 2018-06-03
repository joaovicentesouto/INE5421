#include "../catch.hpp"

#include <formal_languages/components/FiniteAutomatonComponents.hpp>

using namespace formal_device::finite_automaton;

TEST_CASE("FA Symbol", "[finite_automaton][symbol]")
{
    SECTION("FA Symbol: Default constructor", "[finite_automaton][symbol]"){
        Symbol a;

        CHECK(a == "&");
    }

    SECTION("FA Symbol: Custom construtors", "[finite_automaton][symbol]"){
        Symbol a("a");

        CHECK(a == "a");
    }

    SECTION("FA Symbol: Copy construtors", "[finite_automaton][symbol]"){
        Symbol a("a");
        Symbol b(a);

        CHECK(b == "a");
    }

    SECTION("FA Symbol: Move construtors", "[finite_automaton][symbol]"){
        Symbol a("a");
        Symbol b(std::move(a));

        CHECK(b == "a");
    }

    SECTION("FA Symbol: Operator ==", "[finite_automaton][symbol]"){
        Symbol a("a");
        Symbol b("a");
        Symbol c("c");

        CHECK(a == b);
        CHECK(!(a == c));
    }
}

TEST_CASE("FA State", "[finite_automaton][symbol]")
{
    SECTION("FA State: Default constructor", "[finite_automaton][symbol]"){
        State a;

        CHECK(a == "Error");
    }

    SECTION("FA State: Custom construtors", "[finite_automaton][symbol]"){
        State a("A");

        CHECK(a == "A");
    }

    SECTION("FA State: Copy construtors", "[finite_automaton][symbol]"){
        State a("A");
        State b(a);

        CHECK(b == "A");
    }

    SECTION("FA State: Move construtors", "[finite_automaton][symbol]"){
        State a("A");
        State b(std::move(a));

        CHECK(b == "A");
    }

    SECTION("FA State: Operator ==", "[finite_automaton][symbol]"){
        State a("A");
        State b("A");
        State c("C");

        CHECK(a == b);
        CHECK(!(a == c));
    }
}
