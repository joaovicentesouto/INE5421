#include "DeSimoneTree.hpp"

namespace formal_device
{
namespace expression
{

DeSimoneTree::DeSimoneTree(RegularPointer exp)
{
    m_root = exp->node_myself();
    m_root->to_sew(nullptr);
}

DeSimoneTree::~DeSimoneTree()
{
    delete m_root;
}

DeSimoneTree::dfa_type DeSimoneTree::execute()
{
    using state_type       = dfa_type::state_type;
    using symbol_type      = dfa_type::symbol_type;
    using symbol_name_type = DeSimoneNode::symbol_name_type;
    using state_name_type  = DeSimoneNode::state_name_type;
    using node_set_type    = DeSimoneNode::node_set_type;
    using composition_type = DeSimoneNode::composition_type;

    dfa_type::set_type<symbol_name_type> alphabet;
    dfa_type::set_type<symbol_name_type> states;
    dfa_type::set_type<symbol_name_type> final_states;
    dfa_type::map_type<state_name_type,
                       dfa_type::map_type<symbol_name_type, state_name_type>
                      > transitions;

    std::deque<state_name_type> to_process;
    dfa_type::map_type<state_name_type, node_set_type> they_made_me;
    dfa_type::map_type<state_name_type, state_name_type> predecessors;
    composition_type compositions;

    int new_id = 0;

    // initial state
    state_name_type initial_state("q" + std::to_string(new_id++));
    states.insert(initial_state);

    // cria composicao do estado inicial
    {
        node_set_type marked;
        m_root->down(initial_state, compositions, marked);
    }

    // Cria estados a partir de q0
    for (auto composition : compositions[initial_state])
    {
        if (composition.first == "&")
        {
            final_states.insert(initial_state);
            continue;
        }

        state_name_type q("q" + std::to_string(new_id++));

        alphabet.insert(composition.first);
        states.insert(q);
        transitions[initial_state][composition.first] = q;
        predecessors[q] = initial_state;

        they_made_me[q] = composition.second;
        to_process.push_back(q);
    }

    // construi todos os estados menos se for equivalente
    while (!to_process.empty())
    {
        auto current = to_process.front();
        to_process.pop_front();

        node_set_type marked;

        for (auto node : they_made_me[current])
            node->up(current, compositions, marked);

        state_name_type equivalent = current;
        for (auto composition_state : compositions)
        {
            auto state = composition_state.first;
            if (current == state)
                continue;

            if (compositions[current] == compositions[state])
            {
                equivalent = state;
                break;
            }
        }

        if (equivalent == current)
        {
            // Não existe equivalente
            for (auto composition : compositions[current])
            {
                if (composition.first == "&")
                {
                    final_states.insert(current);
                    continue;
                }

                state_name_type q("q" + std::to_string(new_id++));

                alphabet.insert(composition.first);
                states.insert(q);
                transitions[current][composition.first] = q;
                predecessors[q] = current;

                they_made_me[q] = composition.second;
                to_process.push_back(q);
            }
        }
        else
        {
            // Existe equivalente então devo substituir esse cara
            states.erase(current);
            they_made_me.erase(current);
            compositions.erase(current);

            for (auto transition : transitions[predecessors[current]])
                if (transition.second == current) {
                    transition.second = equivalent;
                    transitions[predecessors[current]][transition.first] = equivalent;
                }

            predecessors.erase(current);
        }
    }

    dfa_type::symbol_set_type     new_alphabet;
    dfa_type::state_set_type      new_states;
    dfa_type::transition_map_type new_transitions;
    dfa_type::state_set_type      new_final_states;
    dfa_type::state_type          new_initial_state{initial_state};

    dfa_type::map_type<state_name_type, dfa_type::state_type> mapping;

    for (auto symbol : alphabet)
        new_alphabet.insert(symbol);

    new_id = 0;
    for (auto state : states)
    {
        dfa_type::state_type q{"q" + std::to_string(new_id++)};
        new_states.insert(q);
        mapping[state] = q;
    }

    for (auto state: states)
        for (auto transition : transitions[state])
        {
            auto s = mapping[state];
            auto alfa = transition.first;
            auto t = mapping[transition.second];
            new_transitions[mapping[state]][transition.first] = mapping[transition.second];
        }

    for (auto final_state : final_states)
        new_final_states.insert(mapping[final_state]);

    return dfa_type(std::move(new_alphabet),
                    std::move(new_states),
                    std::move(new_transitions),
                    std::move(new_final_states),
                    std::move(new_initial_state));
}

}
}
