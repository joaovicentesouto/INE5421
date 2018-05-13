#include "../catch.hpp"

#include <src/parser/FiniteAutomatonParser.hpp>

using namespace formal_devices::finite_automaton;

TEST_CASE("Finite Automaton Parser", "[finite_automaton][parser]")
{
    SECTION("FA Symbol Parser", "[finite_automaton][parser]")
    {
        std::string str =  "a";
        auto f = str.begin();
        auto l = str.end();

        ast::Symbol symbol;
        CHECK(phrase_parse(f, l, parser::symbol, parser::ascii::space, symbol));
        CHECK(symbol.m_value == "a");
    }

    SECTION("FA Transition Symbol", "[finite_automaton][parser]")
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

    SECTION("FA Symbol Parser", "[finite_automaton][parser]")
    {
        std::string str =  "a";
        auto f = str.begin();
        auto l = str.end();

        ast::Symbol symbol;
        CHECK(phrase_parse(f, l, parser::symbol, parser::ascii::space, symbol));
        CHECK(symbol.m_value == "a");
    }

    SECTION("FA Transition of a state", "[finite_automaton][parser]")
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

    SECTION("FA State", "[finite_automaton][parser]")
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

//    SECTION("Document States", "[regular_expression][empty]")
//    {
//        std::string str = ("+ | a |  b\n*S | A | S\nA | B | B");
//        auto f = str.begin();
//        auto l = str.end();

//        ast::Document doc;
//        CHECK(phrase_parse(f, l, parser::document, parser::ascii::space, doc));
//        CHECK(doc.m_lines.size() == 2);

//        ast::Line line = doc.m_lines.front();
//        CHECK(line.m_symbol == "S");
//        CHECK(line.m_productions.size() == 3);

//        for (auto prod : line.m_productions)
//            CHECK((prod.m_production == "aA" ||
//                   prod.m_production == "a"  ||
//                   prod.m_production == "b" ));

//        line = doc.m_lines.back();
//        CHECK(line.m_symbol == "A");
//        CHECK(line.m_productions.size() == 3);

//        for (auto prod : line.m_productions)
//            CHECK((prod.m_production == "bS" ||
//                   prod.m_production == "b"  ||
//                   prod.m_production == "c" ));
//    }
}

//const auto identifier             = x3::lexeme[+x3::char_("a-zA-Z0-9")];
//const auto symbol_def             = identifier;
//const auto transition_symbols_def = "+" >> symbol % "|";
//const auto transition_def         = -x3::lit("{") >> (symbol % ",") >> -x3::lit("{");
//const auto state_def              = symbol >> "|" >> transition % "|";
//const auto document_def           = transition_symbols >> "\n" >> (state % "\n");
