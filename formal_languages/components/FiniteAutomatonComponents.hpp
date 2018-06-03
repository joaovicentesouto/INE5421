#ifndef DEVICES_FINITEAUTOMATON_COMPONENTS_H
#define DEVICES_FINITEAUTOMATON_COMPONENTS_H

#include <string>
#include <utility>
#include <set>
#include <unordered_map>

namespace formal_device
{
namespace finite_automaton
{

class Symbol
{
public:
    using string_type = std::string;

    //! Default Construct Symbol
    /*!
        \brief Constructs an epsilon symbol.
    */
    Symbol() = default;

    //! Copy constructor
    Symbol(const Symbol &) = default;
    Symbol &operator=(const Symbol &) = default;

    //! Move constructor
    Symbol(Symbol &&) = default;
    Symbol &operator=(Symbol &&) = default;

    //! Construct Symbol
    /*!
        \brief Constructs an symbol with a copy string value.
        \param symbol Value name.
    */
    Symbol(const string_type &symbol);

    //! Construct Symbol
    /*!
        \brief Constructs an symbol with a moved string value.
        \param symbol Value name.
    */
    Symbol(string_type &&symbol);

    //! Equality operator (from another symbol)
    /*!
        \brief Verifies that symbols are the same.
        \param symbol Another symbol.
        \return True if contains the same value.
    */
    bool operator==(const Symbol &symbol) const;

    //! Equality operator (from string value)
    /*!
        \brief Verifies that a symbol contains the same value.
        \param symbol Another symbol.
        \return True if contains the same value.
    */
    bool operator==(const string_type &symbol) const;

    //! Less than operator
    /*!
        \brief It checks to see if one symbol is smaller than another.
        \param symbol Another symbol.
        \return True if is less than.
    */
    bool operator<(const Symbol &symbol) const;

    //! Get value
    /*!
        \brief Simple get.
        \return The name of the symbol.
    */
    string_type value() const;

private:
    string_type m_symbol{"&"};   //! Symbol name
};

class State
{
public:
    using string_type = std::string;

    //! Default Construct State
    /*!
        \brief Constructs an error state.
    */
    State() = default;

    //! Copy constructor
    State(const State &) = default;
    State &operator=(const State &) = default;

    //! Move constructor
    State(State &&) = default;
    State &operator=(State &&) = default;

    //! Construct State
    /*!
        \brief Constructs an state with a copy string value.
        \param state Value name.
    */
    State(const string_type &state);

    //! Construct State
    /*!
        \brief Constructs an state with a moved string value.
        \param state Value name.
    */
    State(string_type &&state);

    //! Equality operator (from another state)
    /*!
        \brief Verifies that states are the same.
        \param state Another state.
        \return True if contains the same value.
    */
    bool operator==(const State &state) const;

    //! Equality operator (from string value)
    /*!
        \brief Verifies that a state contains the same value.
        \param state Another state.
        \return True if contains the same value.
    */
    bool operator==(const string_type &state) const;

    //! Less than operator
    /*!
        \brief It checks to see if one state is smaller than another.
        \param state Another state.
        \return True if is less than.
    */
    bool operator<(const State &state) const;

    //! Get value
    /*!
        \brief Simple get.
        \return The name of the state.
    */
    string_type value() const;

private:
    string_type m_state{"Error"};   //! State name
};

} // namespace finite_automaton
} // namespace formal_device

#endif // DEVICES_FINITEAUTOMATON_COMPONENTS_H
