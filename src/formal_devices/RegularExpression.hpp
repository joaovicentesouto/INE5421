#ifndef DEVICES_REGULAREXPRESSION_HPP
#define DEVICES_REGULAREXPRESSION_HPP

#include <src/formal_devices/RegularExpressionComponents.hpp>

namespace formal_device
{
namespace expression
{

class RegularManipulator
{
public:
    using expression_type_ptr = RegularPointer;

    RegularManipulator() = delete;

    RegularManipulator(const expression_type_ptr &exp);

    ~RegularManipulator() = default;

private:
    expression_type_ptr m_expression;
};

}   // namespace expression
}   // namespace formal_device

#endif // DEVICES_REGULAREXPRESSION_HPP
