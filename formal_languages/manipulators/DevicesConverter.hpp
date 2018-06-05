#ifndef DEVICESCONVERTER_H
#define DEVICESCONVERTER_H

#include <algorithm>
#include <cctype>
#include <functional>
#include <formal_languages/devices/FiniteAutomaton.hpp>
#include <formal_languages/devices/Grammar.hpp>

namespace formal_device
{
namespace manipulator
{

class DevicesConverter
{
public:
    using dfa_type     = finite_automaton::Deterministic;
    using ndfa_type    = finite_automaton::NonDeterministic;
    using grammar_type = grammar::Regular;

    //! Default Constructor
    /*!
        \brief Build a DevicesConverter.
    */
    DevicesConverter() = default;

    //! Copy constructor
    DevicesConverter(const DevicesConverter &) = default;
    DevicesConverter &operator=(const DevicesConverter &) = default;

    //! Move constructor
    DevicesConverter(DevicesConverter &&) = default;
    DevicesConverter &operator=(DevicesConverter &&) = default;

    //! Convert Grammar to NDFA
    /*!
        \brief Convert a Grammar to a equivalent NDFA.
        \return Non deterministic.
    */
    ndfa_type convert(const grammar_type & grammar);

    //! Convert NDFA to Grammar
    /*!
        \brief Convert a NDFA to a equivalent Grammar.
        \return Grammar.
    */
    grammar_type convert(const ndfa_type & ndfa);
};

}   // namespace manipulator
}   // namespace formal_device

#endif // DEVICESCONVERTER_H
