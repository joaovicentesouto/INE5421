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

using grammar_type                 = grammar::ContextFree;
using string_type                  = grammar_type::string_type;
using string_vector_type           = std::vector<string_type>;
using vector_of_string_vector_type = std::vector<std::vector<string_type>>;


using symbol_ptr_type              = grammar_type::symbol_ptr_type;
using symbol_type                  = grammar_type::symbol_type;
using terminal_symbol_type         = grammar_type::terminal_symbol_type;
using non_terminal_symbol_type     = grammar_type::non_terminal_symbol_type;
using production_type              = grammar_type::production_type;

using terminal_set_type        = grammar_type::terminal_set_type;
using non_terminal_set_type    = grammar_type::non_terminal_set_type;
using symbol_ptr_set_type      = grammar_type::symbol_ptr_set_type;
using production_map_type      = grammar_type::production_map_type;

using non_terminal_set_type = grammar_type::non_terminal_set_type;

grammar_type grammar_parser(string_type grammar);

vector_of_string_vector_type split(string_type grammar);

}  // namespace parser
}  // namespace formal_device

#endif // CONTEXTFREEGRAMMARPARSER_H
