#ifndef PARSER_REGULAREXPRESSION_H
#define PARSER_REGULAREXPRESSION_H

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include <string>
#include <vector>
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
