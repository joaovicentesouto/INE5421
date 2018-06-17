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

    SymbolPointer pS(new NonTerminalSymbol("S"));

    CHECK(grammar.first()[pS].empty());
    CHECK(*grammar.follow()[grammar.initial_symbol()].begin() == "$");
    CHECK(grammar.follow()[grammar.initial_symbol()].size() == 1);

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

        ContextFree::first_map_type first_test;
        first_test[pS] = {a};
        first_test[pA] = {a, b};
        first_test[pB] = {a, b};
        first_test[pa] = {a};
        first_test[pb] = {b};
        CHECK(ga.first() == first_test);
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

        ContextFree::first_map_type first_test;
        first_test[pS] = {a, b};
        first_test[pA] = {};
        first_test[pa] = {a};
        first_test[pb] = {b};
        first_test[pc] = {c};
        CHECK(grammar.first() == first_test);
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
    SECTION("Simple", "[grammar][unreachable_symbols]")
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

    SECTION("Complex", "[grammar][unreachable_symbols]")
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

TEST_CASE("Grammar: Remove useless symbols", "[grammar][function]")
{
    SECTION("Simple", "[grammar][useless_symbol]")
    {
        NonTerminalSymbol S{"S"}, A{"A"}, B{"B"};
        TerminalSymbol a{"a"}, b{"b"}, c{"c"};

        SymbolPointer pS{new NonTerminalSymbol(S)},
                      pA{new NonTerminalSymbol(A)},
                      pB{new NonTerminalSymbol(B)};
        SymbolPointer pa{new TerminalSymbol(a)}, pb{new TerminalSymbol(b)}, pc{new TerminalSymbol(c)};
        Production prod0{pa, pA}, prod1{pb, pS}, prod2{pb},
                   prod3{pc, pA},
                   prod4{pb, pB}, prod5{pb};

        ContextFree::non_terminal_set_type vn{S, A, B};
        ContextFree::terminal_set_type vt{a, b, c};
        ContextFree::production_map_type prods;
        prods[S] = {prod0, prod1, prod2};
        prods[A] = {prod3};
        prods[B] = {prod4, prod5};

        ContextFree grammar{vn, vt, prods, S};

        ContextFree::non_terminal_set_type fertible;
        ContextFree::symbol_ptr_set_type reachable;
        auto new_grammar = grammar.remove_useless_symbols(fertible, reachable);

        REQUIRE((!fertible.empty() && !reachable.empty()));

        ContextFree::non_terminal_set_type new_vn{S};
        ContextFree::terminal_set_type new_vt{b};
        ContextFree::production_map_type new_prods;
        new_prods[S] = {prod1, prod2};

        ContextFree grammar_2{new_vn, new_vt, new_prods, S};

        ContextFree::non_terminal_set_type fertible_test{S, B};
        ContextFree::symbol_ptr_set_type reachable_test{pS, pb};

        REQUIRE(fertible.size() == 2);
        REQUIRE(reachable.size() == 2);

        CHECK(fertible == fertible_test);
        CHECK(reachable == reachable_test);
        CHECK(new_grammar.vn().size() == 1);
        CHECK(new_grammar.vt().size() == 1);
        CHECK(new_grammar.productions().size() == 1);
        CHECK(new_grammar.initial_symbol() == S);
        CHECK(new_grammar == grammar_2);
    }

    SECTION("Complex", "[grammar][useless_symbol]")
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

TEST_CASE("Grammar: Turn on Epsilon Free", "[grammar][function]")
{
    SECTION("Simple", "[grammar][epsilon_free]")
    {
        NonTerminalSymbol S{"S"}, A{"A"};
        TerminalSymbol a{"a"}, b{"b"}, epsilon{"&"};

        SymbolPointer pS{new NonTerminalSymbol(S)},
                      pA{new NonTerminalSymbol(A)};
        SymbolPointer pa{new TerminalSymbol(a)}, pb{new TerminalSymbol(b)}, pEpsilon{new TerminalSymbol(epsilon)};
        Production prod0{pa, pA}, prod1{pb}, prod2{pEpsilon}, prod3{pa};

        ContextFree::non_terminal_set_type vn{S, A};
        ContextFree::terminal_set_type vt{a, b, epsilon};
        ContextFree::production_map_type prods;
        prods[S] = {prod0};
        prods[A] = {prod1, prod2};

        ContextFree grammar{vn, vt, prods, S};

        ContextFree::non_terminal_set_type derives_epsilon;
        auto new_grammar = grammar.epsilon_free(derives_epsilon);

        REQUIRE(!derives_epsilon.empty());

        ContextFree::production_map_type new_prods;
        new_prods[S] = {prod0, prod3};
        new_prods[A] = {prod1};

        ContextFree grammar_2{vn, vt, new_prods, S};

        ContextFree::non_terminal_set_type derives_epsilon_test{A};

        REQUIRE(derives_epsilon.size() == 1);
        CHECK(derives_epsilon == derives_epsilon_test);
        CHECK(new_grammar == grammar_2);
    }

    SECTION("Complex", "[grammar][epsilon_free]")
    {
        NonTerminalSymbol S_linha{"S\'"}, S{"S"}, A{"A"}, B{"B"}, C{"C"};
        TerminalSymbol a{"a"}, b{"b"}, c{"c"}, epsilon{"&"};

        SymbolPointer pS{new NonTerminalSymbol(S)},
                      pA{new NonTerminalSymbol(A)},
                      pB{new NonTerminalSymbol(B)},
                      pC{new NonTerminalSymbol(C)};
        SymbolPointer pa{new TerminalSymbol(a)},
                      pb{new TerminalSymbol(b)},
                      pc{new TerminalSymbol(c)},
                      pEpsilon{new TerminalSymbol(epsilon)};
        Production prod0{pA, pB}, prod1{pA, pC},
                   prod2{pa, pA}, prod3{pEpsilon},
                   prod4{pb, pB}, prod5{pEpsilon},
                   prod6{pc, pC}, prod7{pc};

        ContextFree::non_terminal_set_type vn{S, A, B, C};
        ContextFree::terminal_set_type vt{a, b, c, epsilon};
        ContextFree::production_map_type prods;
        prods[S] = {prod0, prod1};
        prods[A] = {prod2, prod3};
        prods[B] = {prod4, prod5};
        prods[C] = {prod6, prod7};

        ContextFree grammar{vn, vt, prods, S};

        ContextFree::first_map_type first_test;
        first_test[pS] = {a, b, c, epsilon};
        first_test[pA] = {a, epsilon};
        first_test[pB] = {b, epsilon};
        first_test[pC] = {c};
        first_test[pa] = {a};
        first_test[pb] = {b};
        first_test[pc] = {c};
        first_test[pEpsilon] = {epsilon};
        CHECK(grammar.first() == first_test);

        ContextFree::non_terminal_set_type derives_epsilon;
        auto new_grammar = grammar.epsilon_free(derives_epsilon);

        REQUIRE(!derives_epsilon.empty());

        SymbolPointer pS_linha(new NonTerminalSymbol(S_linha));
        Production prod_a{pa}, prod_b{pb}, prod_A{pA}, prod_B{pB}, prod_C{pC}, prodEp{pEpsilon};


        ContextFree::non_terminal_set_type new_vn{S_linha, S, A, B, C};
        ContextFree::production_map_type new_prods;
        new_prods[S_linha] = {prod0, prod1, prod_A, prod_B, prod_C, prodEp};
        new_prods[S] = {prod0, prod1, prod_A, prod_B, prod_C};
        new_prods[A] = {prod2, prod_a};
        new_prods[B] = {prod4, prod_b};
        new_prods[C] = {prod6, prod7};

        ContextFree grammar_2{new_vn, vt, new_prods, S_linha};

        ContextFree::non_terminal_set_type derives_epsilon_test{S, A, B};

        REQUIRE(derives_epsilon.size() == 3);
        CHECK(derives_epsilon == derives_epsilon_test);
        CHECK(new_grammar == grammar_2);
    }
}

TEST_CASE("Grammar: Remove simple productions", "[grammar][function]")
{
    SECTION("Simple", "[grammar][simple_productions]")
    {
        NonTerminalSymbol S{"S"}, A{"A"};
        TerminalSymbol a{"a"}, b{"b"};

        SymbolPointer pS{new NonTerminalSymbol(S)},
                      pA{new NonTerminalSymbol(A)};
        SymbolPointer pa{new TerminalSymbol(a)}, pb{new TerminalSymbol(b)};
        Production prod0{pA}, prod1{pa, pA}, prod2{pa}, prod3{pb};

        ContextFree::non_terminal_set_type vn{S, A};
        ContextFree::terminal_set_type vt{a, b};
        ContextFree::production_map_type prods;
        prods[S] = {prod0, prod2};
        prods[A] = {prod0, prod1, prod3};

        ContextFree grammar{vn, vt, prods, S};

        ContextFree::simple_production_map_type na;
        auto new_grammar = grammar.remove_simple_productions(na);

        REQUIRE(!na.empty());

        ContextFree::production_map_type new_prods;
        new_prods[S] = {prod2, prod1, prod3};
        new_prods[A] = {prod1, prod3};

        ContextFree grammar_2{vn, vt, new_prods, S};

        ContextFree::simple_production_map_type na_test;
        na_test[S] = {S, A};
        na_test[A] = {A};

        REQUIRE(na.size() == 2);
        CHECK(na == na_test);
        CHECK(new_grammar.vn() == vn);
        CHECK(new_grammar.vt() == vt);
        CHECK(new_grammar.initial_symbol() == S);
        CHECK(new_grammar.productions() == new_prods);
        CHECK(new_grammar == grammar_2);
    }

    SECTION("Complex", "[grammar][simple_productions]")
    {
        NonTerminalSymbol S{"S"}, A{"A"}, B{"B"}, C{"C"};
        TerminalSymbol a{"a"}, b{"b"}, c{"c"}, epsilon{"&"};

        SymbolPointer pS{new NonTerminalSymbol(S)},
                      pA{new NonTerminalSymbol(A)},
                      pB{new NonTerminalSymbol(B)},
                      pC{new NonTerminalSymbol(C)};
        SymbolPointer pa{new TerminalSymbol(a)},
                      pb{new TerminalSymbol(b)},
                      pc{new TerminalSymbol(c)},
                      pEpsilon{new TerminalSymbol(epsilon)};
        Production prod0{pA}, prod1{pC},
                   prod2{pa, pA}, prod3{pEpsilon},
                   prod4{pS}, prod5{pB, pa},
                   prod6{pc, pC}, prod7{pB};

        ContextFree::non_terminal_set_type vn{S, A, B, C};
        ContextFree::terminal_set_type vt{a, b, c, epsilon};
        ContextFree::production_map_type prods;
        prods[S] = {prod0, prod1};
        prods[A] = {prod2, prod3};
        prods[B] = {prod4, prod5};
        prods[C] = {prod6, prod7};

        ContextFree grammar{vn, vt, prods, S};

        ContextFree::simple_production_map_type na;
        auto new_grammar = grammar.remove_simple_productions(na);

        REQUIRE(!na.empty());

        ContextFree::production_map_type new_prods;
        new_prods[S] = {prod2, prod3, prod5, prod6};
        new_prods[A] = {prod2, prod3};
        new_prods[B] = {prod2, prod3, prod5, prod6};
        new_prods[C] = {prod2, prod3, prod5, prod6};

        ContextFree grammar_2{vn, vt, new_prods, S};

        ContextFree::simple_production_map_type na_test;
        na_test[S] = {S, A, B, C};
        na_test[A] = {A};
        na_test[B] = {S, A, B, C};
        na_test[C] = {S, A, B, C};

        REQUIRE(na.size() == 4);
        CHECK(na == na_test);
        CHECK(new_grammar.vn() == vn);
        CHECK(new_grammar.vt() == vt);
        CHECK(new_grammar.initial_symbol() == S);
        CHECK(new_grammar.productions() == new_prods);
        CHECK(new_grammar == grammar_2);
    }
}

TEST_CASE("Grammar: Transform a grammar on own grammar", "[grammar][function]")
{
    SECTION("Simple", "[grammar][own]")
    {

//        S -> AC | BD
//        A -> aA | &
//        B -> bB | B
//        C -> cC | c
//        D -> aD | a

        NonTerminalSymbol S{"S"}, A{"A"}, B{"B"}, C{"C"}, D{"D"};
        TerminalSymbol a{"a"}, b{"b"}, c{"c"}, epsilon{"&"};

        SymbolPointer pS{new NonTerminalSymbol(S)},
                      pA{new NonTerminalSymbol(A)},
                      pB{new NonTerminalSymbol(B)},
                      pC{new NonTerminalSymbol(C)},
                      pD{new NonTerminalSymbol(D)};
        SymbolPointer pa{new TerminalSymbol(a)},
                      pb{new TerminalSymbol(b)},
                      pc{new TerminalSymbol(c)},
                      pEpsilon{new TerminalSymbol(epsilon)};
        Production prod_AC{pA, pC}, prod_BD{pB, pD},
                   prod_aA{pa, pA}, prod_ep{pEpsilon},
                   prod_bB{pb, pB}, prod_B{pB},
                   prod_cC{pc, pC}, prod_c{pc},
                   prod_aD{pa, pD}, prod_a{pa};

        ContextFree::non_terminal_set_type vn{S, A, B, C, D};
        ContextFree::terminal_set_type vt{a, b, c, epsilon};
        ContextFree::production_map_type prods;
        prods[S] = {prod_AC, prod_BD};
        prods[A] = {prod_aA, prod_ep};
        prods[B] = {prod_bB, prod_B};
        prods[C] = {prod_cC, prod_c};
        prods[D] = {prod_aD, prod_a};

        ContextFree grammar{vn, vt, prods, S};

        ContextFree::non_terminal_set_type derives_epsilon;
        ContextFree::simple_production_map_type na;
        ContextFree::non_terminal_set_type fertible;
        ContextFree::symbol_ptr_set_type reachable;

        auto new_grammar = grammar.own(derives_epsilon, na, fertible, reachable);

        REQUIRE((!derives_epsilon.empty() && !na.empty() && !fertible.empty() && !reachable.empty()));

        ContextFree::non_terminal_set_type new_vn{S, A, C};
        ContextFree::terminal_set_type new_vt{a, c};
        ContextFree::production_map_type new_prods;
        new_prods[S] = {prod_AC, prod_cC, prod_c};
        new_prods[A] = {prod_aA, prod_a};
        new_prods[C] = {prod_cC, prod_c};

        ContextFree grammar_2{new_vn, new_vt, new_prods, S};

        ContextFree::non_terminal_set_type derives_epsilon_test{A};
        ContextFree::simple_production_map_type na_test;
        na_test[S] = {S, C};
        na_test[A] = {A};
        na_test[B] = {B};
        na_test[C] = {C};
        na_test[D] = {D};

        ContextFree::non_terminal_set_type fertible_test{S, A, C, D};
        ContextFree::symbol_ptr_set_type reachable_test{pS, pA, pC, pa, pc};

        CHECK(derives_epsilon == derives_epsilon_test);
        CHECK(na == na_test);
        CHECK(fertible == fertible_test);
        CHECK(reachable == reachable_test);
        CHECK(new_grammar == grammar_2);
    }
}

TEST_CASE("Grammar: Emptiness", "[grammar][function]")
{
    ContextFree grammar;

    CHECK(grammar.emptiness());

    NonTerminalSymbol S{"S"}, A{"A"}, B{"B"};
    TerminalSymbol a{"a"}, b{"b"};

    SymbolPointer pS{new NonTerminalSymbol(S)}, pA{new NonTerminalSymbol(A)}, pB{new NonTerminalSymbol(B)};
    SymbolPointer pa{new TerminalSymbol(a)}, pb{new TerminalSymbol(b)};
    Production prod_SA{pS, pA}, prod_aAB{pa, pA, pB}, prod_BBa{pB, pB, pa}, prod_ba{pb, pa};

    ContextFree::non_terminal_set_type vn{S, A, B};
    ContextFree::terminal_set_type vt{a, b};
    ContextFree::production_map_type prods;
    prods[S] = {prod_SA, prod_ba};
    prods[A] = {prod_ba};
    prods[B] = {prod_aAB, prod_BBa};

    grammar = ContextFree{vn, vt, prods, S};
    CHECK(!grammar.emptiness());

    prods[S] = {prod_SA, prod_BBa};
    prods[A] = {prod_SA, prod_aAB};

    grammar = ContextFree{vn, vt, prods, S};
    CHECK(grammar.emptiness());
}

TEST_CASE("Grammar: Finitiness", "[grammar][function]")
{
    ContextFree grammar;

    CHECK(grammar.finitiness());

    NonTerminalSymbol S{"S"}, A{"A"};
    TerminalSymbol a{"a"}, b{"b"};

    SymbolPointer pS{new NonTerminalSymbol(S)}, pA{new NonTerminalSymbol(A)};
    SymbolPointer pa{new TerminalSymbol(a)}, pb{new TerminalSymbol(b)};
    Production prod_a{pa}, prod_b{pb}, prod_bA{pb, pA}, prod_aS{pa, pS};

    ContextFree::non_terminal_set_type vn{S, A};
    ContextFree::terminal_set_type vt{a, b};
    ContextFree::production_map_type prods;
    prods[S] = {prod_bA, prod_b};
    prods[A] = {prod_a, prod_b};

    grammar = ContextFree{vn, vt, prods, S};
    CHECK(grammar.finitiness());

    prods[S] = {prod_bA, prod_b};
    prods[A] = {prod_a, prod_aS};

    grammar = ContextFree{vn, vt, prods, S};
    CHECK(!grammar.finitiness());
}

TEST_CASE("Grammar: G has recursion?", "[grammar][function]")
{
    ContextFree grammar;

    CHECK(!grammar.has_recursion());

    NonTerminalSymbol S{"S"}, A{"A"};
    TerminalSymbol a{"a"}, b{"b"};

    SymbolPointer pS{new NonTerminalSymbol(S)}, pA{new NonTerminalSymbol(A)};
    SymbolPointer pa{new TerminalSymbol(a)}, pb{new TerminalSymbol(b)};
    Production prod_a{pa}, prod_b{pb}, prod_bA{pb, pA}, prod_aS{pa, pS}, prod_Sa{pS, pa}, prod_AS{pA, pS};

    ContextFree::non_terminal_set_type vn{S, A};
    ContextFree::terminal_set_type vt{a, b};
    ContextFree::production_map_type prods;
    prods[S] = {prod_bA, prod_b};
    prods[A] = {prod_a, prod_b};

    ContextFree::first_map_type first;
    first[pS] = {b};
    first[pA] = {a, b};
    first[pa] = {a};
    first[pb] = {b};
    ContextFree::follow_map_type follow;
    follow[S] = {TerminalSymbol("$")};
    follow[A] = {TerminalSymbol("$")};

    grammar = ContextFree{vn, vt, prods, S};
    CHECK(!grammar.has_recursion());
    CHECK(grammar.first() == first);
    CHECK(grammar.follow() == follow);

    prods[S] = {prod_bA, prod_b, prod_Sa};
    prods[A] = {prod_a, prod_aS, prod_AS};

    first[pS] = {b};
    first[pA] = {a};
    follow[S] = {TerminalSymbol("$"), a, b};
    follow[A] = {TerminalSymbol("$"), a, b};

    grammar = ContextFree{vn, vt, prods, S};
    CHECK(grammar.has_recursion());
    CHECK(grammar.first() == first);
    CHECK(grammar.follow() == follow);
}

TEST_CASE("Grammar: G is fatored?", "[grammar][function]")
{
    ContextFree grammar;

    CHECK(grammar.is_factored());

    NonTerminalSymbol S{"S"}, A{"A"};
    TerminalSymbol a{"a"}, b{"b"};

    SymbolPointer pS{new NonTerminalSymbol(S)}, pA{new NonTerminalSymbol(A)};
    SymbolPointer pa{new TerminalSymbol(a)}, pb{new TerminalSymbol(b)};
    Production prod_a{pa}, prod_b{pb}, prod_bA{pb, pA}, prod_aS{pa, pS}, prod_Sa{pS, pa}, prod_AS{pA, pS};

    ContextFree::non_terminal_set_type vn{S, A};
    ContextFree::terminal_set_type vt{a, b};
    ContextFree::production_map_type prods;
    prods[S] = {prod_bA, prod_b};
    prods[A] = {prod_a, prod_b};

    grammar = ContextFree{vn, vt, prods, S};
    CHECK(!grammar.is_factored());

    prods[S] = {prod_aS, prod_bA};
    prods[A] = {prod_a, prod_b};

    grammar = ContextFree{vn, vt, prods, S};
    CHECK(grammar.is_factored());
}

TEST_CASE("Grammar: Remove recursion", "[grammar][function]")
{
    NonTerminalSymbol S{"S"}, A{"A"}, S_linha{"S\'"}, A_linha{"A\'"};
    TerminalSymbol a{"a"}, b{"b"}, epsilon{"&"};

    SymbolPointer pS{new NonTerminalSymbol(S)}, pA{new NonTerminalSymbol(A)},
                  pS_linha{new NonTerminalSymbol(S_linha)}, pA_linha{new NonTerminalSymbol(A_linha)};

    SymbolPointer pa{new TerminalSymbol(a)}, pb{new TerminalSymbol(b)}, pE{new TerminalSymbol(epsilon)};

    Production prod_Sa{pS, pa}, prod_SAa{pS, pA, pa}, prod_b{pb}, prod_Ab{pA, pb};

    ContextFree::non_terminal_set_type vn{S, A};
    ContextFree::terminal_set_type vt{a, b};
    ContextFree::production_map_type prods;
    prods[S] = {prod_Sa, prod_SAa, prod_b};
    prods[A] = {prod_Ab, prod_SAa, prod_b};

    ContextFree grammar = ContextFree{vn, vt, prods, S};

    ContextFree::recursion_map_type recursion;
    auto new_grammar = grammar.remove_recursion(recursion);

    CHECK(grammar.has_recursion());
    REQUIRE(!recursion.empty());

    Production prod_bSl{pb, pS_linha}, prod_ep{pE},
        prod_aSl{pa, pS_linha}, prod_AaSl{pA, pa, pS_linha},
        prod_SAaAl{pS, pA, pa, pA_linha}, prod_bAl{pb, pA_linha};

    ContextFree::non_terminal_set_type new_vn{S, A, S_linha, A_linha};
    ContextFree::terminal_set_type new_vt{a, b, epsilon};
    ContextFree::production_map_type new_prods;
    new_prods[S] = {prod_bSl};
    new_prods[S_linha] = {prod_aSl, prod_AaSl, prod_ep};
    new_prods[A] = {prod_SAaAl, prod_bAl};
    new_prods[A_linha] = {prod_bAl, prod_ep};

    ContextFree grammar_2{new_vn, new_vt, new_prods, S};

    ContextFree::recursion_map_type rec;
    rec[S][ContextFree::Recursion::Direct] = {S};
    rec[S][ContextFree::Recursion::Indirect] = {};
    rec[A][ContextFree::Recursion::Direct] = {A};
    rec[A][ContextFree::Recursion::Indirect] = {};

    CHECK(!new_grammar.has_recursion());
    CHECK(recursion == rec);
    CHECK(new_grammar == grammar_2);
}

TEST_CASE("Grammar: Fator a grammar", "[grammar][function]")
{
    NonTerminalSymbol S{"S"}, A{"A"}, B{"B"}, S_linha{"S0"}, B_linha{"B0"};
    TerminalSymbol a{"a"}, b{"b"}, c{"c"}, epsilon{"&"};

    SymbolPointer pS{new NonTerminalSymbol(S)}, pA{new NonTerminalSymbol(A)}, pB{new NonTerminalSymbol(B)},
                  pS_linha{new NonTerminalSymbol(S_linha)}, pB_linha{new NonTerminalSymbol(B_linha)};

    SymbolPointer pa{new TerminalSymbol(a)}, pb{new TerminalSymbol(b)}, pc{new TerminalSymbol(c)}, pE{new TerminalSymbol(epsilon)};

    Production prod_aA{pa, pA}, prod_aB{pa, pB},
                prod_bA{pb, pA}, prod_ep{pE},
                prod_cS{pc, pS}, prod_c{pc};

    ContextFree::non_terminal_set_type vn{S, A, B};
    ContextFree::terminal_set_type vt{a, b, c, epsilon};
    ContextFree::production_map_type prods;
    prods[S] = {prod_aA, prod_aB};
    prods[A] = {prod_bA, prod_ep};
    prods[B] = {prod_cS, prod_c};

    ContextFree grammar = ContextFree{vn, vt, prods, S};

    REQUIRE(!grammar.is_factored());

    auto new_grammar = grammar.factor(10);

    Production prod_cB_l{pc, pB_linha}, prod_aS_l{pa, pS_linha}, prod_A{pA}, prod_B{pB}, prod_S{pS};

    ContextFree::non_terminal_set_type new_vn{S, A, B, S_linha, B_linha};
    ContextFree::production_map_type new_prods;
    new_prods[S] = {prod_aS_l};
    new_prods[S_linha] = {prod_A, prod_S, prod_ep};
    new_prods[A] = {prod_bA, prod_ep};
    new_prods[B] = {prod_cB_l};
    new_prods[B_linha] = {prod_S, prod_ep};

    ContextFree grammar_2{new_vn, vt, new_prods, S};

    CHECK(new_grammar.is_factored());
    CHECK(new_grammar == grammar_2);
}

//ContextFree factor(unsigned max_steps) const;
//ContextFree remove_recursion(recursion_map_type &recursions) const;

//bool is_factored() const;
