//! João Vicente Souto e Bruno Izaias Bonotto

#ifndef DEVICES_GRAMMAR_COMPONENTS_HPP
#define DEVICES_GRAMMAR_COMPONENTS_HPP

#include <utility>
#include <string>
#include <regex>
#include <set>
#include <unordered_map>

namespace formal_device
{
namespace grammar
{

class Symbol
{
  public:
    friend class SentencialForm;
    friend class TerminalProduction;
    friend class NonTerminalProduction;
    friend class Hasher;

    using string_type = std::string;

    //! Default Construct Symbol
    /*!
        \brief Constructs an epsilon symbol.
    */
    Symbol() = default;

    //! Copy constructor
    Symbol(const Symbol &) = default;
    Symbol &operator=(const Symbol &) = default;

    //! Move Constructor
    Symbol(Symbol &&) = default;
    Symbol &operator=(Symbol &&) = default;

    //! Construct Symbol
    /*!
        \brief Constructs an symbol with a copy string value.
        \param value Value name.
    */
    Symbol(const string_type &value);

    //! Construct Symbol
    /*!
        \brief Constructs an symbol with a moved string value.
        \param value Value name.
    */
    Symbol(string_type &&value);

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
    string_type m_value{"&"};   //!< Value of the symbol [a-z&]
};

class SentencialForm
{
  public:
    using symbol_type = Symbol;
    using string_type = symbol_type::string_type;

    //! Default Construct SentencialForm
    /*!
        \brief There is no sentence form without symbols.
    */
    SentencialForm() = delete;

    //! Copy constructor
    SentencialForm(const SentencialForm &) = default;
    SentencialForm &operator=(const SentencialForm &) = default;

    //! Move constructor
    SentencialForm(SentencialForm &&) = default;
    SentencialForm &operator=(SentencialForm &&) = default;

    //! Polymorphic Construct SentencialForm
    /*!
        \param non_terminal Non terminal symbol
        \param terminal Terminal symbol
        \brief Constructs a sentenced form with a sentence and a non-terminal symbol
    */
    template <class Arg1, class Arg2>
    SentencialForm(Arg1 &&non_terminal, Arg2 &&sentence) :
        m_sentence{std::forward<Arg2>(sentence)},
        m_non_terminal{std::forward<Arg1>(non_terminal)}
    {
    }

    //! Sentence check
    /*!
        \brief Verifies that a sentence has ' & ' as a non-terminal symbol.
        \return True if is a sentence.
    */
    bool is_sentence() const;

    //! Get non terminal symbol
    /*!
        \brief Simple get.
        \return The non terminal symbol
    */
    symbol_type non_terminal();

    //! Get sentence
    /*!
        \brief Simple get.
        \return The sentence on a string value
    */
    string_type sentence();

    //! Concatenation operator
    /*!
        \brief Receives a symbol and generates a new sentence form.
        \param symbol Symbol to concat.
        \return The new sentencial form.
    */
    SentencialForm operator+(const symbol_type &symbol) const;

    //! Equality operator
    /*!
        \brief Verifies the sentence and non terminal values are the same.
        \param form Another sentencial form.
        \return True if are the same.
    */
    bool operator==(const SentencialForm &from) const;

  private:
    string_type m_sentence;     //!< Sentence value
    symbol_type m_non_terminal; //!< Non terminal symbol
};

class Sentence : public SentencialForm
{
  public:
    using string_type = SentencialForm::string_type;
    using symbol_type = SentencialForm::symbol_type;

    //! Default Construct Symbol
    /*!
        \brief There is no empty sentence.
    */
    Sentence() = delete;

    //! Copy constructor
    Sentence(const Sentence &) = default;
    Sentence &operator=(const Sentence &) = default;

    //! Move constructor
    Sentence(Sentence &&) = default;
    Sentence &operator=(Sentence &&) = default;

    //! Construct Sentence from copy string
    /*!
        \brief A sentence is a sentenced form with the non-terminal symbol equal to &.
        \param sentence String copy value.
    */
    Sentence(const string_type &sentence);

    //! Construct Sentence from move string
    /*!
        \brief A sentence is a sentenced form with the non-terminal symbol equal to &.
        \param sentence String move value.
    */
    Sentence(string_type &&sentence);

    //! Sentence check
    /*!
        \brief Verifies that a sentence has ' & ' as a non-terminal symbol.
        \return True.
    */
    bool is_sentence() const;

    //! Get sentence
    /*!
        \brief Simple get.
        \return The sentence on a string value.
    */
    string_type sentence();

    //! Concatenation operator
    /*!
        \brief Receives a symbol and generates a new sentence form.
        \param symbol Symbol to concat.
        \return The new sentencial form.
    */
    SentencialForm operator+(const symbol_type &symbol) const;

    //! Equality operator with a sentencial form.
    /*!
        \brief Verifies if the form is a sentence and the values are the same
        \param form Another sentencial form.
        \return True if are the same.
    */
    bool operator==(const SentencialForm &form) const;

    //! Equality operator with a sentence.
    /*!
        \brief Verifies if the values are the same
        \param form Another sentencial form.
        \return True if are the same.
    */
    bool operator==(const Sentence &form) const;
};

class Production;
class ProductionPointer : public std::shared_ptr<Production>
{
public:

    //! Default Construct
    /*!
        \brief Save a nullptr.
    */
    ProductionPointer() = default;

    //! Construct
    /*!
        \brief Save a Production pointer.
        \param prod a Production pointer
    */
    ProductionPointer(Production * prod);

    //! Copy constructor
    ProductionPointer(const ProductionPointer &) = default;
    ProductionPointer &operator=(const ProductionPointer &) = default;

    //! Move constructor
    ProductionPointer(ProductionPointer &&) = default;
    ProductionPointer &operator=(ProductionPointer &&) = default;

    //! << operator.
    /*!
        \brief Generates changes in a sentencing form.
        \param form A sentencial form
        \return The new changed sentencial form.
    */
    SentencialForm operator<<(const SentencialForm &form) const;

    //! Equality operator.
    /*!
        \brief Verifies that they point to the same objects{values}.
        \param prod Another ProductionPointer
        \return True if are the same.
    */
    bool operator==(const ProductionPointer &prod) const;

    //! Less than operator
    /*!
        \brief It checks to see if producitons is smaller than another.
        \param prod Another ProductionPointer.
        \return True if is less than.
    */
    bool operator<(const ProductionPointer &prod) const;
};

class Production
{
  public:
    using string_type = SentencialForm::string_type;
    using symbol_type = SentencialForm::symbol_type;

    //! Default Destructor
    /*!
        \brief To implement a pure interface.
    */
    virtual ~Production() = default;

    //! Get nonterminal symbol
    /*!
        \brief Simple get.
        \return The non terminal symbol on a string value.
    */
    virtual string_type non_terminal() const = 0;

    //! Get terminal symbol
    /*!
        \brief Simple get.
        \return The terminal symbol on a string value.
    */
    virtual string_type terminal() const = 0;

    //! Terminal production check
    /*!
        \brief Verifies if is a terminal production.
        \return True.
    */
    virtual bool is_terminal() const = 0;

    //! << operator.
    /*!
        \brief Generates changes in a sentencing form.
        \param form A sentencial form
        \return The new changed sentencial form.
    */
    virtual SentencialForm operator<<(const SentencialForm &form) const = 0;

    //! Equality operator.
    /*!
        \brief Check to see if they make the same changes.
        \param prod Another Production.
        \return True if are make the same changes.
    */
    virtual bool operator==(const Production &prod) const = 0;

    //! Less than operator
    /*!
        \brief It checks to see if producitons is smaller than another.
        \param prod Another Production.
        \return True if is less than.
    */
    virtual bool operator<(const Production &prod) const = 0;

    //! Transform Production to string
    /*!
        \brief Representation of the production in the form of a string.
        \return The string representation.
    */
    virtual string_type to_string() const = 0;
};

class TerminalProduction : public Production
{
  public:
    TerminalProduction() = delete;

    //! Copy constructor
    TerminalProduction(const TerminalProduction &) = default;
    TerminalProduction &operator=(const TerminalProduction &) = default;

    //! Move constructor
    TerminalProduction(TerminalProduction &&) = default;
    TerminalProduction &operator=(TerminalProduction &&) = default;

    TerminalProduction(const symbol_type &terminal);
    TerminalProduction(symbol_type &&terminal);

    //! Get nonterminal symbol
    /*!
        \brief Simple get.
        \return The non terminal symbol on a string value.
    */
    string_type non_terminal() const;

    //! Get terminal symbol
    /*!
        \brief Simple get.
        \return The terminal symbol on a string value.
    */
    string_type terminal() const;

    //! Terminal production check
    /*!
        \brief Verifies if is a terminal production.
        \return True.
    */
    bool is_terminal() const;

    //! << operator.
    /*!
        \brief Generates changes in a sentencing form.
        \param form A sentencial form
        \return The new changed sentencial form.
    */
    SentencialForm operator<<(const SentencialForm &form) const;

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
    symbol_type m_terminal; //!< Terminal symbol
};

class NonTerminalProduction : public Production
{
  public:
    // using symbol_type = Production::symbol_type;

    NonTerminalProduction() = delete;

    //! Copy constructor
    NonTerminalProduction(const NonTerminalProduction &) = default;
    NonTerminalProduction &operator=(const NonTerminalProduction &) = default;

    //! Move constructor
    NonTerminalProduction(NonTerminalProduction &&) = default;
    NonTerminalProduction &operator=(NonTerminalProduction &&) = default;

    template <class Arg1, class Arg2>
    NonTerminalProduction(Arg1 &&terminal, Arg2 &&non_terminal) :
        m_terminal{std::forward<Arg1>(terminal)},
        m_non_terminal{std::forward<Arg2>(non_terminal)}
    {
    }

    //! Get nonterminal symbol
    /*!
        \brief Simple get.
        \return The non terminal symbol on a string value.
    */
    string_type non_terminal() const;

    //! Get terminal symbol
    /*!
        \brief Simple get.
        \return The terminal symbol on a string value.
    */
    string_type terminal() const;

    //! Terminal production check
    /*!
        \brief Verifies if is a terminal production.
        \return True.
    */
    bool is_terminal() const;

    //! << operator.
    /*!
        \brief Generates changes in a sentencing form.
        \param form A sentencial form
        \return The new changed sentencial form.
    */
    SentencialForm operator<<(const SentencialForm &form) const;

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
    symbol_type m_terminal, m_non_terminal; //!< Non terminal and terminal symbols
};

} // namespace grammar
} // namespace formal_device

#endif // DEVICES_GRAMMAR_COMPONENTS_HPP
