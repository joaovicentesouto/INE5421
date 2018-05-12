#ifndef MODEL_REGULAREXPRESSION_HPP
#define MODEL_REGULAREXPRESSION_HPP

#include <src/model/RegularExpressionComponents.hpp>

namespace formal_device
{
namespace expression
{

class RegularManipulator
{
public:
    using expression_type_ptr = RegularPointer;

    RegularManipulator() = delete;

    template <class Arg1>
    RegularManipulator(Arg1 &&exp):
        m_expression{std::forward<Arg1>(exp)}
    {
    }

    ~RegularManipulator() = default;

private:
    expression_type_ptr m_expression;
};

}   // namespace expression
}   // namespace formal_device

#endif // MODEL_REGULAREXPRESSION_HPP
