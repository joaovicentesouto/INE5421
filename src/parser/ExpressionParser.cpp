#include "ExpressionParser.hpp"

namespace formal_device
{
namespace parser
{

expression::RegularManipulator make_regular_expression(const std::string &file)
{
    return expression::RegularManipulator(expression::RegularPointer(new expression::Unit("a")));
}

} // namespace parser
} // namespace formal_device
