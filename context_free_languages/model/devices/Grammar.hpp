//! João Vicente Souto e Bruno Izaias Bonotto

#ifndef DEVICES_GRAMMAR_HPP
#define DEVICES_GRAMMAR_HPP

#include <set>
#include <map>
#include <functional>
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
    using first_map_type           = map_type<symbol_ptr_type, terminal_set_type>;
    using follow_map_type          = map_type<non_terminal_symbol_type, terminal_set_type>;
    using production_map_type      = map_type<non_terminal_symbol_type, set_type<production_type>>;
    using recursion_map_type       = map_type<non_terminal_symbol_type, map_type<Recursion, non_terminal_set_type>>;
    using simple_production_map_type = map_type<non_terminal_symbol_type, set_type<non_terminal_symbol_type>>;

    // Class constructors
    ContextFree();

    ContextFree(const ContextFree &) = default;
    ContextFree &operator=(const ContextFree &) = default;

    ContextFree(ContextFree &&) = default;
    ContextFree &operator=(ContextFree &&) = default;

    template <class Arg1, class Arg2, class Arg3, class Arg4>
    ContextFree(Arg1 &&vn, Arg2 &&vt, Arg3 &&productions, Arg4 &&initial_symbol) :
        m_initial_symbol{std::forward<Arg4>(initial_symbol)},
        m_vn{std::forward<Arg1>(vn)},
        m_vt{std::forward<Arg2>(vt)},
        m_productions{std::forward<Arg3>(productions)}
    {
        calculate_first();
        calculate_follow();
    }

    const non_terminal_set_type &vn() const;
    const terminal_set_type &vt() const;
    const production_map_type &productions() const;
    const non_terminal_symbol_type &initial_symbol() const;
    first_map_type first() const;
    follow_map_type follow() const;
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
    ContextFree remove_recursion(recursion_map_type &recursions) const;

    bool emptiness() const;
    bool finitiness() const;
    bool is_factored() const;
    bool has_recursion() const;

    bool operator==(const ContextFree &another) const;
    bool operator!=(const ContextFree &another) const;
    bool operator<(const ContextFree &another) const;

  private:
    void calculate_first();
    void calculate_follow();
    bool contains_cycle(non_terminal_symbol_type state,
                        non_terminal_set_type & temporary,
                        non_terminal_set_type & permanent) const;

    non_terminal_symbol_type m_initial_symbol{"S"};
    non_terminal_set_type    m_vn{m_initial_symbol};
    terminal_set_type        m_vt;
    production_map_type      m_productions;
    first_map_type           m_first;
    follow_map_type          m_follow;
};

} // namespace grammar
} // namespace formal_device

#endif // DEVICES_GRAMMAR_HPP
