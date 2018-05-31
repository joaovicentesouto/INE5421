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

    //! Delete copy constructor
    Symbol(const Symbol &) = default;
    Symbol &operator=(const Symbol &) = default;

    //! Move Constructor
    Symbol(Symbol &&) = default;
    Symbol &operator=(Symbol &&) = default;

    //! Construct Symbol
    /*!
        \brief Constructs an symbol with a string value.
    */
    Symbol(const string_type &value);

    //! Construct Symbol
    /*!
        \param Value name.
        \brief Constructs an symbol with a moved string value.
    */
    Symbol(string_type &&value);

    //! Get value
    /*!
        \param Value name
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
        \return True if contains the same value.
    */
    bool operator==(const Symbol &symbol) const;

    //! Equality operator (from string value)
    /*!
        \brief Verifies that a symbol contains the same value.
        \return True if contains the same value.
    */
    bool operator==(const string_type &symbol) const;

    //! Less than operator
    /*!
        \brief It checks to see if one symbol is smaller than another.
        \return True if is less than.
    */
    bool operator<(const Symbol &symbol) const;

  private:
    string_type m_value{"&"};   //!< Value of the symbol [a-z&]
};

class SentencialForm
{
  public:
    using string_type = std::string;
    using symbol_type = Symbol;

    //! Default Construct SentencialForm
    /*!
        \brief There is no sentence form without symbols.
    */
    SentencialForm() = delete;

    //! Delete copy constructor
    SentencialForm(const SentencialForm &) = default;
    SentencialForm &operator=(const SentencialForm &) = default;

    //! Move constructor
    SentencialForm(SentencialForm &&) = default;
    SentencialForm &operator=(SentencialForm &&) = default;

    //! Polymorphic Construct SentencialForm
    /*!
        \param Non terminal symbol
        \param Terminal symbol
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

    SentencialForm operator+(const symbol_type &symbol) const;

    //! Equality operator
    /*!
        \brief Verifies the sentence and non terminal values are the same.
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
    using string_type = std::string;
    using symbol_type = Symbol;

    Sentence() = delete;

    Sentence(const Sentence &) = default;
    Sentence &operator=(const Sentence &) = default;
    Sentence(Sentence &&) = default;
    Sentence &operator=(Sentence &&) = default;

    Sentence(const string_type &sentence);
    Sentence(string_type &&sentence);

    bool is_sentence() const;
    string_type sentence();

    SentencialForm operator+(const symbol_type &symbol) const;
    bool operator==(const SentencialForm &form) const;
    bool operator==(const Sentence &form) const;
};

class Production;
class ProductionPointer : public std::shared_ptr<Production>
{
public:

    ProductionPointer() = default;
    ProductionPointer(Production * prod);

    ProductionPointer(const ProductionPointer &) = default;
    ProductionPointer &operator=(const ProductionPointer &) = default;
    ProductionPointer(ProductionPointer &&) = default;
    ProductionPointer &operator=(ProductionPointer &&) = default;
    SentencialForm operator<<(const SentencialForm &form) const;

    bool operator==(const ProductionPointer &prod) const;
    bool operator<(const ProductionPointer &prod) const;
};

class Production
{
  public:
    friend class Hasher;
    using string_type = std::string;

    virtual ~Production() = default;

    virtual string_type non_terminal() const = 0;
    virtual string_type terminal() const = 0;
    virtual bool is_terminal() const = 0;
    virtual SentencialForm operator<<(const SentencialForm &form) const = 0;
    virtual bool operator==(const Production &form) const = 0;
    virtual bool operator<(const Production &prod) const = 0;
    virtual string_type to_string() = 0;
};

class TerminalProduction : public Production
{
  public:
    friend class Hasher;

    using symbol_type = Symbol;

    TerminalProduction() = delete;

    TerminalProduction(const TerminalProduction &) = default;
    TerminalProduction &operator=(const TerminalProduction &) = default;
    TerminalProduction(TerminalProduction &&) = default;
    TerminalProduction &operator=(TerminalProduction &&) = default;

    TerminalProduction(const symbol_type &terminal);
    TerminalProduction(symbol_type &&terminal);

    string_type non_terminal() const;
    string_type terminal() const;
    bool is_terminal() const;
    SentencialForm operator<<(const SentencialForm &form) const;
    bool operator==(const Production &prod) const;
    bool operator<(const Production &prod) const;
    string_type to_string();

  private:
    symbol_type m_terminal;
};

class NonTerminalProduction : public Production
{
  public:
    friend class Hasher;

    using symbol_type = Symbol;

    NonTerminalProduction() = delete;

    NonTerminalProduction(const NonTerminalProduction &) = default;
    NonTerminalProduction &operator=(const NonTerminalProduction &) = default;
    NonTerminalProduction(NonTerminalProduction &&) = default;
    NonTerminalProduction &operator=(NonTerminalProduction &&) = default;

    template <class Arg1, class Arg2>
    NonTerminalProduction(Arg1 &&terminal, Arg2 &&non_terminal) :
        m_terminal{std::forward<Arg1>(terminal)},
        m_non_terminal{std::forward<Arg2>(non_terminal)}
    {
    }

    string_type non_terminal() const;
    string_type terminal() const;
    bool is_terminal() const;
    SentencialForm operator<<(const SentencialForm &form) const;
    bool operator==(const Production &prod) const;
    bool operator<(const Production &prod) const;
    string_type to_string();

  private:
    symbol_type m_terminal, m_non_terminal;
};

class Hasher
{   
  public:
    using symbol_type         = Symbol;
    using production_type_ptr = ProductionPointer;

    std::size_t operator()(const symbol_type &symbol) const;
    std::size_t operator()(const production_type_ptr &prod) const;
};

} // namespace grammar
} // namespace formal_device

#endif // DEVICES_GRAMMAR_COMPONENTS_HPP
