#include "DevicesConverter.hpp"

namespace formal_device
{
namespace manipulator
{

DevicesConverter::ndfa_type DevicesConverter::convert(const grammar_type & grammar)
{
    ndfa_type::state_type          end("FIM");
    ndfa_type::symbol_set_type     alphabet;
    ndfa_type::state_set_type      states{end};
    ndfa_type::transition_map_type transitions;
    ndfa_type::state_set_type      final_states{end};
    ndfa_type::state_type          initial_state(grammar.m_initial_symbol.value());

    //! For each terminal symbol of the grammar, a corresponding symbol is created in the NDFA alphabet.
    for (auto symbol : grammar.m_vt)
        alphabet.insert(ndfa_type::symbol_type(symbol.value()));

    for (auto state : grammar.m_vn)
    {
        //! For each non-terminal symbol of the grammar, an equivalent state is created.
        auto new_state = ndfa_type::state_type(state.value());
        states.insert(new_state);

        grammar_type::production_map_type copy(grammar.m_productions);
        for (auto production : copy[state])
        {
            auto symbol = ndfa_type::symbol_type(production->terminal());

            //! Terminal Productions Create a new transition between state and final state.
            if (production->is_terminal())
                transitions[new_state][symbol].insert(end);
            else
            {
                //! Non-terminal Productions create a new transition between non-final states.
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
    using string_type = dfa_type::string_type;

    //! Function to transform the names of the States to only letters letters.
    std::function<string_type(string_type)> to_upper = [](string_type s) {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::toupper(c); });
        return s;
    };

    //! Minimize the machine.
    dfa_type minimum = ndfa.minimization();

    grammar_type::vocabulary_set_type vn;
    grammar_type::vocabulary_set_type vt;
    grammar_type::production_map_type productions;

    //! At first, the initial symbol is the initial state.
    grammar_type::symbol_type initial_symbol{to_upper(minimum.m_initial_state.value())};

    dfa_type::state_set_type states(minimum.m_states);
    dfa_type::state_set_type final_states(minimum.m_final_states);
    dfa_type::transition_map_type transitions(minimum.m_transitions);

    for (auto state : states)
    {
        //! Creates only non-terminal symbols that generate something.
        if (transitions.find(state) != transitions.end())
            vn.insert(to_upper(state.value()));

        for (auto transition : transitions[state])
        {
            auto symbol = transition.first;
            auto target = transition.second;

            //! If Target is a final state, it creates a terminal production.
            if (final_states.find(target) != final_states.end())
            {
                vt.insert(symbol.value());
                productions[to_upper(state.value())].insert(new grammar::TerminalProduction(symbol.value()));
            }

            //! If target generates something, then it creates a non-terminal production for it.
            if (transitions.find(target) != transitions.end())
            {
                vt.insert(symbol.value());
                productions[to_upper(state.value())].insert(new grammar::NonTerminalProduction(symbol.value(), to_upper(target.value())));
            }
        }
    }

    //! Se o estado inicial é final então então cria-se S’ -> S->prod | &
    if (final_states.find(minimum.m_initial_state) != final_states.end())
    {
        grammar_type::symbol_type new_initial_symbol(initial_symbol.value() + "\'");
        vt.insert(grammar_type::symbol_type("&"));
        productions[new_initial_symbol] = productions[initial_symbol];
        productions[new_initial_symbol].insert(new grammar::TerminalProduction(grammar_type::symbol_type("&")));
        initial_symbol = new_initial_symbol;
    }

    return grammar_type(std::move(vn),
                        std::move(vt),
                        std::move(productions),
                        std::move(initial_symbol));
}

}   // namespace manipulator
}   // namespace formal_device
