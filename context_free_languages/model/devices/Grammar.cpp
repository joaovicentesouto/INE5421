#include "Grammar.hpp"

namespace formal_device
{
namespace grammar
{

const ContextFree::non_terminal_set_type &ContextFree::vn() const
{
    return m_vn;
}

const ContextFree::terminal_set_type &ContextFree::vt() const
{
    return m_vt;
}

const ContextFree::production_map_type &ContextFree::productions() const
{
    return m_productions;
}

const ContextFree::non_terminal_symbol_type &ContextFree::initial_symbol() const
{
    return m_initial_symbol;
}

bool ContextFree::operator==(const ContextFree &ContextFree) const
{
    return m_vn             == ContextFree.m_vn
        && m_vt             == ContextFree.m_vt
        && m_productions    == ContextFree.m_productions
        && m_initial_symbol == ContextFree.m_initial_symbol;
}

bool ContextFree::operator!=(const ContextFree &ContextFree) const
{
    return m_vn             != ContextFree.m_vn
        || m_vt             != ContextFree.m_vt
        || m_productions    != ContextFree.m_productions
        || m_initial_symbol != ContextFree.m_initial_symbol;
}

ContextFree ContextFree::own(non_terminal_set_type &derives_epsilon,
                             simple_production_map_type &na,
                             non_terminal_set_type &fertile_symbols,
                             symbol_ptr_set_type &reachable_symbols) const
{
    return ContextFree();
}

ContextFree ContextFree::epsilon_free(non_terminal_set_type &derives_epsilon) const
{
    return ContextFree();
}

ContextFree ContextFree::remove_simple_productions(simple_production_map_type &na) const
{
    return ContextFree();
}

template<class T, class V>
bool contains(const ContextFree::set_type<T>& set, const V& value)
{
    auto value_cast = dynamic_cast<const T*>(&value);

    if (!value_cast)
        return false;

    return set.find(*value_cast) != set.end();
}

ContextFree ContextFree::remove_infertile_symbols(non_terminal_set_type &fertile_symbols) const
{
    non_terminal_set_type previous;
    production_map_type productions(m_productions);
    non_terminal_set_type still_infertile(m_vn);

    do
    {
        previous = fertile_symbols;

        for (const auto& symbol : non_terminal_set_type{still_infertile})
        {
            bool fertile = false;

            for (const auto& prod : productions[symbol])
            {
                fertile = true;

                for (const auto& alfa : prod)
                    fertile &= alfa->is_terminal() | contains(fertile_symbols, *alfa);

                if (fertile)
                    break;
            }

            if (fertile)
            {
                still_infertile.erase(symbol);
                fertile_symbols.insert(symbol);
            }
        }


    } while (fertile_symbols != previous);

    non_terminal_set_type new_vn{fertile_symbols};
    terminal_set_type new_vt;
    production_map_type new_productions;
    non_terminal_symbol_type new_initial_symbol{m_initial_symbol};

    if (!contains(fertile_symbols, m_initial_symbol))
        return ContextFree();

    for (const auto& fertile : fertile_symbols)
        for (const auto& prod : productions[fertile])
        {
            bool fertile_production = true;
            for (const auto& symbol : prod)
                fertile_production &= symbol->is_terminal() | contains(fertile_symbols, *symbol);

            if (fertile_production)
                new_productions[fertile].insert(prod);
        }

    for (const auto& pair : new_productions)
        for (const auto& prod : pair.second)
            for (const auto& symbol : prod)
                if (symbol->is_terminal())
                {
                    terminal_symbol_type term = *dynamic_cast<const terminal_symbol_type*>(symbol.get());
                    new_vt.insert(term);
                }

    return ContextFree(new_vn, new_vt, new_productions, new_initial_symbol);
}

ContextFree ContextFree::remove_unreachable_symbols(symbol_ptr_set_type &reachable_symbols) const
{
    return ContextFree();
}

ContextFree ContextFree::remove_useless_symbols(non_terminal_set_type &fertile_symbols,
                                                symbol_ptr_set_type &reachable_symbols) const
{
    return ContextFree();
}

ContextFree ContextFree::factor(unsigned max_steps) const
{
    return ContextFree();
}

ContextFree ContextFree::remove_recursion(resursion_map_type &recursions) const
{
    return ContextFree();
}

bool ContextFree::emptiness() const
{
    return false;
}

bool ContextFree::finitude() const
{
    return false;
}

bool ContextFree::is_factored() const
{
    return false;
}

bool ContextFree::has_recursion() const
{
    return false;
}

ContextFree::string_type ContextFree::to_string() const
{
    string_type string;
    string = m_initial_symbol.value() + " -> ";

    // auto productions(m_productions);

    // int i = productions[m_initial_symbol].size();
    // for (auto production : productions[m_initial_symbol])
    // {
    //     if (production->is_terminal())
    //         string += " " + production->to_string() + " ";
    //     else
    //         string += production->to_string();

    //     if (--i > 0)
    //         string += " | ";
    // }

    // string += "\n";

    // for (auto non_terminal : m_vn)
    // {
    //     if (non_terminal == m_initial_symbol)
    //         continue;

    //     string += non_terminal.value() + " -> ";

    //     i = productions[non_terminal].size();
    //     for (auto production : productions[non_terminal])
    //     {
    //         if (production->is_terminal())
    //             string += " " + production->to_string() + " ";
    //         else
    //             string += production->to_string();

    //         if (--i > 0)
    //             string += " | ";
    //     }
    //     string += "\n";
    // }

    return string;
}

} // namespace grammar
} // namespace formal_device