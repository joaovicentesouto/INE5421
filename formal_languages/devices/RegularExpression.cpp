#include "RegularExpression.hpp"

namespace formal_device
{
namespace expression
{

RegularPointer::RegularPointer() :
    std::shared_ptr<Regular>(new Empty())
{

}

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

string_type RegularPointer::to_string() const
{
    return get()->to_string();
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

simone_node_ptr Empty::node_myself() const
{
    auto unit = new UnitNode();
    unit->m_symbol = "Empty";
    return unit;
}

string_type Empty::to_string() const
{
    return "";
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

simone_node_ptr Epsilon::node_myself() const
{
    auto unit = new UnitNode();
    unit->m_symbol = "&";
    return unit;
}

string_type Epsilon::to_string() const
{
    return "&";
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
        return (*this)^Operation::Optional;

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
    case Operation::Reflexive :
        return new ReflexiveClosure(clone());

    case Operation::Transitive :
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

simone_node_ptr Unit::node_myself() const
{
    auto unit = new UnitNode();
    unit->m_symbol = m_symbol;
    return unit;
}

string_type Unit::to_string() const
{
    return m_symbol;
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
        return (*this)^Operation::Optional;

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
    case Operation::Reflexive :
        return new ReflexiveClosure(clone());

    case Operation::Transitive :
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

simone_node_ptr Union::node_myself() const
{
    auto union_ptr = new UnionNode();
    
    union_ptr->m_left = m_left_expression->node_myself();
    union_ptr->m_right = m_right_expression->node_myself();
    
    return union_ptr;
}

string_type Union::to_string() const
{
    return m_left_expression->to_string() + " | " + m_right_expression->to_string();
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
        return (*this)^Operation::Optional;

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
    case Operation::Reflexive :
        return new ReflexiveClosure(clone());

    case Operation::Transitive :
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

simone_node_ptr Concatenation::node_myself() const
{
    auto concatenation_ptr = new ConcatenationNode();
    
    concatenation_ptr->m_left = m_left_expression->node_myself();
    concatenation_ptr->m_right = m_right_expression->node_myself();
    
    return concatenation_ptr;
}

string_type Concatenation::to_string() const
{
    return m_left_expression->to_string() + m_right_expression->to_string();
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
        return (*this)^Operation::Optional;

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
    case Operation::Reflexive :
        return clone();

    case Operation::Transitive :
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

simone_node_ptr ReflexiveClosure::node_myself() const
{
    auto reflexive_ptr = new ReflexiveNode();
    
    reflexive_ptr->m_left = m_expression->node_myself();
    
    return reflexive_ptr;
}

string_type ReflexiveClosure::to_string() const
{
    auto empty = dynamic_cast<const Empty*>(m_expression.get());

    if (empty)
        return "";

    auto epsilon = dynamic_cast<const Epsilon*>(m_expression.get());

    if (epsilon)
        return m_expression->to_string();

    auto unit = dynamic_cast<const Unit*>(m_expression.get());

    if (unit)
        return m_expression->to_string() + "*";

    return "(" + m_expression->to_string() + ")*";
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
        return (*this)^Operation::Optional;

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
    case Operation::Reflexive :
        return m_expression^Operation::Reflexive;

    case Operation::Transitive :
        return clone();

    case Operation::Optional :
        return m_expression^Operation::Reflexive;
    }
}

bool TransitiveClosure::operator==(const regular_ptr &reg) const
{
    const TransitiveClosure * check = dynamic_cast<const TransitiveClosure*>(reg.get());
    
    if (!check)
        return false;

    return m_expression == check->m_expression;
}

simone_node_ptr TransitiveClosure::node_myself() const
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

string_type TransitiveClosure::to_string() const
{
    auto empty = dynamic_cast<const Empty*>(m_expression.get());

    if (empty)
        return "";

    auto epsilon = dynamic_cast<const Epsilon*>(m_expression.get());

    if (epsilon)
        return m_expression->to_string();

    auto unit = dynamic_cast<const Unit*>(m_expression.get());

    if (unit)
        return m_expression->to_string() + "+";

    return "(" + m_expression->to_string() + ")+";
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
    case Operation::Reflexive :
        return m_expression^Operation::Reflexive;

    case Operation::Transitive :
        return m_expression^Operation::Reflexive;

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

simone_node_ptr Optional::node_myself() const
{
    auto optional_ptr = new OptionalNode();
    
    optional_ptr->m_left = m_expression->node_myself();
    
    return optional_ptr;
}

string_type Optional::to_string() const
{
    auto empty = dynamic_cast<const Empty*>(m_expression.get());

    if (empty)
        return "";

    auto epsilon = dynamic_cast<const Epsilon*>(m_expression.get());

    if (epsilon)
        return m_expression->to_string();

    auto unit = dynamic_cast<const Unit*>(m_expression.get());

    if (unit)
        return m_expression->to_string() + "?";

    return "(" + m_expression->to_string() + ")?";
}

} // namespace expression
} // namespace formal_device
