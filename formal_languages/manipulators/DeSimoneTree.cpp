#include "DeSimoneTree.hpp"

namespace formal_device
{
namespace manipulator
{

using namespace expression;

DeSimoneTree::DeSimoneTree(expression_ptr exp)
{
    //! The expression itself builds the tree
    m_root = exp->node_myself();

    //! Sew the tree
    m_root->to_sew(nullptr);
}

DeSimoneTree::~DeSimoneTree()
{
    delete m_root;
}

DeSimoneTree::dfa_type DeSimoneTree::execute()
{
    using symbol_name_type = de_simone_node_type::symbol_name_type;
    using state_name_type  = de_simone_node_type::state_name_type;
    using node_set_type    = de_simone_node_type::node_set_type;
    using composition_type = de_simone_node_type::composition_type;
    using deque_type       = std::deque<state_name_type>;

    //! If root is a empty node, constructs an dfa M | T(M) = Empty language.
    if (m_root->is_empty())
        return dfa_type();

    dfa_type::set_type<symbol_name_type> alphabet;
    dfa_type::set_type<symbol_name_type> states;
    dfa_type::set_type<symbol_name_type> final_states;
    dfa_type::map_type<state_name_type,
                       dfa_type::map_type<symbol_name_type, state_name_type>
                      > transitions;

    deque_type to_process;
    dfa_type::map_type<state_name_type, node_set_type> they_made_me;
    dfa_type::map_type<state_name_type, state_name_type> predecessors;
    composition_type compositions;

    int new_id = 0;

    //! Initial state
    state_name_type initial_state("q" + std::to_string(new_id++));
    states.insert(initial_state);

    //! Creates composition of the initial state.
    {
        node_set_type marked;
        m_root->down(initial_state, compositions, marked);

        //! Creates new states from the composition of the initial state.
        for (auto composition : compositions[initial_state])
        {
            symbol_name_type symbol = composition.first;

            //! & Represents final State (Lambda on algorithm)
            if (symbol == "&")
            {
                final_states.insert(initial_state);
                continue;
            }

            state_name_type q("q" + std::to_string(new_id++));

            alphabet.insert(symbol);
            states.insert(q);
            transitions[initial_state][symbol] = q;
            
            predecessors[q] = initial_state;
            they_made_me[q] = composition.second;   //! Pointer to tree node.

            //! New state to be processed.
            to_process.push_back(q);
        }
    }

    //! Build all States, unless there is already an equivalent state.
    while (!to_process.empty())
    {
        auto current_state = to_process.front();
        to_process.pop_front();

        node_set_type marked;

        //! It rises from all the nodes that built them, that is, same symbol.
        for (auto node : they_made_me[current_state])
            node->up(current_state, compositions, marked);

        state_name_type equivalent = current_state;

        //! Seeks equivalent state.
        for (auto composition_state : compositions)
        {
            auto state = composition_state.first;

            if (current_state == state)
                continue;

            if (compositions[current_state] == compositions[state])
            {
                equivalent = state;
                break;
            }
        }

        if (equivalent == current_state)
        {
            //! There is no equivalent.
            for (auto composition : compositions[current_state])
            {
                symbol_name_type symbol = composition.first;

                if (symbol == "&")
                {
                    final_states.insert(current_state);
                    continue;
                }

                state_name_type q("q" + std::to_string(new_id++));

                alphabet.insert(symbol);
                states.insert(q);
                transitions[current_state][symbol] = q;

                predecessors[q] = current_state;
                they_made_me[q] = composition.second;   //! Pointer to tree node.

                //! New state to be processed.
                to_process.push_back(q);
            }
        }
        else
        {
            //! There is equivalent then I must replace this guy.
            states.erase(current_state);
            they_made_me.erase(current_state);
            compositions.erase(current_state);

            //! Replaces transitions from the current state to the equivalent state.
            for (auto transition : transitions[predecessors[current_state]])
                if (transition.second == current_state) {
                    transition.second = equivalent;
                    transitions[predecessors[current_state]][transition.first] = equivalent;
                }

            predecessors.erase(current_state);
        }
    }

    //! After the algorithm has been completed, the automaton is built.

    dfa_type::symbol_set_type     new_alphabet;
    dfa_type::state_set_type      new_states;
    dfa_type::transition_map_type new_transitions;
    dfa_type::state_set_type      new_final_states;
    dfa_type::state_type          new_initial_state{initial_state};

    dfa_type::map_type<state_name_type, dfa_type::state_type> mapping;

    //! Creates the new alphabet
    for (auto symbol : alphabet)
        new_alphabet.insert(symbol);

    //! Maps the old names of the States to the corresponding States.
    new_id = 0;
    for (auto state : states)
    {
        dfa_type::state_type q{"q" + std::to_string(new_id++)};
        new_states.insert(q);
        mapping[state] = q;
    }

    //! Creates the new transitions
    for (auto state: states)
        for (auto transition : transitions[state])
            new_transitions[mapping[state]][transition.first] = mapping[transition.second];

    //! Creates the new final states
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
