#include "Grammar.hpp"

namespace formal_device
{
namespace grammar
{

const ContextFree::non_terminal_set_type& ContextFree::vn() const
{
    return m_vn;
}

const ContextFree::terminal_set_type& ContextFree::vt() const
{
    return m_vt;
}

const ContextFree::production_map_type& ContextFree::productions() const
{
    return m_productions;
}

const ContextFree::non_terminal_symbol_type& ContextFree::initial_symbol() const
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


}   // namespace grammar
}   // namespace formal_device
