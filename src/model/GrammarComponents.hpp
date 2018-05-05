#ifndef MODEL_GRAMMAR_COMPONENTS_HPP
#define MODEL_GRAMMAR_COMPONENTS_HPP

#include <utility>
#include <string>
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

    Symbol();

    Symbol(const Symbol &) = default;
    Symbol &operator=(const Symbol &) = default;

    Symbol(Symbol &&) = default;
    Symbol &operator=(Symbol &&) = default;

    template <class Arg1>
    Symbol(Arg1 &&symbol) : m_symbol{std::forward<Arg1>(symbol)}
    {
    }

    bool is_terminal() const;
    bool operator==(const Symbol &symbol) const;

  private:
    string_type m_symbol;
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

    symbol_type non_terminal() const;

    SentencialForm operator+(const symbol_type &symbol) const;

  private:
    string_type m_sentence;
    symbol_type m_non_terminal;
};

class Sentence : private SentencialForm
{
  public:
    using string_type = std::string;
    using symbol_type = Symbol;

    Sentence() = delete;

    Sentence(const Sentence &) = default;
    Sentence &operator=(const Sentence &) = default;

    Sentence(Sentence &&) = default;
    Sentence &operator=(Sentence &&) = default;

    template <class Arg1>
    Sentence(Arg1 &&sentence) : SentencialForm("&", std::forward<Arg1>(sentence))
    {
    }

    bool is_sentence() const;

    SentencialForm operator+(const symbol_type &symbol) const;
};

class Production
{
  public:
    friend class Hasher;
    ~Production() = default;

    virtual bool is_terminal() const = 0;
    virtual SentencialForm operator<<(const SentencialForm &form) const = 0;
    virtual bool operator==(const Production &form) const = 0;
};

class ProductionTerminal : public Production
{
  public:
    friend class Hasher;

    using symbol_type = Symbol;

    ProductionTerminal() = delete;

    ProductionTerminal(const ProductionTerminal &) = default;
    ProductionTerminal &operator=(const ProductionTerminal &) = default;

    ProductionTerminal(ProductionTerminal &&) = default;
    ProductionTerminal &operator=(ProductionTerminal &&) = default;

    template <class Arg1>
    ProductionTerminal(Arg1 &&terminal) : m_terminal{std::forward<Arg1>(terminal)}
    {
    }

    bool is_terminal() const;
    SentencialForm operator<<(const SentencialForm &form) const;
    bool operator==(const Production &prod) const;

  private:
    symbol_type m_terminal;
};

class ProductionNonTerminal : public Production
{
  public:
    friend class Hasher;

    using symbol_type = Symbol;

    ProductionNonTerminal() = delete;

    ProductionNonTerminal(const ProductionNonTerminal &) = default;
    ProductionNonTerminal &operator=(const ProductionNonTerminal &) = default;

    ProductionNonTerminal(ProductionNonTerminal &&) = default;
    ProductionNonTerminal &operator=(ProductionNonTerminal &&) = default;

    template <class Arg1, class Arg2>
    ProductionNonTerminal(Arg1 &&terminal, Arg1 &&non_terminal) : m_terminal{std::forward<Arg1>(terminal)},
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
    std::size_t operator()(const Symbol &symbol) const;
    std::size_t operator()(const Production &prod) const;
};

} // namespace grammar
} // namespace formal_device

#endif // MODEL_GRAMMAR_COMPONENTS_HPP
