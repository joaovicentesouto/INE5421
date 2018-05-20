#include "RegularExpression.hpp"

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

simone_node_ptr Empty::node_myself()
{
    auto unit = new UnitNode();
    unit->m_symbol = "Empty";
    return unit;
}

/* --------------------- Epsilon --------------------- */

regular_ptr Epsilon::clone() const
{
    return new Epsilon();
}

regular_ptr Epsilon::operator|(const regular_ptr &reg) const
{
    return reg ^ Operation::Optional;
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

simone_node_ptr Epsilon::node_myself()
{
    auto unit = new UnitNode();
    unit->m_symbol = "&";
    return unit;
}

/* --------------------- Unit --------------------- */

regular_ptr Unit::clone() const
{
    return new Unit(m_symbol);
}

regular_ptr Unit::operator|(const regular_ptr &reg) const
{
    if (dynamic_cast<const Empty*>(reg.get()) || *this == reg)
        return clone();

    if (dynamic_cast<const Epsilon*>(reg.get()))
        return new Optional(clone());

    return new Union(clone(), reg);
}

regular_ptr Unit::operator+(const regular_ptr &reg) const
{
    if (dynamic_cast<const Empty*>(reg.get()) ||
            dynamic_cast<const Epsilon*>(reg.get()))
        return clone();

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

simone_node_ptr Unit::node_myself()
{
    auto unit = new UnitNode();
    unit->m_symbol = m_symbol;
    return unit;
}

/* --------------------- Union --------------------- */

regular_ptr Union::clone() const
{
    return new Union(m_left_expression, m_right_expression);
}

regular_ptr Union::operator|(const regular_ptr &reg) const
{
    if (dynamic_cast<const Empty*>(reg.get()) || *this == reg)
        return clone();

    if (dynamic_cast<const Epsilon*>(reg.get()))
        return new Optional(clone());

    return new Union(clone(), reg);
}

regular_ptr Union::operator+(const regular_ptr &reg) const
{
    if (dynamic_cast<const Empty*>(reg.get()) ||
            dynamic_cast<const Epsilon*>(reg.get()))
        return clone();

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

simone_node_ptr Union::node_myself()
{
    auto union_ptr = new UnionNode();
    
    union_ptr->m_left = m_left_expression->node_myself();
    union_ptr->m_right = m_right_expression->node_myself();
    
    return union_ptr;
}

/* --------------------- Concatenation --------------------- */

regular_ptr Concatenation::clone() const
{
    return new Concatenation(m_left_expression, m_right_expression);
}

regular_ptr Concatenation::operator|(const regular_ptr &reg) const
{
    if (dynamic_cast<const Empty*>(reg.get()) || *this == reg)
        return clone();

    if (dynamic_cast<const Epsilon*>(reg.get()))
        return new Optional(clone());

    return new Union(clone(), reg);
}

regular_ptr Concatenation::operator+(const regular_ptr &reg) const
{
    if (dynamic_cast<const Empty*>(reg.get()) ||
            dynamic_cast<const Epsilon*>(reg.get()))
        return clone();

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

simone_node_ptr Concatenation::node_myself()
{
    auto concatenation_ptr = new ConcatenationNode();
    
    concatenation_ptr->m_left = m_left_expression->node_myself();
    concatenation_ptr->m_right = m_right_expression->node_myself();
    
    return concatenation_ptr;
}

/* --------------------- ReflexiveClosure --------------------- */

regular_ptr ReflexiveClosure::clone() const
{
    return new ReflexiveClosure(m_expression);
}

regular_ptr ReflexiveClosure::operator|(const regular_ptr &reg) const
{
    if (dynamic_cast<const Empty*>(reg.get()) || *this == reg)
        return clone();

    if (dynamic_cast<const Epsilon*>(reg.get()))
        return new Optional(clone());

    return new Union(clone(), reg);
}

regular_ptr ReflexiveClosure::operator+(const regular_ptr &reg) const
{
    if (dynamic_cast<const Empty*>(reg.get()) ||
            dynamic_cast<const Epsilon*>(reg.get()))
        return clone();

    return new Concatenation(clone(), reg);
}

regular_ptr ReflexiveClosure::operator^(const Operation &op) const
{
    switch (op)
    {
    case Operation::Star :
        return clone();

    case Operation::Plus :
        return clone();

    case Operation::Optional :
        return clone();
    }
}

bool ReflexiveClosure::operator==(const regular_ptr &reg) const
{
    const ReflexiveClosure * check = dynamic_cast<const ReflexiveClosure*>(reg.get());
    
    if (!check)
        return false;

    return m_expression == check->m_expression;
}

simone_node_ptr ReflexiveClosure::node_myself()
{
    auto reflexive_ptr = new ReflexiveNode();
    
    reflexive_ptr->m_left = m_expression->node_myself();
    
    return reflexive_ptr;
}

/* --------------------- TransitiveClosure --------------------- */

regular_ptr TransitiveClosure::clone() const
{
    return new TransitiveClosure(m_expression);
}

regular_ptr TransitiveClosure::operator|(const regular_ptr &reg) const
{
    if (dynamic_cast<const Empty*>(reg.get()) || *this == reg)
        return clone();

    if (dynamic_cast<const Epsilon*>(reg.get()))
        return new Optional(clone());

    return new Union(clone(), reg);
}

regular_ptr TransitiveClosure::operator+(const regular_ptr &reg) const
{
    if (dynamic_cast<const Empty*>(reg.get()) ||
            dynamic_cast<const Epsilon*>(reg.get()))
        return clone();

    return new Concatenation(clone(), reg);
}

regular_ptr TransitiveClosure::operator^(const Operation &op) const
{
    switch (op)
    {
    case Operation::Star :
        return new ReflexiveClosure(m_expression);

    case Operation::Plus :
        return clone();

    case Operation::Optional :
        return new ReflexiveClosure(m_expression);
    }
}

bool TransitiveClosure::operator==(const regular_ptr &reg) const
{
    const TransitiveClosure * check = dynamic_cast<const TransitiveClosure*>(reg.get());
    
    if (!check)
        return false;

    return m_expression == check->m_expression;
}

simone_node_ptr TransitiveClosure::node_myself()
{
    auto transitive_ptr = new ConcatenationNode();
    auto reflexive_ptr = new ReflexiveNode();

    auto transitive_left_ptr = m_expression->node_myself();
    auto reflexive_left_ptr = m_expression->node_myself();

    transitive_ptr->m_left = transitive_left_ptr;
    transitive_ptr->m_right = reflexive_ptr;

    reflexive_ptr->m_left = reflexive_left_ptr;
    
    return transitive_ptr;
}

/* --------------------- Optional --------------------- */

regular_ptr Optional::clone() const
{
    return new Optional(m_expression);
}

regular_ptr Optional::operator|(const regular_ptr &reg) const
{
    if (dynamic_cast<const Empty*>(reg.get()) ||
            dynamic_cast<const Epsilon*>(reg.get()) ||
            *this == reg)
        return clone();

    return new Union(clone(), reg);
}

regular_ptr Optional::operator+(const regular_ptr &reg) const
{
    if (dynamic_cast<const Empty*>(reg.get()) ||
            dynamic_cast<const Epsilon*>(reg.get()))
        return clone();

    return new Concatenation(clone(), reg);
}

regular_ptr Optional::operator^(const Operation &op) const
{
    switch (op)
    {
    case Operation::Star :
        return new ReflexiveClosure(m_expression);

    case Operation::Plus :
        return new ReflexiveClosure(m_expression);

    case Operation::Optional :
        return clone();
    }
}

bool Optional::operator==(const regular_ptr &reg) const
{
    const Optional * check = dynamic_cast<const Optional*>(reg.get());
    
    if (!check)
        return false;

    return m_expression == check->m_expression;
}

simone_node_ptr Optional::node_myself()
{
    auto optional_ptr = new OptionalNode();
    
    optional_ptr->m_left = m_expression->node_myself();
    
    return optional_ptr;
}

} // namespace expression
} // namespace formal_device
