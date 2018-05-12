#include "../catch.hpp"

#include <src/model/FiniteAutomatonComponents.hpp>

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

TEST_CASE("FA's Hasher Class", "[grammar][hasher]")
{
    SECTION("FA's Symbol:: set", "[grammar][symbol]"){
        Symbol a("a");
        Symbol b("b");

        std::unordered_set<Symbol, Hasher> set;

        set.insert(a);
        set.insert(b);

        CHECK(set.find(a) != set.end());
        CHECK(set.find(b) != set.end());

        CHECK(set.find(Symbol("a")) != set.end());
        CHECK(set.find(Symbol("b")) != set.end());
        CHECK(set.find(Symbol("c")) == set.end());
    }

    SECTION("FA's State:: set", "[grammar][symbol]"){
        State a("A");
        State b("B");

        std::unordered_set<State, Hasher> set;

        set.insert(a);
        set.insert(b);

        CHECK(set.find(a) != set.end());
        CHECK(set.find(b) != set.end());

        CHECK(set.find(State("A")) != set.end());
        CHECK(set.find(State("B")) != set.end());
        CHECK(set.find(State("C")) == set.end());
    }

    SECTION("FA's map: map symbol to state", "[grammar][symbol]"){
        Symbol a("a");
        Symbol b("b");
        State  A("A");
        State  B("B");

        std::unordered_map<Symbol, State, Hasher> map;

        map[a] = A;
        map[b] = B;

        CHECK(map.find(a) != map.end());
        CHECK(map.find(b) != map.end());

        CHECK(map[a] == A);
        CHECK(map[b] == B);

        CHECK(map.find(Symbol("a")) != map.end());
        CHECK(map.find(Symbol("b")) != map.end());
        CHECK(map.find(Symbol("c")) == map.end());

        CHECK(map[Symbol("a")] == A);
        CHECK(map[Symbol("b")] == B);
    }
}
