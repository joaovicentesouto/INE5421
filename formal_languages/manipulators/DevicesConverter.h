#ifndef DEVICESCONVERTER_H
#define DEVICESCONVERTER_H

#include <formal_languages/devices/FiniteAutomaton.hpp>
#include <formal_languages/devices/Grammar.hpp>

namespace formal_device
{
namespace converter
{

class DevicesConverter
{
  public:
    using ndfa_type    = finite_automaton::NonDeterministic;
    using grammar_type = grammar::Regular;

    // Class constructors
    DevicesConverter() = default;

    DevicesConverter(const DevicesConverter &) = default;
    DevicesConverter &operator=(const DevicesConverter &) = default;

    DevicesConverter(DevicesConverter &&) = default;
    DevicesConverter &operator=(DevicesConverter &&) = default;

    ndfa_type convert(const grammar_type & grammar);
    grammar_type convert(const ndfa_type & ndfa);
};

}   // namespace converter
}   // namespace formal_device

#endif // DEVICESCONVERTER_H
