#include "./RegularExpressionComponents.hpp"

namespace formal_device
{
namespace expression
{

/* --------------------- Empty --------------------- */

regular_ptr Empty::clone() const
{
    return regular_ptr(new Empty());
}

regular_ptr Empty::operator|(const Regular &reg) const
{
    return reg.clone();
}

regular_ptr Empty::operator+(const Regular &reg) const
{
    return reg.clone();
}

regular_ptr Empty::operator^(const Operation &op) const
{
    return clone();
}

bool Empty::operator==(const Regular &reg) const
{
    return dynamic_cast<const Empty*>(&reg);
}

/* --------------------- Epsilon --------------------- */

regular_ptr Epsilon::clone() const
{
    return regular_ptr(new Epsilon());
}

regular_ptr Epsilon::operator|(const Regular &reg) const
{
    return regular_ptr(new Optional(reg.clone()));
}

regular_ptr Epsilon::operator+(const Regular &reg) const
{
    return regular_ptr(reg.clone());
}

regular_ptr Epsilon::operator^(const Operation &op) const
{
    return clone();
}

bool Epsilon::operator==(const Regular &reg) const
{
    return dynamic_cast<const Epsilon*>(&reg);
}

/* --------------------- Unit --------------------- */

Unit::Unit(const string_type &symbol) :
    m_symbol{symbol}
{
}

Unit::Unit(string_type &&symbol) :
    m_symbol{std::move(symbol)}
{
}

regular_ptr Unit::operator|(const Regular &reg) const
{
    return new Union(clone(), reg.clone());
}

regular_ptr Unit::operator+(const Regular &reg) const
{
    return new Concatenation(clone(), reg.clone());
}

regular_ptr Unit::operator^(const Operation &op) const
{
    switch (op)
    {
    case Operation::Star :
        return new ReflexiveClosure(clone());

    case Operation::Plus :
        return new TransitiveClosure(clone());

    case Operation::Optional :
        return new Optional(clone());
    }
}

bool Unit::operator==(const Regular &reg) const
{
    const Unit * check = dynamic_cast<const Unit*>(&reg);
    
    if (!check)
        return false;

    return m_symbol == check->m_symbol;
}

/* --------------------- Union --------------------- */

regular_ptr Union::clone() const
{
    return new Union(m_left_expression, m_right_expression);
}

regular_ptr Union::operator|(const Regular &reg) const
{
    return new Union(clone(), reg.clone());
}

regular_ptr Union::operator+(const Regular &reg) const
{
    return new Concatenation(clone(), reg.clone());
}

regular_ptr Union::operator^(const Operation &op) const
{
    switch (op)
    {
    case Operation::Star :
        return new ReflexiveClosure(clone());

    case Operation::Plus :
        return new TransitiveClosure(clone());

    case Operation::Optional :
        return new Optional(clone());
    }
}

bool Union::operator==(const Regular &reg) const
{
    const Union * check = dynamic_cast<const Union*>(&reg);
    
    if (!check)
        return false;

    return m_left_expression == check->m_left_expression &&
           m_right_expression == check->m_right_expression;
}

/* --------------------- Concatenation --------------------- */

regular_ptr Concatenation::clone() const
{
    return new Concatenation(m_left_expression, m_right_expression);
}

regular_ptr Concatenation::operator|(const Regular &reg) const
{
    return new Union(clone(), reg.clone());
}

regular_ptr Concatenation::operator+(const Regular &reg) const
{
    return new Concatenation(clone(), reg.clone());
}

regular_ptr Concatenation::operator^(const Operation &op) const
{
    switch (op)
    {
    case Operation::Star :
        return new ReflexiveClosure(clone());

    case Operation::Plus :
        return new TransitiveClosure(clone());

    case Operation::Optional :
        return new Optional(clone());
    }
}

bool Concatenation::operator==(const Regular &reg) const
{
    const Concatenation * check = dynamic_cast<const Concatenation*>(&reg);
    
    if (!check)
        return false;

    return m_left_expression == check->m_left_expression &&
           m_right_expression == check->m_right_expression;
}

/* --------------------- ReflexiveClosure --------------------- */

regular_ptr ReflexiveClosure::clone() const
{
    return new ReflexiveClosure(m_expression);
}

regular_ptr ReflexiveClosure::operator|(const Regular &reg) const
{
    return new Union(clone(), reg.clone());
}

regular_ptr ReflexiveClosure::operator+(const Regular &reg) const
{
    return new Concatenation(clone(), reg.clone());
}

regular_ptr ReflexiveClosure::operator^(const Operation &op) const
{
    switch (op)
    {
    case Operation::Star :
        return new ReflexiveClosure(clone());

    case Operation::Plus :
        return new TransitiveClosure(clone());

    case Operation::Optional :
        return new Optional(clone());
    }
}

bool ReflexiveClosure::operator==(const Regular &reg) const
{
    const ReflexiveClosure * check = dynamic_cast<const ReflexiveClosure*>(&reg);
    
    if (!check)
        return false;

    return m_expression == check->m_expression;
}

/* --------------------- TransitiveClosure --------------------- */

regular_ptr TransitiveClosure::clone() const
{
    return new ReflexiveClosure(m_expression);
}

regular_ptr TransitiveClosure::operator|(const Regular &reg) const
{
    return new Union(clone(), reg.clone());
}

regular_ptr TransitiveClosure::operator+(const Regular &reg) const
{
    return new Concatenation(clone(), reg.clone());
}

regular_ptr TransitiveClosure::operator^(const Operation &op) const
{
    switch (op)
    {
    case Operation::Star :
        return new ReflexiveClosure(clone());

    case Operation::Plus :
        return new TransitiveClosure(clone());

    case Operation::Optional :
        return new Optional(clone());
    }
}

bool TransitiveClosure::operator==(const Regular &reg) const
{
    const TransitiveClosure * check = dynamic_cast<const TransitiveClosure*>(&reg);
    
    if (!check)
        return false;

    return m_expression == check->m_expression;
}

/* --------------------- Optional --------------------- */

regular_ptr Optional::clone() const
{
    return new ReflexiveClosure(m_expression);
}

regular_ptr Optional::operator|(const Regular &reg) const
{
    return new Union(clone(), reg.clone());
}

regular_ptr Optional::operator+(const Regular &reg) const
{
    return new Concatenation(clone(), reg.clone());
}

regular_ptr Optional::operator^(const Operation &op) const
{
    switch (op)
    {
    case Operation::Star :
        return new ReflexiveClosure(clone());

    case Operation::Plus :
        return new TransitiveClosure(clone());

    case Operation::Optional :
        return new Optional(clone());
    }
}

bool Optional::operator==(const Regular &reg) const
{
    const Optional * check = dynamic_cast<const Optional*>(&reg);
    
    if (!check)
        return false;

    return m_expression == check->m_expression;
}

} // namespace expression
} // namespace formal_device
