#ifndef PARSER_FINITEAUTOMATON_H
#define PARSER_FINITEAUTOMATON_H

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include <string>
#include <vector>
#include <iostream>

#include <src/formal_devices/FiniteAutomaton.hpp>

namespace formal_device
{
namespace parser
{

auto make_finite_automaton(const std::string &file);

} // namespace parser
} // namespace formal_device

#endif // PARSER_FINITEAUTOMATON_H
