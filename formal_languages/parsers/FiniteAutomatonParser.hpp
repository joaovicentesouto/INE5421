#ifndef PARSER_FINITEAUTOMATON_HPP
#define PARSER_FINITEAUTOMATON_HPP

#include <iostream>
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <boost/spirit/include/support_istream_iterator.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

namespace formal_device
{
namespace finite_automaton
{
namespace ast
{

struct Symbol
{
    std::string m_value;
};

struct TransitionSymbols
{
    std::vector<Symbol> m_transition_symbols;
};

struct Transition
{
    std::vector<Symbol> m_transitions;
};

struct State
{
    Symbol m_state;
    std::vector<Transition> m_transitions;
};

struct FADocument
{
    TransitionSymbols m_transition_symbols;
    std::vector<State> m_states;
};

}
}
}

BOOST_FUSION_ADAPT_STRUCT(formal_device::finite_automaton::ast::Symbol, m_value)
BOOST_FUSION_ADAPT_STRUCT(formal_device::finite_automaton::ast::TransitionSymbols, m_transition_symbols)
BOOST_FUSION_ADAPT_STRUCT(formal_device::finite_automaton::ast::Transition, m_transitions)
BOOST_FUSION_ADAPT_STRUCT(formal_device::finite_automaton::ast::State, m_state, m_transitions)
BOOST_FUSION_ADAPT_STRUCT(formal_device::finite_automaton::ast::FADocument, m_transition_symbols, m_states)

namespace formal_device
{
namespace finite_automaton
{
namespace parser {
    namespace x3    = boost::spirit::x3;
    namespace ascii = x3::ascii;

    x3::rule<class symbol_, ast::Symbol>         symbol{"symbol"};
    x3::rule<class transition_symbols_, ast::TransitionSymbols> transition_symbols{"transition_symbols"};
    x3::rule<class transition_, ast::Transition> transition{"transition"};
    x3::rule<class state_, ast::State>           state{"state"};
    x3::rule<class FADocument, ast::FADocument>     FADocument{"FADocument"};

    const auto identifier             = x3::lexeme[+x3::char_("->a-zA-Z0-9*") - '\n'];
    const auto symbol_def             = identifier;
    const auto transition_symbols_def = x3::lit("+ |") >> symbol % "|";
    const auto transition_def         = -x3::lit("{") >> (symbol % ",") >> -x3::lit("}");
    const auto state_def              = symbol >> "|" >> transition % "|";
    const auto FADocument_def         = transition_symbols >> x3::eol >> (state % x3::eol);

    BOOST_SPIRIT_DEFINE(symbol, transition_symbols, transition, state, FADocument);
}
}
}

#endif
