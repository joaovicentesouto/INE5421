//! João Vicente Souto e Bruno Izaias Bonotto

#ifndef FINITEAUTOMATONPARSER_HPP
#define FINITEAUTOMATONPARSER_HPP

#include <regular_languages/model/devices/FiniteAutomaton.hpp>
#include <algorithm>
#include <iostream>

namespace formal_device
{
namespace parser
{

using namespace formal_device::finite_automaton;

using ndfa_type           = NonDeterministic;
using state_type          = NonDeterministic::state_type;
using state_set_type      = NonDeterministic::state_set_type;
using symbol_set_type     = NonDeterministic::symbol_set_type;
using non_det_transition_map_type = NonDeterministic::transition_map_type;

ndfa_type create_automaton(std::set<std::string> & symbols, std::set<std::string> & states,
                           std::map<std::string, std::map<std::string, std::set<std::string>>> & transitions);

}  // namespace parser
}  // namespace formal_devices


#endif // FINITEAUTOMATONPARSER_HPP
