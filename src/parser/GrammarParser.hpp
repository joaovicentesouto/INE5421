#ifndef PARSER_REGULAR_GRAMMAR_HPP
#define PARSER_REGULAR_GRAMMAR_HPP

#include <iostream>
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <boost/spirit/include/support_istream_iterator.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

#include <src/formal_devices/Grammar.hpp>

namespace formal_device
{
namespace grammar
{

using string_type = Regular::symbol_type::string_type;

namespace ast
{
struct Production
{
    string_type m_production;
};

struct Line
{
    string_type m_symbol;
    std::vector<Production> m_productions;
};

struct Document
{
    std::vector<Line> m_lines;
};
}   // namespace ast
}   // namespace grammar
}   // namespace formal_devices

BOOST_FUSION_ADAPT_STRUCT(formal_device::grammar::ast::Production, m_production)
BOOST_FUSION_ADAPT_STRUCT(formal_device::grammar::ast::Line, m_symbol, m_productions)
BOOST_FUSION_ADAPT_STRUCT(formal_device::grammar::ast::Document, m_lines)

namespace formal_device
{
namespace grammar
{
namespace parser
{
    Regular make_regular_grammar(const string_type & file);

    namespace x3    = boost::spirit::x3;
    namespace ascii = x3::ascii;

    x3::rule<class production_, ast::Production> production{"production"};
    x3::rule<class line_, ast::Line>             line{"line"};
    x3::rule<class document_, ast::Document>     document{"document"};

    const auto identifier     = x3::lexeme[+x3::char_("a-zA-Z")];
    const auto production_def = identifier;
    const auto line_def       = identifier >> x3::lit("->") >> production % "|";
    const auto document_def   = line % x3::eol;

    BOOST_SPIRIT_DEFINE(production, line, document);
}   // namespace ast
}   // namespace grammar
}   // namespace formal_devices

#endif
