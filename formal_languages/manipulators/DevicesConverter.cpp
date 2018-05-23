#include "DevicesConverter.hpp"

namespace formal_device
{
namespace manipulator
{

DevicesConverter::ndfa_type DevicesConverter::convert(const grammar_type & grammar)
{
    ndfa_type::state_type          end("END");
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
    dfa_type minimum = ndfa.minimization();

    grammar_type::vocabulary_set_type vn;
    grammar_type::vocabulary_set_type vt;
    grammar_type::production_map_type productions;
    grammar_type::symbol_type initial_symbol{minimum.m_initial_state.value()};

    dfa_type::state_set_type states(minimum.m_states);
    dfa_type::state_set_type final_states(minimum.m_final_states);

    for (auto state : states)
    {
        dfa_type::transition_map_type transitions(minimum.m_transitions);

        if (transitions.find(state) != transitions.end())
            vn.insert(state.value());

        for (auto transition : transitions[state])
        {
            auto symbol = transition.first;
            auto target = transition.second;

            if (final_states.find(target) != final_states.end())
            {
                vt.insert(symbol.value());
                productions[state.value()].insert(new grammar::TerminalProduction(symbol.value()));
            }

            if (minimum.m_transitions.find(target) != minimum.m_transitions.end())
            {
                vt.insert(symbol.value());
                productions[state.value()].insert(new grammar::NonTerminalProduction(symbol.value(), target.value()));
            }
        }
    }

    return grammar_type(std::move(vn),
                        std::move(vt),
                        std::move(productions),
                        std::move(initial_symbol));
}

}   // namespace manipulator
}   // namespace formal_device
