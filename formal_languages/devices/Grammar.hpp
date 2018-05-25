#ifndef DEVICES_GRAMMAR_HPP
#define DEVICES_GRAMMAR_HPP

#include <set>
#include <map>
#include <formal_languages/components/GrammarComponents.hpp>


namespace formal_device
{
namespace manipulator
{
    class DevicesConverter;
}
namespace grammar
{


class Regular
{
  public:
    friend class manipulator::DevicesConverter;

    template <class T>
    using set_type                     = std::set<T>;
    template <class Key, class Value>
    using map_type                     = std::map<Key, Value>;

    using string_type                  = std::string;
    using symbol_type                  = Symbol;
    using terminal_production_type     = TerminalProduction;
    using non_terminal_production_type = NonTerminalProduction;
    using production_type_ptr          = ProductionPointer;

    using vocabulary_set_type          = set_type<symbol_type>;
    using production_map_type          = map_type<symbol_type, set_type<production_type_ptr>>;
    using pair_production_type         = std::pair<symbol_type, set_type<production_type_ptr>>;

    // Class constructors
    Regular() = default;

    Regular(const Regular &) = default;
    Regular &operator=(const Regular &) = default;

    Regular(Regular &&) = default;
    Regular &operator=(Regular &&) = default;

    template <class Arg1, class Arg2, class Arg3, class Arg4>
    Regular(Arg1 &&vn, Arg2 &&vt, Arg3 &&productions, Arg4 &&initial_symbol) :
        m_vn{std::forward<Arg1>(vn)},
        m_vt{std::forward<Arg2>(vt)},
        m_productions{std::forward<Arg3>(productions)},
        m_initial_symbol{std::forward<Arg4>(initial_symbol)}
    {
    }

    const vocabulary_set_type& vn() const;
    const vocabulary_set_type& vt() const;
    const production_map_type& productions() const;
    const symbol_type& initial_symbol() const;
    string_type to_string() const;

    set_type<string_type> sentences_generator(int n) const;

    bool operator==(const Regular &regular);

  public:
    vocabulary_set_type m_vn;
    vocabulary_set_type m_vt;
    production_map_type m_productions;
    symbol_type         m_initial_symbol{"Error"};
};

}   // namespace grammar
}   // namespace formal_device

#endif // DEVICES_GRAMMAR_HPP
