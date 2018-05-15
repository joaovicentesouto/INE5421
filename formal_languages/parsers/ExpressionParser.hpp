#ifndef PARSER_REGULAREXPRESSION_HPP
#define PARSER_REGULAREXPRESSION_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <algorithm>
#include <regex>

#include <formal_languages/devices/RegularExpressionComponents.hpp>

namespace formal_device
{
namespace parser
{

using string_type          = expression::string_type;
using string_iterator_type = string_type::iterator;
using regular_ptr          = expression::RegularPointer;
using empty_type           = expression::Empty;
using epsilon_type         = expression::Epsilon;
using unit_type            = expression::Unit;
using union_type           = expression::Union;
using concatenation_type   = expression::Concatenation;
using reflexive_type       = expression::ReflexiveClosure;
using transitive_type      = expression::TransitiveClosure;
using optional_type        = expression::Optional;

regular_ptr make_regular_expression(const string_type & file_path);

regular_ptr parse(string_iterator_type &begin, const string_iterator_type &end);

}   // namespace parser
}   // namespace formal_device

#endif
