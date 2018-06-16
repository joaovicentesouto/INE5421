//! João Vicente Souto e Bruno Izaias Bonotto

#include "../catch.hpp"

#include <context_free_languages/model/devices/Grammar.hpp>

using namespace formal_device::grammar;
TEST_CASE("Grammar init", "[grammar]")
{
    ContextFree grammar;
    CHECK(grammar == grammar);
    CHECK(!grammar.vn().empty());
    CHECK(grammar.vt().empty());
    CHECK(grammar.productions().empty());
    CHECK(grammar.initial_symbol() == "S");

    SECTION("Compare", "[grammar][==]")
    {
        NonTerminalSymbol S{"S"}, A{"A"}, B{"B"};
        TerminalSymbol a{"a"}, b{"b"};

        SymbolPointer pS{new NonTerminalSymbol(S)}, pA{new NonTerminalSymbol(A)}, pB{new NonTerminalSymbol(B)};
        SymbolPointer pa{new TerminalSymbol(a)}, pb{new TerminalSymbol(b)};
        Production p0{pS, pA}, p1{pa, pA, pB}, p2{pB, pB, pa}, p3{pb, pA, pa};

        ContextFree::non_terminal_set_type ga_vn{S, A, B};
        ContextFree::terminal_set_type ga_vt{a, b};
        ContextFree::production_map_type prods;
        prods[S] = {p0, p1};
        prods[A] = {p0, p2};
        prods[B] = {p0, p3};

        ContextFree ga{ga_vn, ga_vt, prods, S};

        CHECK(ga == ga);
        CHECK(ga != grammar);
        CHECK(!ga.vn().empty());
        CHECK(!ga.vt().empty());
        CHECK(!ga.productions().empty());
        CHECK(ga.initial_symbol() == "S");

        ContextFree gcopy(ga);
        CHECK(gcopy == ga);

        ContextFree gmove(std::move(gcopy));
        CHECK(gmove == ga);
    }
}

TEST_CASE("Grammar: Remove infertile symbols", "[grammar][function]")
{
    SECTION("Simple", "[grammar][inferile]")
    {
        NonTerminalSymbol S{"S"}, A{"A"};
        TerminalSymbol a{"a"}, b{"b"}, c{"c"};

        SymbolPointer pS{new NonTerminalSymbol(S)},
                      pA{new NonTerminalSymbol(A)};
        SymbolPointer pa{new TerminalSymbol(a)}, pb{new TerminalSymbol(b)}, pc{new TerminalSymbol(c)};
        Production prod0{pa}, prod1{pb, pS}, prod2{pA, pS}, prod3{pA, pA, pc};

        ContextFree::non_terminal_set_type vn{S, A};
        ContextFree::terminal_set_type vt{a, b, c};
        ContextFree::production_map_type prods;
        prods[S] = {prod0, prod1, prod2};
        prods[A] = {prod3};

        ContextFree grammar{vn, vt, prods, S};

        ContextFree::non_terminal_set_type fertible;
        auto new_grammar = grammar.remove_infertile_symbols(fertible);

        REQUIRE(!fertible.empty());

        ContextFree::non_terminal_set_type new_vn{S};
        ContextFree::terminal_set_type new_vt{a, b};
        ContextFree::production_map_type new_prods;
        new_prods[S] = {prod0, prod1};

        ContextFree grammar_2{new_vn, new_vt, new_prods, S};

        REQUIRE(fertible == new_vn);
        CHECK(new_grammar.vn().size() == 1);
        CHECK(new_grammar.vt().size() == 2);
        CHECK(new_grammar.productions().size() == 1);
        CHECK(new_grammar.initial_symbol() == S);
        CHECK(new_grammar == grammar_2);
    }

    SECTION("Complex", "[grammar][inferile]")
    {
        NonTerminalSymbol S{"S"}, A{"A"}, B{"B"}, C{"C"};
        TerminalSymbol a{"a"}, b{"b"}, c{"c"};

        SymbolPointer pS{new NonTerminalSymbol(S)},
                      pA{new NonTerminalSymbol(A)},
                      pB{new NonTerminalSymbol(B)},
                      pC{new NonTerminalSymbol(C)};
        SymbolPointer pa{new TerminalSymbol(a)}, pb{new TerminalSymbol(b)}, pc{new TerminalSymbol(c)};
        Production prod0{pa, pA, pA}, prod1{pb, pB, pC}, prod2{pA, pS, pA}, prod3{pC, pC},
                   prod4{pb, pb}, prod5{pA, pC},
                   prod6{pa, pA}, prod7{pC, pc},
                   prod8{pC, pC}, prod9{pB, pS, pa, pC}, prod10{pc, pC};

        ContextFree::non_terminal_set_type vn{S, A, B, C};
        ContextFree::terminal_set_type vt{a, b, c};
        ContextFree::production_map_type prods;
        prods[S] = {prod0, prod1, prod2, prod3};
        prods[A] = {prod4, prod5};
        prods[B] = {prod6, prod7};
        prods[C] = {prod8, prod9, prod10};

        ContextFree grammar{vn, vt, prods, S};

        ContextFree::non_terminal_set_type fertible;
        auto new_grammar = grammar.remove_infertile_symbols(fertible);

        REQUIRE(!fertible.empty());

        ContextFree::non_terminal_set_type new_vn{S, A, B};
        ContextFree::terminal_set_type new_vt{a, b};
        ContextFree::production_map_type new_prods;
        new_prods[S] = {prod0, prod2};
        new_prods[A] = {prod4};
        new_prods[B] = {prod6};

        ContextFree grammar_2{new_vn, new_vt, new_prods, S};

        REQUIRE(fertible == new_vn);
        CHECK(new_grammar.vn().size() == 3);
        CHECK(new_grammar.vt().size() == 2);
        CHECK(new_grammar.productions().size() == 3);
        CHECK(new_grammar.initial_symbol() == S);
        CHECK((new_grammar == grammar_2));
    }

    SECTION("Complex", "[grammar][inferile]")
    {
        NonTerminalSymbol S{"S"}, A{"A"}, B{"B"}, C{"C"};
        TerminalSymbol a{"a"}, b{"b"}, c{"c"};

        SymbolPointer pS{new NonTerminalSymbol(S)},
                      pA{new NonTerminalSymbol(A)},
                      pB{new NonTerminalSymbol(B)},
                      pC{new NonTerminalSymbol(C)};
        SymbolPointer pa{new TerminalSymbol(a)}, pb{new TerminalSymbol(b)}, pc{new TerminalSymbol(c)};
        Production prod0{pa, pA, pA}, prod1{pb, pB, pC}, prod2{pA, pS, pA}, prod3{pC, pC},
                   prod4{pb, pb}, prod5{pA, pC},
                   prod6{pa, pA}, prod7{pC, pc},
                   prod8{pC, pC}, prod9{pB, pS, pa, pC}, prod10{pc, pC};

        ContextFree::non_terminal_set_type vn{S, A, B, C};
        ContextFree::terminal_set_type vt{a, b, c};
        ContextFree::production_map_type prods;
        prods[S] = {prod10};
        prods[A] = {prod4, prod5};
        prods[B] = {prod6, prod7};
        prods[C] = {prod8, prod9, prod10};

        ContextFree grammar{vn, vt, prods, S};

        ContextFree::non_terminal_set_type fertible;
        auto new_grammar = grammar.remove_infertile_symbols(fertible);

        REQUIRE(!fertible.empty());

        ContextFree::non_terminal_set_type new_vn{A, B};
        ContextFree::terminal_set_type new_vt{a, b};
        ContextFree::production_map_type new_prods;
        new_prods[A] = {prod4};
        new_prods[B] = {prod6};

        ContextFree grammar_2{new_vn, new_vt, new_prods, S};

        REQUIRE(fertible == new_vn);
        CHECK(new_grammar.vn().size() == 2);
        CHECK(new_grammar.vt().size() == 2);
        CHECK(new_grammar.productions().size() == 2);
        CHECK(new_grammar.initial_symbol() == S);
        CHECK((new_grammar == grammar_2));
    }
}

TEST_CASE("Grammar: Removes unreachable symbols", "[grammar][function]")
{
    SECTION("Simple", "[grammar][inferile]")
    {
        NonTerminalSymbol S{"S"}, A{"A"};
        TerminalSymbol a{"a"}, b{"b"};

        SymbolPointer pS{new NonTerminalSymbol(S)},
                      pA{new NonTerminalSymbol(A)};
        SymbolPointer pa{new TerminalSymbol(a)}, pb{new TerminalSymbol(b)};
        Production prod0{pa, pS}, prod1{pa}, prod2{pb, pA}, prod3{pb};

        ContextFree::non_terminal_set_type vn{S, A};
        ContextFree::terminal_set_type vt{a, b};
        ContextFree::production_map_type prods;
        prods[S] = {prod0, prod1};
        prods[A] = {prod0, prod2, prod3};

        ContextFree grammar{vn, vt, prods, S};

        ContextFree::symbol_ptr_set_type reachable;
        auto new_grammar = grammar.remove_unreachable_symbols(reachable);

        REQUIRE(!reachable.empty());

        ContextFree::non_terminal_set_type new_vn{S};
        ContextFree::terminal_set_type new_vt{a};
        ContextFree::production_map_type new_prods;
        new_prods[S] = {prod0, prod1};

        ContextFree grammar_2{new_vn, new_vt, new_prods, S};

        ContextFree::symbol_ptr_set_type reachable_test{pS, pa};

        REQUIRE(reachable.size() == 2);
        CHECK(reachable == reachable_test);
        CHECK(new_grammar.vn().size() == 1);
        CHECK(new_grammar.vt().size() == 1);
        CHECK(new_grammar.productions().size() == 1);
        CHECK(new_grammar.initial_symbol() == S);
        CHECK(new_grammar == grammar_2);
    }

    SECTION("Complex", "[grammar][inferile]")
    {
        NonTerminalSymbol S{"S"}, A{"A"}, B{"B"}, C{"C"};
        TerminalSymbol a{"a"}, b{"b"}, c{"c"};

        SymbolPointer pS{new NonTerminalSymbol(S)},
                      pA{new NonTerminalSymbol(A)},
                      pB{new NonTerminalSymbol(B)},
                      pC{new NonTerminalSymbol(C)};
        SymbolPointer pa{new TerminalSymbol(a)}, pb{new TerminalSymbol(b)}, pc{new TerminalSymbol(c)};
        Production prod0{pa, pA}, prod1{pb, pC},
                   prod2{pb, pS}, prod3{pb, pC},
                   prod4{pc, pB},
                   prod5{pC, pb};

        ContextFree::non_terminal_set_type vn{S, A, B, C};
        ContextFree::terminal_set_type vt{a, b, c};
        ContextFree::production_map_type prods;
        prods[S] = {prod0, prod1};
        prods[A] = {prod2, prod3};
        prods[B] = {prod4};
        prods[C] = {prod5};

        ContextFree grammar{vn, vt, prods, S};

        ContextFree::symbol_ptr_set_type reachable;
        auto new_grammar = grammar.remove_unreachable_symbols(reachable);

        REQUIRE(!reachable.empty());

        ContextFree::non_terminal_set_type new_vn{S, A, C};
        ContextFree::terminal_set_type new_vt{a, b};
        ContextFree::production_map_type new_prods;
        new_prods[S] = {prod0, prod1};
        new_prods[A] = {prod2, prod3};
        new_prods[C] = {prod5};

        ContextFree grammar_2{new_vn, new_vt, new_prods, S};

        ContextFree::symbol_ptr_set_type reachable_test{pS, pA, pC, pa, pb};

        REQUIRE(reachable.size() == 5);
        CHECK(reachable == reachable_test);
        CHECK(new_grammar.vn().size() == 3);
        CHECK(new_grammar.vt().size() == 2);
        CHECK(new_grammar.productions().size() == 3);
        CHECK(new_grammar.initial_symbol() == S);
        CHECK(new_grammar == grammar_2);
    }
}


//ContextFree own(non_terminal_set_type &derives_epsilon,
//                simple_production_map_type &na,
//                non_terminal_set_type &fertile_symbols,
//                symbol_ptr_set_type &reachable_symbols) const;

//ContextFree epsilon_free(non_terminal_set_type &derives_epsilon) const;
//ContextFree remove_simple_productions(simple_production_map_type &na) const;

//ContextFree remove_unreachable_symbols(symbol_ptr_set_type &reachable_symbols) const;
//ContextFree remove_useless_symbols(non_terminal_set_type &fertile_symbols,
//                                   symbol_ptr_set_type &reachable_symbols) const;

//ContextFree factor(unsigned max_steps) const;
//ContextFree remove_recursion(resursion_map_type &recursions) const;

//bool emptiness() const;
//bool finitude() const;
//bool is_factored() const;
//bool has_recursion() const;
