#ifndef PARSER_REGULAREXPRESSION_H
#define PARSER_REGULAREXPRESSION_H

#include <iostream>
#include <src/formal_devices/Grammar.hpp>

namespace formal_device
{
namespace parser
{

grammar::Regular make_regular_grammar(const std::string &file);

} // namespace parser
} // namespace formal_device

#endif // PARSER_REGULAREXPRESSION_H
