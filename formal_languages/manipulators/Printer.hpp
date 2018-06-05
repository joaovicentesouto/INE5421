//! João Vicente Souto e Bruno Izaias Bonotto

#ifndef PRINTER_H
#define PRINTER_H

#include<string>
#include<iostream>
#include <formal_languages/devices/FiniteAutomaton.hpp>
#include <formal_languages/devices/Grammar.hpp>
#include <formal_languages/devices/RegularExpression.hpp>

namespace formal_device
{

std::ostream& operator<<(std::ostream& os, const finite_automaton::Deterministic& machine);
std::ostream& operator<<(std::ostream& os, const finite_automaton::NonDeterministic& machine);
std::ostream& operator<<(std::ostream& os, const grammar::Regular& reg_grammar);
std::ostream& operator<<(std::ostream& os, const expression::regular_ptr& expression);

}   // namespace formal_devices

#endif // PRINTER_H
