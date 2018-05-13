#ifndef PARSER_REGULAREXPRESSION_HPP
#define PARSER_REGULAREXPRESSION_HPP

#include <iostream>
//#include <boost/spirit/home/x3.hpp>
//#include <boost/fusion/include/adapt_struct.hpp>
//#include <boost/fusion/include/io.hpp>

//#include <boost/spirit/include/support_istream_iterator.hpp>
//#include <iostream>
//#include <sstream>

//namespace formal_devices
//{
//namespace expression
//{
//namespace ast
//{

//struct rexpr
//{
//    std::string m_left{""};
//    std::string m_operation{"."};
//    std::string m_right{""};
//};

//}
//}
//}

//BOOST_FUSION_ADAPT_STRUCT(formal_devices::expression::ast::rexpr, m_left, m_operation, m_right)

//namespace formal_devices
//{
//namespace expression
//{
//namespace parser {
//namespace x3 = boost::spirit::x3;
//    namespace ascii = boost::spirit::x3::ascii;

//    using x3::lit;
//    using x3::lexeme;
//    using ascii::char_;
//    using ascii::string;

//    x3::rule<class rexpr, ast::rexpr>       rexpr = "rexpr";
//    x3::rule<class rexpr_value, ast::rexpr> rexpr = "rexpr";

//    auto const closure =
//        '*' | '+' | '?';

//    auto const operation = '|';

//    auto const symbol =
//        char_("a-z");

//    auto const rexpr_value_def =
//        symbol >> symbol | symbol | rexpr;

//    auto const rexpr_key_value_def =
//        symbol >> '|' >> rexpr_value;

//    auto const rexpr_def =
//        '(' >> rexpr >> ')' >> closure |
//        rexpr >> closure |
//        rexpr_value;

//    BOOST_SPIRIT_DEFINE(rexpr_value, rexpr, rexpr_key_value);
//}
//}
//}

#endif
