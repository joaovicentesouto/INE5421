//! João Vicente Souto e Bruno Izaias Bonotto

#include "../catch.hpp"

#include <context_free_languages/model/components/GrammarComponents.hpp>
#include <context_free_languages/model/parsers/ContextFreeGrammarParser.hpp>

using namespace formal_device::grammar;
using namespace formal_device::parser;

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

TEST_CASE("Parser", "[parser][grammar]")
{
    non_terminal_symbol_type E("E123");
    non_terminal_symbol_type T("T");
    non_terminal_symbol_type F("F");

    terminal_symbol_type plus("+");
    terminal_symbol_type subtraction("-");
    terminal_symbol_type multiplier("*");
    terminal_symbol_type divisor("/");
    terminal_symbol_type open("(");
    terminal_symbol_type close(")");
    terminal_symbol_type id("id");

    non_terminal_set_type vn{E, T, F};
    terminal_set_type vt{plus, subtraction, multiplier, divisor, open, close, id};

    production_type p1(symbol_ptr_type(E),
                       symbol_ptr_type(plus),
                       symbol_ptr_type(T));
    production_type p2(symbol_ptr_type(E),
                       symbol_ptr_type(subtraction),
                       symbol_ptr_type(T));
    production_type p3(symbol_ptr_type(T));

    production_type p4(symbol_ptr_type(T),
                       symbol_ptr_type(multiplier),
                       symbol_ptr_type(F));
    production_type p5(symbol_ptr_type(T),
                       symbol_ptr_type(divisor),
                       symbol_ptr_type(F));
    production_type p6(symbol_ptr_type(F));

    production_type p7(symbol_ptr_type(open),
                       symbol_ptr_type(E),
                       symbol_ptr_type(close));
    production_type p8(symbol_ptr_type(id));

    production_map_type p = {{E, set_type<production_type>{p1, p2, p3}},
                             {T, set_type<production_type>{p4, p5, p6}},
                             {F, set_type<production_type>{p7, p8}}};

    grammar_type grammar(vn, vt, p, E);

    grammar_type parser_grammar = grammar_parser("E123 -> E123 + T | E123 - T | T \n T -> T * F | T / F | F\n F -> ( E123 ) | id");

    CHECK(parser_grammar == grammar);
}
