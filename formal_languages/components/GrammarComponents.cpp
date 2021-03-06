#include "GrammarComponents.hpp"

namespace formal_device
{
namespace grammar
{

Symbol::Symbol(const string_type &value) :
    m_value{value}
{
}

Symbol::Symbol(string_type &&value) :
    m_value{std::move(value)}
{
}

bool Symbol::is_terminal() const
{
    return std::regex_match(m_value, std::regex("[a-z]")) || m_value == "&";
}

bool Symbol::operator==(const Symbol& symbol) const
{
    return m_value == symbol.m_value;
}

bool Symbol::operator==(const string_type &value) const
{
    return m_value == value;
}

bool Symbol::operator<(const Symbol &symbol) const
{
    return m_value < symbol.m_value;
}

Symbol::string_type Symbol::value() const
{
    return m_value;
}

/* ----------------------------------------------------------------------- */

bool SentencialForm::is_sentence() const
{
    return m_non_terminal == "&";
}

SentencialForm::symbol_type SentencialForm::non_terminal()
{
    return m_non_terminal;
}

SentencialForm::string_type SentencialForm::sentence()
{
    return m_sentence;
}

SentencialForm SentencialForm::operator+(const symbol_type& symbol) const
{
    auto sent = m_sentence == "&" ? "" : m_sentence;

    if (symbol.is_terminal())
        return SentencialForm{"&", sent + symbol.m_value};
    else
        return SentencialForm{symbol, sent};
}

bool SentencialForm::operator==(const SentencialForm &form) const
{
    return m_sentence == form.m_sentence && m_non_terminal == form.m_non_terminal;
}

/* ----------------------------------------------------------------------- */

Sentence::Sentence(const string_type &sentence) :
    SentencialForm("&", sentence)
{
}

Sentence::Sentence(string_type &&sentence) :
    SentencialForm("&", std::move(sentence))
{
}

bool Sentence::is_sentence() const
{
    return SentencialForm::is_sentence();
}

Sentence::string_type Sentence::sentence()
{
    return SentencialForm::sentence();
}

SentencialForm Sentence::operator+(const symbol_type& symbol) const
{
    return SentencialForm::operator+(symbol);
}

bool Sentence::operator==(const SentencialForm &form) const
{
    return SentencialForm::operator==(form);
}

bool Sentence::operator==(const Sentence &form) const
{
    return SentencialForm::operator==(form);
}

/* ----------------------------------------------------------------------- */

ProductionPointer::ProductionPointer(Production * prod) :
    std::shared_ptr<Production>(prod)
{
}

bool ProductionPointer::operator==(const ProductionPointer &prod) const
{
    return (*get()) == *prod;
}

bool ProductionPointer::operator<(const ProductionPointer &prod) const
{
    return (*get()) < *prod;
}

SentencialForm ProductionPointer::operator<<(const SentencialForm &form) const
{
    return (*get()) << form;
}

/* ----------------------------------------------------------------------- */

TerminalProduction::TerminalProduction(const symbol_type &terminal) :
    m_terminal{terminal}
{
}

TerminalProduction::TerminalProduction(symbol_type &&terminal) :
    m_terminal{std::move(terminal)}
{
}

bool TerminalProduction::is_terminal() const
{
    return true;
}

SentencialForm TerminalProduction::operator<<(const SentencialForm& form) const
{
    return form + m_terminal;
}

bool TerminalProduction::operator==(const Production& prod) const
{
    if (!prod.is_terminal())
        return false;

    const TerminalProduction* term = dynamic_cast<const TerminalProduction*>(&prod);
    return m_terminal == term->m_terminal;
}

bool TerminalProduction::operator<(const Production &prod) const
{
    if (!prod.is_terminal())
        return true;

    const TerminalProduction* term = dynamic_cast<const TerminalProduction*>(&prod);

    return m_terminal.m_value < term->m_terminal.m_value;
}

Production::string_type TerminalProduction::non_terminal() const
{
    return "";
}

Production::string_type TerminalProduction::terminal() const
{
    return m_terminal.value();
}

Production::string_type TerminalProduction::to_string() const
{
    return m_terminal.value();
}

/* ----------------------------------------------------------------------- */

bool NonTerminalProduction::is_terminal() const
{
    return false;
}

SentencialForm NonTerminalProduction::operator<<(const SentencialForm& form) const
{
    return form + m_terminal + m_non_terminal;
}

bool NonTerminalProduction::operator==(const Production& prod) const
{
    if (prod.is_terminal())
        return false;

    const NonTerminalProduction* term = dynamic_cast<const NonTerminalProduction*>(&prod);
    return m_terminal == term->m_terminal && m_non_terminal == term->m_non_terminal;
}

bool NonTerminalProduction::operator<(const Production &prod) const
{
    if (prod.is_terminal())
        return false;

    const NonTerminalProduction* term = dynamic_cast<const NonTerminalProduction*>(&prod);

    symbol_type::string_type value = m_terminal.m_value + m_non_terminal.m_value;
    symbol_type::string_type other_value = term->m_terminal.m_value + term->m_non_terminal.m_value;

    return value < other_value;
}

NonTerminalProduction::string_type NonTerminalProduction::non_terminal() const
{
    return m_non_terminal.value();
}

NonTerminalProduction::string_type NonTerminalProduction::terminal() const
{
    return m_terminal.value();
}

Production::string_type NonTerminalProduction::to_string() const
{
    return m_terminal.value() + m_non_terminal.value();
}

}   // namespace grammar
}   // namespace formal_device
