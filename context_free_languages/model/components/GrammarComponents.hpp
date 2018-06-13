//! João Vicente Souto e Bruno Izaias Bonotto

#ifndef DEVICES_GRAMMAR_COMPONENTS_HPP
#define DEVICES_GRAMMAR_COMPONENTS_HPP

#include <utility>
#include <string>
#include <regex>
#include <set>
#include <vector>

namespace formal_device
{
namespace grammar
{

class Symbol
{
  public:
    using string_type                       = std::string;
    template <class T> using container_type = std::set<T>;

    //! Destructor
    ~Symbol() = default;

    //! Get value
    /*!
        \brief Simple get.
        \return The name of the symbol.
    */
    virtual string_type value() const = 0;

    //! Terminal check
    /*!
        \brief Verifies whether a symbol is terminal or not (belongs to A-Z or &).
        \return True if is a terminal symbol.
    */
    virtual bool is_terminal() const = 0;

    virtual const symbol_ptr_containter_type& first() const = 0;

    virtual const symbol_ptr_containter_type& follow() const = 0;

    //! Equality operator (from another symbol)
    /*!
        \brief Verifies that symbols are the same.
        \param symbol Another symbol.
        \return True if contains the same value.
    */
    virtual bool operator==(const Symbol &symbol) const = 0;

    //! Equality operator (from string value)
    /*!
        \brief Verifies that a symbol contains the same value.
        \param symbol Another symbol.
        \return True if contains the same value.
    */
    virtual bool operator==(const string_type &symbol) const = 0;

    //! Less than operator
    /*!
        \brief It checks to see if one symbol is smaller than another.
        \param symbol Another symbol.
        \return True if is less than.
    */
    virtual bool operator<(const Symbol &symbol) const = 0;
};

class SymbolPointer : std::shared_ptr<Symbol>
{
public:
    using symbol_type = Symbol;

    // operator < and ==

}

class SymbolSet : public SymbolPointer::symbol_type::container_type<SymbolPointer>
{
public:

    SymbolSet() = default;
    ~SymbolSet() = default;

    bool contains(SymbolPointer symbol);
}

class TerminalSymbol : public Symbol
{
  public:
    friend class Production;

    // using string_type                = Symbol::string;
    // using symbol_ptr_containter_type = Symbol::symbol_ptr_containter_type;

    TerminalSymbol() = default;

    //! Destructor
    ~TerminalSymbol() = default;

    //! Get value
    /*!
        \brief Simple get.
        \return The name of the symbol.
    */
    string_type value() const;

    //! Terminal check
    /*!
        \brief Verifies whether a symbol is terminal or not (belongs to A-Z or &).
        \return True if is a terminal symbol.
    */
    bool is_terminal() const;

    const symbol_ptr_containter_type& first() const;

    const symbol_ptr_containter_type& follow() const;

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

private:
    string_type                m_value;
};

class NonTerminalSymbol : public Symbol
{
  public:
    friend class Production;

    // using string_type                = Symbol::string;
    // using symbol_ptr_containter_type = Symbol::symbol_ptr_containter_type;

    NonTerminalSymbol() = default;

    //! Destructor
    ~NonTerminalSymbol() = default;

    //! Get value
    /*!
        \brief Simple get.
        \return The name of the symbol.
    */
    string_type value() const;

    //! Terminal check
    /*!
        \brief Verifies whether a symbol is terminal or not (belongs to A-Z or &).
        \return True if is a terminal symbol.
    */
    bool is_terminal() const;

    const symbol_ptr_containter_type& first() const;

    const symbol_ptr_containter_type& follow() const;

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

private:
    string_type                m_value;
    symbol_ptr_containter_type m_first;
    symbol_ptr_containter_type m_follow;
};

class Production
{
  public:
    using symbol_type                = Symbol;
    using string_type                = symbol_type::string_type;
    using symbol_ptr_containter_type = std::vector<symbol_type*>;

    Production() = default;

    //! Default Destructor
    /*!
        \brief To implement a pure interface.
    */
    ~Production() = default;

    //! Equality operator.
    /*!
        \brief Check to see if they make the same changes.
        \param prod Another Production.
        \return True if are make the same changes.
    */
    bool operator==(const Production &prod) const;

    //! Less than operator
    /*!
        \brief It checks to see if producitons is smaller than another.
        \param prod Another Production.
        \return True if is less than.
    */
    bool operator<(const Production &prod) const;

    //! Transform Production to string
    /*!
        \brief Representation of the production in the form of a string.
        \return The string representation.
    */
    string_type to_string() const;

private:
    symbol_ptr_containter_type m_production;
};

} // namespace grammar
} // namespace formal_device

#endif // DEVICES_GRAMMAR_COMPONENTS_HPP
