#ifndef PARSER_FINITEAUTOMATON_H
#define PARSER_FINITEAUTOMATON_H

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
