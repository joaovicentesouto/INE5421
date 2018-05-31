
#include "FiniteAutomatonParser.hpp"

namespace formal_device
{
namespace parser
{

ndfa_type create_automaton(std::set<std::string> & symbols, std::set<std::string> & states,
                           std::map<std::string, std::map<std::string, std::set<std::string>>> & transitions)
{
    state_set_type  m_states;
    symbol_set_type m_alphabet;
    state_type m_initial_state;
    state_set_type  m_final_states;
    non_det_transition_map_type m_transitions;

    for (auto symbol : symbols)
        m_alphabet.insert(NonDeterministic::symbol_type(symbol));

    for (auto state : states) {

        std::string state_name = state;
        state_name.erase(std::remove(state_name.begin(), state_name.end(), '*'), state_name.end());
        state_name.erase(std::remove(state_name.begin(), state_name.end(), '-'), state_name.end());
        state_name.erase(std::remove(state_name.begin(), state_name.end(), '>'), state_name.end());

        for (auto aux : state) {
            if (aux == '*')
                m_final_states.insert(state_name);
            if (aux == '-') {
                m_initial_state = state_type(state_name);
                break;
            }
        }
        m_states.insert(state_name);
    }

    for (auto trans : transitions) {
        for (auto sym_States : trans.second) {
            NonDeterministic::symbol_type symbol(sym_States.first);

            for (auto state : sym_States.second)
                m_transitions[trans.first][symbol].insert(state);
        }
    }

    return NonDeterministic(m_alphabet, m_states, m_transitions, m_final_states, m_initial_state);
}

}  // namespace parser
}  // namespace formal_device
