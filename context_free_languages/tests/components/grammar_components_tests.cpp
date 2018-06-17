//! João Vicente Souto e Bruno Izaias Bonotto

#include "../catch.hpp"

#include <context_free_languages/model/components/GrammarComponents.hpp>

using namespace formal_device::grammar;

TEST_CASE("Symbols", "[grammar][symbol]")
{
    TerminalSymbol a("a");
    NonTerminalSymbol B("B");

    CHECK(a == a);
    CHECK(B == B);
    CHECK(a != B);

    //! Copy
    TerminalSymbol a2(a);
    CHECK(a == a2);

    //! Move
    TerminalSymbol a3(std::move(a2));
    CHECK(a == a3);

    //! Copy
    NonTerminalSymbol B2(B);
    CHECK(B == B2);

    NonTerminalSymbol B3(std::move(B2));
    CHECK(B == B3);

    SECTION("Pointers", "[grammar][symbol]")
    {
        SymbolPointer a_ptr(new TerminalSymbol("a"));
        CHECK(a_ptr->is_terminal());
        CHECK(a_ptr->value() == "a");

        Symbol * base_a = a_ptr.get();
        CHECK(a_ptr == base_a);
        CHECK(a_ptr == a_ptr);
        CHECK(*a_ptr == "a");
        CHECK(a_ptr == "a");

        SymbolPointer B_ptr(new NonTerminalSymbol("B"));
        CHECK(!B_ptr->is_terminal());
        CHECK(B_ptr->value() == "B");

        Symbol * base_B = B_ptr.get();
        CHECK(B_ptr == base_B);
        CHECK(B_ptr == B_ptr);
        CHECK(*B_ptr == "B");
        CHECK(B_ptr == "B");

        CHECK(a == a_ptr);
        CHECK(a != B_ptr);
        CHECK(B != a_ptr);
        CHECK(B == B_ptr);
    }
}

TEST_CASE("Productions", "[grammar][symbol]")
{
    Production prod;
    prod.push_back(new TerminalSymbol("a"));
    prod.push_back(new NonTerminalSymbol("B"));

    CHECK(prod.front() == "a");
    CHECK(prod.back() == "B");

    Production prod2;
    prod2.push_back(new TerminalSymbol("a"));
    prod2.push_back(new NonTerminalSymbol("B"));
    CHECK(prod == prod2);

    Production prod3;
    prod.push_back(new TerminalSymbol("b"));
    prod.push_back(new NonTerminalSymbol("A"));
    CHECK(prod != prod3);
}
