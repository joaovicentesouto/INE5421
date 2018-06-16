#include "GrammarComponents.hpp"

namespace formal_device
{
namespace grammar
{

SymbolPointer::SymbolPointer(Symbol * symbol) :
    std::shared_ptr<Symbol>(symbol)
{

}

bool SymbolPointer::operator==(const SymbolPointer &another) const
{
    return *get() == *another;
}

bool SymbolPointer::operator<(const SymbolPointer &another) const
{
    return *get() < *another;
}

/* --------------------------------------------------------------- */

bool SymbolSet::contains(const element_type &element)
{
    return find(element) != end();
}

/* --------------------------------------------------------------- */

const TerminalSymbol::string_type& TerminalSymbol::value() const
{
    return m_value;
}

bool TerminalSymbol::is_terminal() const
{
    return true;
}

const TerminalSymbol::terminal_set_type & TerminalSymbol::first() const
{
    return m_first;
}

const TerminalSymbol::terminal_set_type & TerminalSymbol::follow() const
{
    return m_follow;
}

bool TerminalSymbol::operator==(const Symbol &symbol) const
{
    if (!symbol.is_terminal())
        return false;

    return m_value == symbol.value();
}

bool TerminalSymbol::operator==(const TerminalSymbol &symbol) const
{
    return m_value == symbol.m_value;
}

bool TerminalSymbol::operator==(const NonTerminalSymbol &symbol) const
{
    return false;
}

bool TerminalSymbol::operator==(const string_type &value) const
{
    return m_value == value;
}

bool TerminalSymbol::operator<(const Symbol &symbol) const
{
    if (!symbol.is_terminal())
        return true;
        
    return m_value < symbol.value();
}

/* --------------------------------------------------------------- */

const NonTerminalSymbol::string_type& NonTerminalSymbol::value() const
{
    return m_value;
}

bool NonTerminalSymbol::is_terminal() const
{
    return false;
}

const NonTerminalSymbol::terminal_set_type &NonTerminalSymbol::first() const
{
    return m_first;
}

const NonTerminalSymbol::terminal_set_type &NonTerminalSymbol::follow() const
{
    return m_follow;
}

bool NonTerminalSymbol::operator==(const Symbol &symbol) const
{
    if (symbol.is_terminal())
        return false;

    return m_value == symbol.value();
}

bool NonTerminalSymbol::operator==(const TerminalSymbol &symbol) const
{
    return false;
}

bool NonTerminalSymbol::operator==(const NonTerminalSymbol &symbol) const
{
    return m_value == symbol.m_value;
}

bool NonTerminalSymbol::operator==(const string_type &value) const
{
    return m_value == value;
}

bool NonTerminalSymbol::operator<(const Symbol &symbol) const
{
    if (symbol.is_terminal())
        return false;

    return m_value < symbol.value();
}

/* --------------------------------------------------------------- */

Production::string_type Production::to_string() const
{
    string_type string;
    unsigned i = 0;

    for (const auto & symbol : *this)
    {
        string += symbol->value();

        if (++i < size())
            string += " ";
    }

    return string;
}

} // namespace grammar
} // namespace formal_device
