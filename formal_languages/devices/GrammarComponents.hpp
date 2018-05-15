#ifndef DEVICES_GRAMMAR_COMPONENTS_HPP
#define DEVICES_GRAMMAR_COMPONENTS_HPP

#include <utility>
#include <string>
#include <regex>
#include <unordered_set>
#include <unordered_map>

namespace formal_device
{
namespace grammar
{

class Symbol
{
  public:
    friend class SentencialForm;
    friend class Hasher;

    using string_type = std::string;

    Symbol() = default;

    Symbol(const Symbol &) = default;
    Symbol &operator=(const Symbol &) = default;
    Symbol(Symbol &&) = default;
    Symbol &operator=(Symbol &&) = default;

    Symbol(const string_type &symbol);
    Symbol(string_type &&symbol);

    bool is_terminal() const;
    bool operator==(const Symbol &symbol) const;
    bool operator==(const string_type &symbol) const;

  private:
    string_type m_symbol{"&"};
};

class SentencialForm
{
  public:
    using string_type = std::string;
    using symbol_type = Symbol;

    SentencialForm() = delete;

    SentencialForm(const SentencialForm &) = default;
    SentencialForm &operator=(const SentencialForm &) = default;
    SentencialForm(SentencialForm &&) = default;
    SentencialForm &operator=(SentencialForm &&) = default;

    template <class Arg1, class Arg2>
    SentencialForm(Arg1 &&non_terminal, Arg2 &&sentence) :
        m_non_terminal{std::forward<Arg1>(non_terminal)},
        m_sentence{std::forward<Arg2>(sentence)}
    {
    }

    bool is_sentence() const;
    symbol_type non_terminal();
    string_type setence();

    SentencialForm operator+(const symbol_type &symbol) const;
    bool operator==(const SentencialForm &from) const;

  private:
    string_type m_sentence;
    symbol_type m_non_terminal;
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
    string_type setence();

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

    bool operator==(const ProductionPointer &prod) const;
};

class Production
{
  public:
    friend class Hasher;

    virtual ~Production() = default;

    virtual bool is_terminal() const = 0;
    virtual SentencialForm operator<<(const SentencialForm &form) const = 0;
    virtual bool operator==(const Production &form) const = 0;
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

    bool is_terminal() const;
    SentencialForm operator<<(const SentencialForm &form) const;
    bool operator==(const Production &prod) const;

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

    bool is_terminal() const;
    SentencialForm operator<<(const SentencialForm &form) const;
    bool operator==(const Production &prod) const;

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
