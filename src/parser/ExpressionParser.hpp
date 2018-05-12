#ifndef PARSER_REGULAREXPRESSION_H
#define PARSER_REGULAREXPRESSION_H

#include <iostream>
#include <src/formal_devices/RegularExpression.hpp>

namespace formal_device
{
namespace parser
{

expression::RegularManipulator make_regular_expression(const std::string &file);

} // namespace parser
} // namespace formal_device

#endif // PARSER_REGULAREXPRESSION_H
