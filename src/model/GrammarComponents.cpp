#include "./GrammarComponents.hpp"

namespace formal_device
{
namespace grammar
{

bool Symbol::is_terminal() const
{
    return false;
}

bool Symbol::operator==(const Symbol& symbol) const
{
    return m_symbol == symbol.m_symbol;
}

bool SentencialForm::is_sentence() const
{
    return m_non_terminal == "&";
}

SentencialForm::symbol_type SentencialForm::non_terminal() const
{
    return symbol_type("&");
}

SentencialForm SentencialForm::operator+(const symbol_type& symbol) const
{
    if (symbol.is_terminal())
        return std::move(SentencialForm{"&", m_sentence + symbol.m_symbol});
    else
        return std::move(SentencialForm{symbol, m_sentence});
}

bool Sentence::is_sentence() const
{
    return SentencialForm::is_sentence();
}

SentencialForm Sentence::operator+(const symbol_type& symbol) const
{
    return std::move(SentencialForm::operator+(symbol));
}

bool ProductionTerminal::is_terminal() const
{
    return true;
}

SentencialForm ProductionTerminal::operator<<(const SentencialForm& form) const
{
    return std::move(form + m_terminal);
}

bool ProductionTerminal::operator==(const Production& prod) const
{
    if (!prod.is_terminal())
        return false;
    else
    {
        const ProductionTerminal* term = dynamic_cast<const ProductionTerminal*>(&prod);
        return m_terminal == term->m_terminal;
    }
}

bool ProductionNonTerminal::is_terminal() const
{
    return false;
}

SentencialForm ProductionNonTerminal::operator<<(const SentencialForm& form) const
{
    return std::move(form + m_terminal + m_non_terminal);
}

bool ProductionNonTerminal::operator==(const Production& prod) const
{
    if (prod.is_terminal())
        return false;
    else
    {
        const ProductionNonTerminal* term = dynamic_cast<const ProductionNonTerminal*>(&prod);
        return m_terminal == term->m_terminal && m_non_terminal == term->m_non_terminal;
    }
}

std::size_t Hasher::operator()(const Symbol &symbol) const
{
    return std::hash<std::string>()(symbol.m_symbol);
}

std::size_t Hasher::operator()(const Production &prod) const
{
    if (prod.is_terminal())
    {
        const ProductionTerminal* term = dynamic_cast<const ProductionTerminal*>(&prod);
        return std::hash<std::string>()(term->m_terminal.m_symbol);
    }
    else
    {
        const ProductionNonTerminal* term = dynamic_cast<const ProductionNonTerminal*>(&prod);
        return ((std::hash<std::string>()(term->m_terminal.m_symbol)
               ^ (std::hash<std::string>()(term->m_non_terminal.m_symbol) << 1)) >> 1);
    }
}

}   // namespace grammar
}   // namespace formal_device
