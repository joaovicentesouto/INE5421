#include "./GrammarComponents.hpp"

namespace formal_device
{
namespace grammar
{

//Symbol::Symbol() :
//    m_symbol("&")
//{

//}

Symbol::Symbol(const string_type &symbol) :
    m_symbol{symbol}
{
}

Symbol::Symbol(string_type &&symbol) :
    m_symbol{std::move(symbol)}
{
}

bool Symbol::is_terminal() const
{
    return std::regex_match(m_symbol, std::regex("[a-z]")) || m_symbol == "&";
}

bool Symbol::operator==(const Symbol& symbol) const
{
    return m_symbol == symbol.m_symbol;
}

bool Symbol::operator==(const string_type &symbol) const
{
    return m_symbol == symbol;
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

SentencialForm::string_type SentencialForm::setence()
{
    return m_sentence;
}

SentencialForm SentencialForm::operator+(const symbol_type& symbol) const
{
    if (symbol.is_terminal())
        return std::move(SentencialForm{"&", m_sentence + symbol.m_symbol});
    else
        return std::move(SentencialForm{symbol, m_sentence});
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

Sentence::string_type Sentence::setence()
{
    return SentencialForm::setence();
}

SentencialForm Sentence::operator+(const symbol_type& symbol) const
{
    return std::move(SentencialForm::operator+(symbol));
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
    return std::move(form + m_terminal);
}

bool TerminalProduction::operator==(const Production& prod) const
{
    if (!prod.is_terminal())
        return false;
    else
    {
        const TerminalProduction* term = dynamic_cast<const TerminalProduction*>(&prod);
        return m_terminal == term->m_terminal;
    }
}

/* ----------------------------------------------------------------------- */

bool NonTerminalProduction::is_terminal() const
{
    return false;
}

SentencialForm NonTerminalProduction::operator<<(const SentencialForm& form) const
{
    return std::move(form + m_terminal + m_non_terminal);
}

bool NonTerminalProduction::operator==(const Production& prod) const
{
    if (prod.is_terminal())
        return false;
    else
    {
        const NonTerminalProduction* term = dynamic_cast<const NonTerminalProduction*>(&prod);
        return m_terminal == term->m_terminal && m_non_terminal == term->m_non_terminal;
    }
}

/* ----------------------------------------------------------------------- */

std::size_t Hasher::operator()(const symbol_type &symbol) const
{
    return std::hash<std::string>()(symbol.m_symbol);
}

std::size_t Hasher::operator()(const production_type_ptr &prod) const
{
    if (prod->is_terminal())
    {
        const TerminalProduction* term = dynamic_cast<const TerminalProduction*>(prod.get());
        return std::hash<std::string>()(term->m_terminal.m_symbol);
    }
    else
    {
        const NonTerminalProduction* term = dynamic_cast<const NonTerminalProduction*>(prod.get());
        return std::hash<std::string>()(term->m_terminal.m_symbol + term->m_non_terminal.m_symbol);
    }
}

}   // namespace grammar
}   // namespace formal_device
