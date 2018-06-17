#ifndef CONTEXTFREEGRAMMARPARSER_HPP
#define CONTEXTFREEGRAMMARPARSER_HPP

#include <context_free_languages/model/devices/Grammar.hpp>

namespace formal_device
{
namespace parser {

template<class T>
using set_type = std::set<T>;

template<class Key, class Value>
using map_type = std::map<Key, Value>;

using string_type                  = std::string;
using string_vector_type           = std::vector<string_type>;
using vector_of_string_vector_type = std::vector<std::vector<string_type>>;
using symbol_ptr_type              = formal_device::grammar::SymbolPointer;
using symbol_type                  = formal_device::grammar::Symbol;
using terminal_symbol_type         = formal_device::grammar::TerminalSymbol;
using non_terminal_symbol_type     = formal_device::grammar::NonTerminalSymbol;
using production_type              = formal_device::grammar::Production;

using terminal_set_type        = set_type<terminal_symbol_type>;
using non_terminal_set_type    = set_type<non_terminal_symbol_type>;
using symbol_ptr_set_type      = set_type<symbol_ptr_type>;
using production_map_type      = map_type<non_terminal_symbol_type, set_type<production_type>>;

using grammar_type = grammar::ContextFree;
using non_terminal_set_type = set_type<non_terminal_symbol_type>;

grammar_type grammar_parser(string_type grammar);

vector_of_string_vector_type split(string_type grammar);

}  // namespace parser
}  // namespace formal_device

#endif // CONTEXTFREEGRAMMARPARSER_H
