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

bool SymbolPointer::operator!=(const SymbolPointer &another) const
{
    return *get() != *another;
}

bool SymbolPointer::operator==(const Symbol *another) const
{
    return *get() == *another;
}

bool SymbolPointer::operator!=(const Symbol *another) const
{
    return *get() != *another;
}

bool SymbolPointer::operator==(const string_type &another) const
{
    return *get() == another;
}

bool SymbolPointer::operator!=(const string_type &another) const
{
    return *get() != another;
}

bool SymbolPointer::operator<(const SymbolPointer &another) const
{
    return *get() < *another;
}

/* --------------------------------------------------------------- */

TerminalSymbol::TerminalSymbol(const string_type & value) :
    m_value(value)
{
}

TerminalSymbol::TerminalSymbol(string_type &&value) :
    m_value(std::move(value))
{
}

const TerminalSymbol::string_type& TerminalSymbol::value() const
{
    return m_value;
}

bool TerminalSymbol::is_terminal() const
{
    return true;
}

bool TerminalSymbol::operator==(const Symbol &symbol) const
{
    if (!symbol.is_terminal())
        return false;

    return m_value == symbol.value();
}

bool TerminalSymbol::operator!=(const Symbol &symbol) const
{
    return !(*this == symbol);
}

bool TerminalSymbol::operator==(const SymbolPointer &symbol) const
{
    return *this == *symbol;
}

bool TerminalSymbol::operator!=(const SymbolPointer &symbol) const
{
    return *this != *symbol;
}

bool TerminalSymbol::operator==(const TerminalSymbol &symbol) const
{
    return m_value == symbol.m_value;
}

bool TerminalSymbol::operator!=(const TerminalSymbol &symbol) const
{
    return m_value != symbol.m_value;
}

bool TerminalSymbol::operator==(const string_type &value) const
{
    return m_value == value;
}

bool TerminalSymbol::operator!=(const string_type &value) const
{
    return m_value != value;
}

bool TerminalSymbol::operator<(const Symbol &symbol) const
{
    if (!symbol.is_terminal())
        return true;
        
    return m_value < symbol.value();
}

/* --------------------------------------------------------------- */

NonTerminalSymbol::NonTerminalSymbol(const string_type &value) :
    m_value(value)
{
}

NonTerminalSymbol::NonTerminalSymbol(string_type &&value) :
    m_value(std::move(value))
{
}

const NonTerminalSymbol::string_type& NonTerminalSymbol::value() const
{
    return m_value;
}

bool NonTerminalSymbol::is_terminal() const
{
    return false;
}

bool NonTerminalSymbol::operator==(const Symbol &symbol) const
{
    if (symbol.is_terminal())
        return false;

    return m_value == symbol.value();
}

bool NonTerminalSymbol::operator!=(const Symbol &symbol) const
{
    return !(*this == symbol);
}

bool NonTerminalSymbol::operator==(const SymbolPointer &symbol) const
{
    return *this == *symbol;
}

bool NonTerminalSymbol::operator!=(const SymbolPointer &symbol) const
{
    return *this != *symbol;
}

bool NonTerminalSymbol::operator==(const NonTerminalSymbol &symbol) const
{
    return m_value == symbol.m_value;
}

bool NonTerminalSymbol::operator!=(const NonTerminalSymbol &symbol) const
{
    return m_value != symbol.m_value;
}

bool NonTerminalSymbol::operator==(const string_type &value) const
{
    return m_value == value;
}

bool NonTerminalSymbol::operator!=(const string_type &value) const
{
    return m_value != value;
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
