#include "DevicesConverter.h"

namespace formal_device
{
namespace converter
{

DevicesConverter::ndfa_type DevicesConverter::convert(const grammar_type & grammar)
{
    ndfa_type::state_type end("END");
    ndfa_type::symbol_set_type     alphabet;
    ndfa_type::state_set_type      states{end};
    ndfa_type::transition_map_type transitions;
    ndfa_type::state_set_type      final_states{end};
    ndfa_type::state_type          initial_state(grammar.m_initial_symbol.value());

    for (auto symbol : grammar.m_vt)
        alphabet.insert(ndfa_type::symbol_type(symbol.value()));

    for (auto state : grammar.m_vn)
    {
        auto new_state = ndfa_type::state_type(state.value());
        states.insert(new_state);

        grammar_type::production_map_type copy(grammar.m_productions);
        for (auto production : copy[state])
        {
            auto symbol = ndfa_type::symbol_type(production->terminal());

            if (production->is_terminal())
            {
                transitions[new_state][symbol].insert(end);
            } else {
                auto target = ndfa_type::state_type(production->non_terminal());
                transitions[new_state][symbol].insert(target);
            }
        }
    }

    return ndfa_type(std::move(alphabet),
                     std::move(states),
                     std::move(transitions),
                     std::move(final_states),
                     std::move(initial_state));
}

DevicesConverter::grammar_type DevicesConverter::convert(const ndfa_type & ndfa)
{

    return grammar_type();
}

}   // namespace converter
}   // namespace formal_device
