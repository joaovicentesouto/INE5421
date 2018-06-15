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

class TerminalSymbol;
class NonTerminalSymbol;
class Symbol
{
  public:
    template <class T> using set_type    = std::set<T>;
    template <class T> using vector_type = std::vector<T>;
    using string_type                    = std::string;
    using terminal_set_type              = set_type<TerminalSymbol>;

    //! Destructor
    ~Symbol() = default;

    //! Get value
    /*!
        \brief Simple get.
        \return The name of the symbol.
    */
    virtual const string_type &value() const = 0;

    //! Terminal check
    /*!
        \brief Verifies whether a symbol is terminal or not (belongs to A-Z or &).
        \return True if is a terminal symbol.
    */
    virtual bool is_terminal() const = 0;

    virtual const terminal_set_type &first() const = 0;

    virtual const terminal_set_type &follow() const = 0;

    //! Equality operator (from another symbol)
    /*!
        \brief Verifies that symbols are the same.
        \param symbol Another symbol.
        \return True if contains the same value.
    */
    virtual bool operator==(const Symbol &symbol) const = 0;
    virtual bool operator==(const TerminalSymbol &symbol) const = 0;
    virtual bool operator==(const NonTerminalSymbol &symbol) const = 0;

    //! Equality operator (from string value)
    /*!
        \brief Verifies that a symbol contains the same value.
        \param symbol Another symbol.
        \return True if contains the same value.
    */
    virtual bool operator==(const string_type &value) const = 0;

    //! Less than operator
    /*!
        \brief It checks to see if one symbol is smaller than another.
        \param symbol Another symbol.
        \return True if is less than.
    */
    virtual bool operator<(const Symbol &symbol) const = 0;
};

class SymbolPointer : public std::shared_ptr<Symbol>
{
  public:
    using symbol_type = Symbol;

    bool operator==(const SymbolPointer &another) const;
    bool operator<(const SymbolPointer &another) const;
};

class SymbolSet : public Symbol::set_type<SymbolPointer>
{
  public:
    using element_type = SymbolPointer;

    SymbolSet() = default;
    SymbolSet(const SymbolSet &) = default;
    SymbolSet &operator=(const SymbolSet &) = default;
    SymbolSet(SymbolSet &&) = default;
    SymbolSet &operator=(SymbolSet &&) = default;

    ~SymbolSet() = default;

    bool contains(const element_type &element);
};

class TerminalSymbol : public Symbol
{
  public:
    friend class Production;

    using string_type       = Symbol::string_type;
    using terminal_set_type = Symbol::terminal_set_type;

    TerminalSymbol() = default;
    TerminalSymbol(const TerminalSymbol &) = default;
    TerminalSymbol &operator=(const TerminalSymbol &) = default;
    TerminalSymbol(TerminalSymbol &&) = default;
    TerminalSymbol &operator=(TerminalSymbol &&) = default;

    template <class Arg>
    TerminalSymbol(Arg &&value) : m_value(std::forward<Arg>(value))
    {
    }

    //! Destructor
    ~TerminalSymbol() = default;

    //! Get value
    /*!
        \brief Simple get.
        \return The name of the symbol.
    */
    const string_type &value() const;

    //! Terminal check
    /*!
        \brief Verifies whether a symbol is terminal or not (belongs to A-Z or &).
        \return True if is a terminal symbol.
    */
    bool is_terminal() const;

    const terminal_set_type &first() const;

    const terminal_set_type &follow() const;

    //! Equality operator (from another symbol)
    /*!
        \brief Verifies that symbols are the same.
        \param symbol Another symbol.
        \return True if contains the same value.
    */
    bool operator==(const Symbol &symbol) const;
    bool operator==(const TerminalSymbol &symbol) const;
    bool operator==(const NonTerminalSymbol &symbol) const;

    //! Equality operator (from string value)
    /*!
        \brief Verifies that a symbol contains the same value.
        \param symbol Another symbol.
        \return True if contains the same value.
    */
    bool operator==(const string_type &value) const;

    //! Less than operator
    /*!
        \brief It checks to see if one symbol is smaller than another.
        \param symbol Another symbol.
        \return True if is less than.
    */
    bool operator<(const Symbol &symbol) const;

  private:
    string_type m_value{"&"};
    terminal_set_type m_first;
    terminal_set_type m_follow;
};

class NonTerminalSymbol : public Symbol
{
  public:
    friend class Production;

    using string_type       = Symbol::string_type;
    using terminal_set_type = Symbol::terminal_set_type;

    NonTerminalSymbol() = default;
    NonTerminalSymbol(const NonTerminalSymbol &) = default;
    NonTerminalSymbol &operator=(const NonTerminalSymbol &) = default;
    NonTerminalSymbol(NonTerminalSymbol &&) = default;
    NonTerminalSymbol &operator=(NonTerminalSymbol &&) = default;

    template <class Arg>
    NonTerminalSymbol(Arg &&value) :
        m_value(std::forward<Arg>(value))
    {
    }

    //! Destructor
    ~NonTerminalSymbol() = default;

    //! Get value
    /*!
        \brief Simple get.
        \return The name of the symbol.
    */
    const string_type &value() const;

    //! Terminal check
    /*!
        \brief Verifies whether a symbol is terminal or not (belongs to A-Z or &).
        \return True if is a terminal symbol.
    */
    bool is_terminal() const;

    const terminal_set_type &first() const;

    const terminal_set_type &follow() const;

    //! Equality operator (from another symbol)
    /*!
        \brief Verifies that symbols are the same.
        \param symbol Another symbol.
        \return True if contains the same value.
    */
    bool operator==(const Symbol &symbol) const;
    bool operator==(const TerminalSymbol &symbol) const;
    bool operator==(const NonTerminalSymbol &symbol) const;

    //! Equality operator (from string value)
    /*!
        \brief Verifies that a symbol contains the same value.
        \param symbol Another symbol.
        \return True if contains the same value.
    */
    bool operator==(const string_type &value) const;

    //! Less than operator
    /*!
        \brief It checks to see if one symbol is smaller than another.
        \param symbol Another symbol.
        \return True if is less than.
    */
    bool operator<(const Symbol &symbol) const;

  private:
    string_type m_value{"Error"};
    terminal_set_type m_first;
    terminal_set_type m_follow;
};

class Production : public Symbol::vector_type<SymbolPointer>
{
  public:
    using symbol_ptr_type           = SymbolPointer;
    using symbol_type               = symbol_ptr_type::symbol_type;
    using string_type               = symbol_type::string_type;
    using symbol_ptr_container_type = symbol_type::vector_type<symbol_ptr_type>;

    Production() = default;
    Production(const Production &) = default;
    Production &operator=(const Production &) = default;
    Production(Production &&) = default;
    Production &operator=(Production &&) = default;

    //! Default Destructor
    /*!
        \brief To implement a pure interface.
    */
    ~Production() = default;

    // //! Equality operator.
    // /*!
    //     \brief Check to see if they make the same changes.
    //     \param prod Another Production.
    //     \return True if are make the same changes.
    // */
    // bool operator==(const Production &prod) const;

    // //! Less than operator
    // /*!
    //     \brief It checks to see if producitons is smaller than another.
    //     \param prod Another Production.
    //     \return True if is less than.
    // */
    // bool operator<(const Production &prod) const;

    //! Transform Production to string
    /*!
        \brief Representation of the production in the form of a string.
        \return The string representation.
    */
    string_type to_string() const;

    // symbol_ptr_type operator[](size_t pos); // ?
    // size_t size() const;
    // iterator begin() const;
    // iterator end() const;
};

} // namespace grammar
} // namespace formal_device

#endif // DEVICES_GRAMMAR_COMPONENTS_HPP
