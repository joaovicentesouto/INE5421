#ifndef PARSER_REGULAR_GRAMMAR_HPP
#define PARSER_REGULAR_GRAMMAR_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "IteratorWrapper.hpp"
#include <formal_languages/devices/Grammar.hpp>

namespace formal_device
{
namespace parser
{
using string_type = std::string;
using symbol_type                  = grammar::Regular::symbol_type;
using terminal_production_type     = grammar::Regular::terminal_production_type;
using non_terminal_production_type = grammar::Regular::non_terminal_production_type;
using production_type_ptr          = grammar::Regular::production_type_ptr;
using vocabulary_set_type          = grammar::Regular::vocabulary_set_type;
using production_map_type          = grammar::Regular::production_map_type;
using pair_production_type         = grammar::Regular::pair_production_type;

void new_non_terminal(IteratorWrapper &begin, IteratorWrapper &end,
                      vocabulary_set_type &vn, vocabulary_set_type &vt,
                      production_map_type &productions, symbol_type &initial, bool &contains_epsilon);
void new_productions(symbol_type current, IteratorWrapper &begin, IteratorWrapper &end,
                     vocabulary_set_type &vn, vocabulary_set_type &vt,
                     production_map_type &productions, symbol_type &initial, bool &contains_epsilon);

grammar::Regular make_regular_grammar_from_file(const string_type & file_path);
grammar::Regular make_regular_grammar(string_type str_grammar);

}   // namespace parser
}   // namespace formal_devices

#endif
