#ifndef PRINTER_H
#define PRINTER_H

#include <context_free_languages/model/devices/Grammar.hpp>

using grammar_type = formal_device::grammar::ContextFree;

grammar_type::string_type& operator<<(grammar_type::string_type& title, const grammar_type::terminal_set_type& set);
grammar_type::string_type& operator<<(grammar_type::string_type& title, const grammar_type::non_terminal_set_type& set);
grammar_type::string_type& operator<<(grammar_type::string_type& title, const grammar_type::recursion_map_type& map);
grammar_type::string_type& operator<<(grammar_type::string_type& title, const grammar_type::simple_production_map_type& map);
grammar_type::string_type& operator<<(grammar_type::string_type& title, const grammar_type::symbol_ptr_set_type& set);

#endif // PRINTER_H
