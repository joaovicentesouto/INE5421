//! João Vicente Souto e Bruno Izaias Bonotto

#ifndef DEVICES_GRAMMAR_HPP
#define DEVICES_GRAMMAR_HPP

#include <set>
#include <map>
#include <context_free_languages/model/components/GrammarComponents.hpp>


namespace formal_device
{
namespace grammar
{

class ContextFree
{
  public:

    template <class T>
    using set_type                 = std::set<T>;
    template <class Key, class Value>
    using map_type                 = std::map<Key, Value>;

    using string_type              = std::string;
    using symbol_ptr_type          = SymbolPointer;
    using symbol_type              = Symbol;
    using terminal_symbol_type     = TerminalSymbol;
    using non_terminal_symbol_type = NonTerminalSymbol;
    using production_type          = Production;

    using terminal_set_type        = set_type<terminal_symbol_type>;
    using non_terminal_set_type    = set_type<non_terminal_symbol_type>;
    using production_map_type      = map_type<non_terminal_symbol_type, set_type<production_type>>;

    // Class constructors
    ContextFree() = default;

    ContextFree(const ContextFree &) = default;
    ContextFree &operator=(const ContextFree &) = default;

    ContextFree(ContextFree &&) = default;
    ContextFree &operator=(ContextFree &&) = default;

    template <class Arg1, class Arg2, class Arg3, class Arg4>
    ContextFree(Arg1 &&vn, Arg2 &&vt, Arg3 &&productions, Arg4 &&initial_symbol) :
        m_vn{std::forward<Arg1>(vn)},
        m_vt{std::forward<Arg2>(vt)},
        m_productions{std::forward<Arg3>(productions)},
        m_initial_symbol{std::forward<Arg4>(initial_symbol)}
    {
    }

    const non_terminal_set_type& vn() const;
    const terminal_set_type& vt() const;
    const production_map_type& productions() const;
    const non_terminal_symbol_type& initial_symbol() const;
    string_type to_string() const;

    bool operator==(const ContextFree &ContextFree) const;

  public:
    non_terminal_set_type    m_vn;
    terminal_set_type        m_vt;
    production_map_type      m_productions;
    non_terminal_symbol_type m_initial_symbol{"S"};
};

}   // namespace grammar
}   // namespace formal_device

#endif // DEVICES_GRAMMAR_HPP
