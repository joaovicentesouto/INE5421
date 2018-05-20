#ifndef DEVICES_REGULAREXPRESSION_COMPONENTS_HPP
#define DEVICES_REGULAREXPRESSION_COMPONENTS_HPP

#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <exception>
#include <formal_languages/components/DeSimoneTreeComponents.hpp>

namespace formal_device
{
namespace expression
{

enum class Operation
{
    Star,
    Plus,
    Optional
};

class Regular;
class RegularPointer : public std::shared_ptr<Regular>
{
  public:
    RegularPointer(Regular * reg);

    RegularPointer(const RegularPointer &) = default;
    RegularPointer &operator=(const RegularPointer &) = default;
    RegularPointer(RegularPointer &&) = default;
    RegularPointer &operator=(RegularPointer &&) = default;

    RegularPointer operator|(const RegularPointer &reg) const;
    RegularPointer operator+(const RegularPointer &reg) const;
    RegularPointer operator^(const Operation &op) const;
    bool operator==(const RegularPointer &reg) const;
};

using string_type = std::string;
using regular_ptr = RegularPointer;
using simone_node_ptr = DeSimoneNode*;

class Regular
{
  public:
    virtual ~Regular() {}

    virtual regular_ptr operator|(const regular_ptr &reg) const = 0;  // Union
    virtual regular_ptr operator+(const regular_ptr &reg) const = 0;  // Concatenate
    virtual regular_ptr operator^(const Operation &op) const = 0;     // Closure
    virtual bool operator==(const regular_ptr &reg) const = 0;

    virtual simone_node_ptr node_myself() = 0;

  private:
    virtual regular_ptr clone() const = 0;
};

class Empty : public Regular
{
  public:
    Empty() = default;

    Empty(const Empty &) = default;
    Empty &operator=(const Empty &) = default;
    Empty(Empty &&) = default;
    Empty &operator=(Empty &&) = default;

    ~Empty() = default;

    regular_ptr operator|(const regular_ptr &reg) const;
    regular_ptr operator+(const regular_ptr &reg) const;
    regular_ptr operator^(const Operation &op) const;
    bool operator==(const regular_ptr &reg) const;

    simone_node_ptr node_myself();

  private:
    regular_ptr clone() const;
};

class Epsilon : public Regular
{
  public:
    Epsilon() = default;
    
    Epsilon(const Epsilon &) = default;
    Epsilon &operator=(const Epsilon &) = default;
    Epsilon(Epsilon &&) = default;
    Epsilon &operator=(Epsilon &&) = default;

    ~Epsilon() = default;

    regular_ptr operator|(const regular_ptr &reg) const;
    regular_ptr operator+(const regular_ptr &reg) const;
    regular_ptr operator^(const Operation &op) const;
    bool operator==(const regular_ptr &reg) const;

    simone_node_ptr node_myself();

  private:
    regular_ptr clone() const;

    string_type m_symbol{"&"};
};

class Unit : public Regular
{
  public:
    Unit() = delete;

    Unit(const Unit &) = default;
    Unit &operator=(const Unit &) = default;
    Unit(Unit &&) = default;
    Unit &operator=(Unit &&) = default;

    template<class Arg1>
    Unit(Arg1 &&symbol) :
        m_symbol{std::forward<Arg1>(symbol)}
    {
    }

    ~Unit() = default;

    regular_ptr operator|(const regular_ptr &reg) const;
    regular_ptr operator+(const regular_ptr &reg) const;
    regular_ptr operator^(const Operation &op) const;
    bool operator==(const regular_ptr &reg) const;

    simone_node_ptr node_myself();

  private:
    regular_ptr clone() const;

    string_type m_symbol;
};

class Union : public Regular
{
  public:
    Union() = delete;

    Union(const Union &) = default;
    Union &operator=(const Union &) = default;
    Union(Union &&) = default;
    Union &operator=(Union &&) = default;

    template<class Arg1, class Arg2>
    Union(Arg1 &&left_exp, Arg2 &&right_exp) :
        m_left_expression{std::forward<Arg1>(left_exp)},
        m_right_expression{std::forward<Arg2>(right_exp)}
    {
    }

    ~Union() = default;

    regular_ptr operator|(const regular_ptr &reg) const;
    regular_ptr operator+(const regular_ptr &reg) const;
    regular_ptr operator^(const Operation &op) const;
    bool operator==(const regular_ptr &reg) const;

    simone_node_ptr node_myself();

  private:
    regular_ptr clone() const;

    regular_ptr m_left_expression;
    regular_ptr m_right_expression;
};

class Concatenation : public Regular
{
  public:
    Concatenation() = delete;

    Concatenation(const Concatenation &) = default;
    Concatenation &operator=(const Concatenation &) = default;
    Concatenation(Concatenation &&) = default;
    Concatenation &operator=(Concatenation &&) = default;

    template<class Arg1, class Arg2>
    Concatenation(Arg1 &&left_exp, Arg2 &&right_exp) :
        m_left_expression{std::forward<Arg1>(left_exp)},
        m_right_expression{std::forward<Arg2>(right_exp)}
    {
    }

    ~Concatenation() = default;

    regular_ptr operator|(const regular_ptr &reg) const;
    regular_ptr operator+(const regular_ptr &reg) const;
    regular_ptr operator^(const Operation &op) const;
    bool operator==(const regular_ptr &reg) const;

    simone_node_ptr node_myself();

  private:
    regular_ptr clone() const;

    regular_ptr m_left_expression;
    regular_ptr m_right_expression;
};

class ReflexiveClosure : public Regular
{
  public:
    ReflexiveClosure() = delete;

    ReflexiveClosure(const ReflexiveClosure &) = default;
    ReflexiveClosure &operator=(const ReflexiveClosure &) = default;
    ReflexiveClosure(ReflexiveClosure &&) = default;
    ReflexiveClosure &operator=(ReflexiveClosure &&) = default;

    template<class Arg1>
    ReflexiveClosure(Arg1 &&exp) :
        m_expression{std::forward<Arg1>(exp)}
    {
    }

    ~ReflexiveClosure() = default;

    regular_ptr operator|(const regular_ptr &reg) const;
    regular_ptr operator+(const regular_ptr &reg) const;
    regular_ptr operator^(const Operation &op) const;
    bool operator==(const regular_ptr &reg) const;

    simone_node_ptr node_myself();

  private:
    regular_ptr clone() const;

    regular_ptr m_expression;
};

class TransitiveClosure : public Regular
{
  public:
    TransitiveClosure() = delete;

    TransitiveClosure(const TransitiveClosure &) = default;
    TransitiveClosure &operator=(const TransitiveClosure &) = default;
    TransitiveClosure(TransitiveClosure &&) = default;
    TransitiveClosure &operator=(TransitiveClosure &&) = default;

    template<class Arg1>
    TransitiveClosure(Arg1 &&exp) :
        m_expression{std::forward<Arg1>(exp)}
    {
    }

    ~TransitiveClosure() = default;

    regular_ptr operator|(const regular_ptr &reg) const;
    regular_ptr operator+(const regular_ptr &reg) const;
    regular_ptr operator^(const Operation &op) const;
    bool operator==(const regular_ptr &reg) const;

    simone_node_ptr node_myself();

  private:
    regular_ptr clone() const;

    regular_ptr m_expression;
};

class Optional : public Regular
{
  public:
    Optional() = delete;

    Optional(const Optional &) = default;
    Optional &operator=(const Optional &) = default;
    Optional(Optional &&) = default;
    Optional &operator=(Optional &&) = default;

    template<class Arg1>
    Optional(Arg1 &&exp) :
        m_expression{std::forward<Arg1>(exp)}
    {
    }

    ~Optional() = default;

    regular_ptr operator|(const regular_ptr &reg) const;
    regular_ptr operator+(const regular_ptr &reg) const;
    regular_ptr operator^(const Operation &op) const;
    bool operator==(const regular_ptr &reg) const;

    simone_node_ptr node_myself();

  private:
    regular_ptr clone() const;

    regular_ptr m_expression;
};

} // namespace expression
} // namespace formal_device

#endif // DEVICES_REGULAREXPRESSION_COMPONENTS_HPP
