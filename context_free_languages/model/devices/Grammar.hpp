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
    enum class Recursion
    {
        Direct,
        Indirect
    };

    template<class T>
    using set_type                 = std::set<T>;
    
    template<class Key, class Value>
    using map_type                 = std::map<Key, Value>;

    using string_type              = std::string;
    using symbol_ptr_type          = SymbolPointer;
    using symbol_type              = Symbol;
    using terminal_symbol_type     = TerminalSymbol;
    using non_terminal_symbol_type = NonTerminalSymbol;
    using production_type          = Production;

    using terminal_set_type        = set_type<terminal_symbol_type>;
    using non_terminal_set_type    = set_type<non_terminal_symbol_type>;
    using symbol_ptr_set_type      = set_type<symbol_ptr_type>;
    using production_map_type      = map_type<non_terminal_symbol_type, set_type<production_type>>;
    using resursion_map_type       = map_type<non_terminal_symbol_type, set_type<Recursion>>;
    using simple_production_map_type = map_type<non_terminal_symbol_type, set_type<non_terminal_symbol_type>>;

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

    const non_terminal_set_type &vn() const;
    const terminal_set_type &vt() const;
    const production_map_type &productions() const;
    const non_terminal_symbol_type &initial_symbol() const;
    string_type to_string() const;

    ContextFree own(non_terminal_set_type &derives_epsilon,
                    simple_production_map_type &na,
                    non_terminal_set_type &fertile_symbols,
                    symbol_ptr_set_type &reachable_symbols) const;

    ContextFree epsilon_free(non_terminal_set_type &derives_epsilon) const;
    ContextFree remove_simple_productions(simple_production_map_type &na) const;

    ContextFree remove_infertile_symbols(non_terminal_set_type &fertile_symbols) const;
    ContextFree remove_unreachable_symbols(symbol_ptr_set_type &reachable_symbols) const;
    ContextFree remove_useless_symbols(non_terminal_set_type &fertile_symbols,
                                       symbol_ptr_set_type &reachable_symbols) const;

    ContextFree factor(unsigned max_steps) const;
    ContextFree remove_recursion(resursion_map_type &recursions) const;

    bool emptiness() const;
    bool finitude() const;
    bool is_factored() const;
    bool has_recursion() const;

    bool operator==(const ContextFree &ContextFree) const;
    bool operator!=(const ContextFree &ContextFree) const;

  public:
    non_terminal_symbol_type m_initial_symbol{"S"};
    non_terminal_set_type m_vn{m_initial_symbol};
    terminal_set_type m_vt;
    production_map_type m_productions;
};

} // namespace grammar
} // namespace formal_device

#endif // DEVICES_GRAMMAR_HPP
