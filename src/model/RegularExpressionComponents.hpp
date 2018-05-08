#ifndef MODEL_REGULAREXPRESSION_HPP
#define MODEL_REGULAREXPRESSION_HPP

namespace formal_device
{
namespace regular_expression
{
    enum class Operation
    {
        Star, Plus, Optional
    };

    class Regular
    {
        Regular() = default;
        ~Regular() = default;

        virtual Regular operator|(const Regular & reg);  // Union
        virtual Regular operator+(const Regular & reg);  // Concatenate
        virtual Regular operator^(const Operation & op); // Closure
    };

    class Empty : public Regular {};             // Empty
    class Epsilon : public Regular {};           // &
    class Unary : public Regular {}; // or unit? // a
    class Union : public Regular {};             // |
    class Concatenation : public Regular {};     // .
    class ReflexiveClosure : public Regular {};  // *
    class TransitiveClosure : public Regular {}; // +
    class Optional : public Regular {};          // ?
    
}   // namespace regular_expression
}   // namespace formal_device

#endif // MODEL_REGULAREXPRESSION_HPP