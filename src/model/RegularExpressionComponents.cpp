#include "./RegularExpressionComponents.hpp"

namespace formal_device
{
namespace expression
{

RegularPointer::RegularPointer(Regular * reg) :
    std::shared_ptr<Regular>(reg)
{

}

RegularPointer RegularPointer::operator|(const RegularPointer &reg) const
{
    return *get() | reg;
}

RegularPointer RegularPointer::operator+(const RegularPointer &reg) const
{
    return *get() + reg;
}

RegularPointer RegularPointer::operator^(const Operation &op) const
{
    return *get() ^ op;
}

bool RegularPointer::operator==(const RegularPointer &reg) const
{
    return *get() == reg;
}

/* --------------------- Empty --------------------- */

regular_ptr Empty::clone() const
{
    return regular_ptr(new Empty());
}

regular_ptr Empty::operator|(const regular_ptr &reg) const
{
    return reg;
}

regular_ptr Empty::operator+(const regular_ptr &reg) const
{
    return reg;
}

regular_ptr Empty::operator^(const Operation &op) const
{
    return clone();
}

bool Empty::operator==(const regular_ptr &reg) const
{
    return dynamic_cast<const Empty*>(reg.get());
}

/* --------------------- Epsilon --------------------- */

regular_ptr Epsilon::clone() const
{
    return new Epsilon();
}

regular_ptr Epsilon::operator|(const regular_ptr &reg) const
{
    return new Optional(reg);
}

regular_ptr Epsilon::operator+(const regular_ptr &reg) const
{
    return reg;
}

regular_ptr Epsilon::operator^(const Operation &op) const
{
    return clone();
}

bool Epsilon::operator==(const regular_ptr &reg) const
{
    return dynamic_cast<const Epsilon*>(reg.get());
}

/* --------------------- Unit --------------------- */

regular_ptr Unit::clone() const
{
    return new Unit(m_symbol);
}

regular_ptr Unit::operator|(const regular_ptr &reg) const
{
    return new Union(clone(), reg);
}

regular_ptr Unit::operator+(const regular_ptr &reg) const
{
    return new Concatenation(clone(), reg);
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

bool Unit::operator==(const regular_ptr &reg) const
{
    const Unit * check = dynamic_cast<const Unit*>(reg.get());

    if (!check)
        return false;

    return m_symbol == check->m_symbol;
}

/* --------------------- Union --------------------- */

regular_ptr Union::clone() const
{
    return new Union(m_left_expression, m_right_expression);
}

regular_ptr Union::operator|(const regular_ptr &reg) const
{
    return new Union(clone(), reg);
}

regular_ptr Union::operator+(const regular_ptr &reg) const
{
    return new Concatenation(clone(), reg);
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

bool Union::operator==(const regular_ptr &reg) const
{
    const Union * check = dynamic_cast<const Union*>(reg.get());
    
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

regular_ptr Concatenation::operator|(const regular_ptr &reg) const
{
    return new Union(clone(), reg);
}

regular_ptr Concatenation::operator+(const regular_ptr &reg) const
{
    return new Concatenation(clone(), reg);
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

bool Concatenation::operator==(const regular_ptr &reg) const
{
    const Concatenation * check = dynamic_cast<const Concatenation*>(reg.get());
    
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

regular_ptr ReflexiveClosure::operator|(const regular_ptr &reg) const
{
    return new Union(clone(), reg);
}

regular_ptr ReflexiveClosure::operator+(const regular_ptr &reg) const
{
    return new Concatenation(clone(), reg);
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

bool ReflexiveClosure::operator==(const regular_ptr &reg) const
{
    const ReflexiveClosure * check = dynamic_cast<const ReflexiveClosure*>(reg.get());
    
    if (!check)
        return false;

    return m_expression == check->m_expression;
}

/* --------------------- TransitiveClosure --------------------- */

regular_ptr TransitiveClosure::clone() const
{
    return new ReflexiveClosure(m_expression);
}

regular_ptr TransitiveClosure::operator|(const regular_ptr &reg) const
{
    return new Union(clone(), reg);
}

regular_ptr TransitiveClosure::operator+(const regular_ptr &reg) const
{
    return new Concatenation(clone(), reg);
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

bool TransitiveClosure::operator==(const regular_ptr &reg) const
{
    const TransitiveClosure * check = dynamic_cast<const TransitiveClosure*>(reg.get());
    
    if (!check)
        return false;

    return m_expression == check->m_expression;
}

/* --------------------- Optional --------------------- */

regular_ptr Optional::clone() const
{
    return new ReflexiveClosure(m_expression);
}

regular_ptr Optional::operator|(const regular_ptr &reg) const
{
    return new Union(clone(), reg);
}

regular_ptr Optional::operator+(const regular_ptr &reg) const
{
    return new Concatenation(clone(), reg);
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

bool Optional::operator==(const regular_ptr &reg) const
{
    const Optional * check = dynamic_cast<const Optional*>(reg.get());
    
    if (!check)
        return false;

    return m_expression == check->m_expression;
}

} // namespace expression
} // namespace formal_device
