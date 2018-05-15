#include "../catch.hpp"

#include <formal_languages/parsers/FiniteAutomatonParser.hpp>

using namespace formal_device::finite_automaton;

TEST_CASE("Finite Automaton: Symbol Parser", "[finite_automaton][parser]")
{
    std::string str =  "a";
    auto f = str.begin();
    auto l = str.end();

    ast::Symbol symbol;
    CHECK(phrase_parse(f, l, parser::symbol, parser::ascii::space, symbol));
    CHECK(symbol.m_value == "a");
}

TEST_CASE("Finite Automaton: Transition Symbol", "[finite_automaton][parser]")
{
    SECTION("FA Symbol Parser: one symbol", "[finite_automaton][parser]")
    {
        std::string str =  "+ | a";
        auto f = str.begin();
        auto l = str.end();

        ast::TransitionSymbols symbols;
        CHECK(phrase_parse(f, l, parser::transition_symbols, parser::ascii::space, symbols));
        CHECK(symbols.m_transition_symbols.front().m_value == "a");
    }

    SECTION("FA Symbol Parser: two symbol", "[finite_automaton][parser]")
    {
        std::string str =  "+ | a | b";
        auto f = str.begin();
        auto l = str.end();

        ast::TransitionSymbols symbols;
        CHECK(phrase_parse(f, l, parser::transition_symbols, parser::ascii::space, symbols));
        CHECK(symbols.m_transition_symbols.front().m_value == "a");
        CHECK(symbols.m_transition_symbols.back().m_value == "b");
    }

    SECTION("FA Symbol Parser: five symbol", "[finite_automaton][parser]")
    {
        std::string str =  "+ | a | b | c | d | e";
        auto f = str.begin();
        auto l = str.end();

        ast::TransitionSymbols symbols;
        CHECK(phrase_parse(f, l, parser::transition_symbols, parser::ascii::space, symbols));
        CHECK(symbols.m_transition_symbols.size() == 5);
        CHECK(symbols.m_transition_symbols.front().m_value == "a");
        CHECK(symbols.m_transition_symbols.back().m_value == "e");
    }
}

TEST_CASE("Finite Automaton: Transition of a state", "[finite_automaton][parser]")
{
    SECTION("FA Transition Parser: one state", "[finite_automaton][parser]")
    {
        std::string str =  "{A}";
        auto f = str.begin();
        auto l = str.end();

        ast::Transition transition;
        CHECK(phrase_parse(f, l, parser::transition, parser::ascii::space, transition));
        CHECK(transition.m_transitions.size() == 1);
        CHECK(transition.m_transitions.front().m_value == "A");
    }

    SECTION("FA Transition Parser: two states", "[finite_automaton][parser]")
    {
        std::string str =  "{A, B}";
        auto f = str.begin();
        auto l = str.end();

        ast::Transition transition;
        CHECK(phrase_parse(f, l, parser::transition, parser::ascii::space, transition));
        CHECK(transition.m_transitions.size() == 2);
        CHECK(transition.m_transitions.front().m_value == "A");
        CHECK(transition.m_transitions.back().m_value == "B");
    }

    SECTION("FA Transition Parser: five states", "[finite_automaton][parser]")
    {
        std::string str =  "{A, B, C, D, E}";
        auto f = str.begin();
        auto l = str.end();

        ast::Transition transition;
        CHECK(phrase_parse(f, l, parser::transition, parser::ascii::space, transition));
        CHECK(transition.m_transitions.size() == 5);
        CHECK(transition.m_transitions.front().m_value == "A");
        CHECK(transition.m_transitions.back().m_value == "E");
    }

    SECTION("FA Transition Parser: five states", "[finite_automaton][parser]")
    {
        std::string str =  "A, B, C, D, E";
        auto f = str.begin();
        auto l = str.end();

        ast::Transition transition;
        CHECK(phrase_parse(f, l, parser::transition, parser::ascii::space, transition));
        CHECK(transition.m_transitions.size() == 5);
        CHECK(transition.m_transitions.front().m_value == "A");
        CHECK(transition.m_transitions.back().m_value == "E");
    }
}

TEST_CASE("Finite Automaton: State", "[finite_automaton][parser]")
{
    SECTION("FA State Parser: one state", "[finite_automaton][parser]")
    {
        std::string str =  "S | A | S";
        auto f = str.begin();
        auto l = str.end();

        ast::State state;
        CHECK(phrase_parse(f, l, parser::state, parser::ascii::space, state));
        CHECK(state.m_state.m_value == "S");
        CHECK(state.m_transitions.size() == 2);

        CHECK(state.m_transitions.front().m_transitions.size() == 1);
        CHECK(state.m_transitions.front().m_transitions.front().m_value == "A");

        CHECK(state.m_transitions.back().m_transitions.size() == 1);
        CHECK(state.m_transitions.back().m_transitions.front().m_value == "S");
    }

    SECTION("FA State Parser: one final state", "[finite_automaton][parser]")
    {
        std::string str =  "*S | A | S";
        auto f = str.begin();
        auto l = str.end();

        ast::State state;
        CHECK(phrase_parse(f, l, parser::state, parser::ascii::space, state));
        CHECK(state.m_state.m_value == "*S");
        CHECK(state.m_transitions.size() == 2);

        CHECK(state.m_transitions.front().m_transitions.size() == 1);
        CHECK(state.m_transitions.front().m_transitions.front().m_value == "A");

        CHECK(state.m_transitions.back().m_transitions.size() == 1);
        CHECK(state.m_transitions.back().m_transitions.front().m_value == "S");
    }

    SECTION("FA Transition Parser: two states", "[finite_automaton][parser]")
    {
        std::string str =  "S | {A} | {S, B}";
        auto f = str.begin();
        auto l = str.end();

        ast::State state;
        CHECK(phrase_parse(f, l, parser::state, parser::ascii::space, state));
        CHECK(state.m_state.m_value == "S");
        CHECK(state.m_transitions.size() == 2);

        CHECK(state.m_transitions.front().m_transitions.size() == 1);
        CHECK(state.m_transitions.front().m_transitions.front().m_value == "A");

        CHECK(state.m_transitions.back().m_transitions.size() == 2);
        CHECK(state.m_transitions.back().m_transitions.front().m_value == "S");
        CHECK(state.m_transitions.back().m_transitions.back().m_value == "B");
    }
}

TEST_CASE("Finite Automaton: Document States", "[regular_expression][empty]")
{
    std::string str = ("+ | a |  b\n*S | A | S\nA | B | C");
    auto f = str.begin();
    auto l = str.end();

    ast::Document doc;
    CHECK(phrase_parse(f, l, parser::document, parser::ascii::blank, doc));
    CHECK(doc.m_transition_symbols.m_transition_symbols.size() == 2);
    CHECK(doc.m_states.size() == 2);

    SECTION("Transitions Symbol", "[regular_expression][empty]")
    {
        ast::TransitionSymbols & trans = doc.m_transition_symbols;
        CHECK(trans.m_transition_symbols.front().m_value == "a");
        CHECK(trans.m_transition_symbols.back().m_value == "b");
    }

    SECTION("State one", "[regular_expression][empty]")
    {
        ast::State state1 = doc.m_states.front();
        CHECK(state1.m_state.m_value == "*S");
        CHECK(state1.m_transitions.size() == 2);

        CHECK(state1.m_transitions.front().m_transitions.size() == 1);
        CHECK(state1.m_transitions.front().m_transitions.front().m_value == "A");

        CHECK(state1.m_transitions.back().m_transitions.size() == 1);
        CHECK(state1.m_transitions.back().m_transitions.front().m_value == "S");
    }

    SECTION("State two", "[regular_expression][empty]")
    {
        ast::State state2 = doc.m_states.back();
        CHECK(state2.m_state.m_value == "A");
        CHECK(state2.m_transitions.size() == 2);

        CHECK(state2.m_transitions.front().m_transitions.size() == 1);
        CHECK(state2.m_transitions.front().m_transitions.front().m_value == "B");

        CHECK(state2.m_transitions.back().m_transitions.size() == 1);
        CHECK(state2.m_transitions.back().m_transitions.front().m_value == "C");
    }
}

TEST_CASE("Finite Automaton: : File deterministic", "[regular_expression][empty]")
{
    std::ifstream ifs("./files/dfa.txt");
    CHECK(ifs.is_open());
    ifs >> std::noskipws;

    boost::spirit::istream_iterator f(ifs), l;

    ast::Document doc;
    CHECK(phrase_parse(f, l, parser::document, parser::ascii::blank, doc));
    CHECK(doc.m_transition_symbols.m_transition_symbols.size() == 2);
    CHECK(doc.m_states.size() == 2);

    SECTION("Transitions Symbol", "[regular_expression][empty]")
    {
        ast::TransitionSymbols & trans = doc.m_transition_symbols;
        CHECK(trans.m_transition_symbols.front().m_value == "a");
        CHECK(trans.m_transition_symbols.back().m_value == "b");
    }

    SECTION("State one", "[regular_expression][empty]")
    {
        ast::State state1 = doc.m_states.front();
        CHECK(state1.m_state.m_value == "*S");
        CHECK(state1.m_transitions.size() == 2);

        CHECK(state1.m_transitions.front().m_transitions.size() == 1);
        CHECK(state1.m_transitions.front().m_transitions.front().m_value == "A");

        CHECK(state1.m_transitions.back().m_transitions.size() == 1);
        CHECK(state1.m_transitions.back().m_transitions.front().m_value == "S");
    }

    SECTION("State two", "[regular_expression][empty]")
    {
        ast::State state2 = doc.m_states.back();
        CHECK(state2.m_state.m_value == "A");
        CHECK(state2.m_transitions.size() == 2);

        CHECK(state2.m_transitions.front().m_transitions.size() == 1);
        CHECK(state2.m_transitions.front().m_transitions.front().m_value == "B");

        CHECK(state2.m_transitions.back().m_transitions.size() == 1);
        CHECK(state2.m_transitions.back().m_transitions.front().m_value == "C");
    }
}

TEST_CASE("Finite Automaton: : File non deterministc", "[regular_expression][empty]")
{
    std::ifstream ifs("./files/ndfa.txt");
    CHECK(ifs.is_open());
    ifs >> std::noskipws;

    boost::spirit::istream_iterator f(ifs), l;

    ast::Document doc;
    CHECK(phrase_parse(f, l, parser::document, parser::ascii::blank, doc));
    CHECK(doc.m_transition_symbols.m_transition_symbols.size() == 2);
    CHECK(doc.m_states.size() == 2);

    SECTION("Transitions Symbol", "[regular_expression][empty]")
    {
        ast::TransitionSymbols & trans = doc.m_transition_symbols;
        CHECK(trans.m_transition_symbols.front().m_value == "a");
        CHECK(trans.m_transition_symbols.back().m_value == "b");
    }

    SECTION("State one", "[regular_expression][empty]")
    {
        ast::State state1 = doc.m_states.front();
        CHECK(state1.m_state.m_value == "->S");
        CHECK(state1.m_transitions.size() == 2);

        CHECK(state1.m_transitions.front().m_transitions.size() == 1);
        CHECK(state1.m_transitions.front().m_transitions.front().m_value == "A");

        CHECK(state1.m_transitions.back().m_transitions.size() == 1);
        CHECK(state1.m_transitions.back().m_transitions.front().m_value == "S");
    }

    SECTION("State two", "[regular_expression][empty]")
    {
        ast::State state2 = doc.m_states.back();
        CHECK(state2.m_state.m_value == "*A");
        CHECK(state2.m_transitions.size() == 2);

        CHECK(state2.m_transitions.front().m_transitions.size() == 2);
        CHECK(state2.m_transitions.front().m_transitions.front().m_value == "A");
        CHECK(state2.m_transitions.front().m_transitions.back().m_value == "B");

        CHECK(state2.m_transitions.back().m_transitions.size() == 1);
        CHECK(state2.m_transitions.back().m_transitions.front().m_value == "C");
    }
}
