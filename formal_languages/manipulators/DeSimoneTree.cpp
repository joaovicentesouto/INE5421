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
    using dfa_type = finite_automaton::Deterministic;
    return dfa_type();
//    using state_type = dfa_type::state_type;
//	using state_queue_type = std::deque<state_type>;
//    template <class Key, class Value> using map_type            = dfa_type<Key, Value>;

//	using symbol_type = string_type;
//	using node_set_type = std::unordened_set<DeSimoneNode*>;
//	template <class T, class U> using map_type = std::unordened_map<T, U>;

//	state_queue_type to_process;

//	dfa_map_type<state_type, node_set_type> their_make_me;
//	dfa_map_type<state_type, map_type<symbol_type, node_set_type> composição;

//	symbol_set_type alphabet;
//	state_set_type states;
//	state_set_type final_state;
//	transition_map_type transitions;
//	int new_id = 0;

//		// initial state
//	state_type initial_state("q" + std::to_string(i++));
//	states.insert(initial_state);

//	node_set_type visitados;
//	queue_type<Node*> marcados;

//		// cria composicao do estado inicial
//	m_root->down(initial_state, composição, marcados);

//		// constroi estados destinos
//	for (auto map : composição[initial_state])
//		for ... cada mapa
//		{
//			alphabet.insert(map.first);
//			state_type q("q" + std::to_string(i++));
//			states.insert(q);
//			transitions[initial_state][map.first] = q;
//			their_make_me[q] = map.second;

//			to_process.push_back(q);
//		}

//		while (!to_process.empty())
//		{
//			auto current = to_process.deque();

//			auto predecessor = predecessores[current];

//			node_set_type visitados;
//			queue_type<Node*> marcados;

//			for (auto node : their_make_me)
//				node.up(current, composição, marcados, visitados);

//			for (auto state : states)
//			{
//				for (auto symbol : alphabet)
//				{
//					if (composição[current][symbol] ==
//						composição[state][symbol])
//					{
//		// elimina current
//					}
//				}
//			}

//		// constroi estados destinos
//			for (auto map : composição[initial_state])
//				for ... cada mapa
//				{
//					alphabet.insert(map.first);
//					state_type q("q" + std::to_string(i++));
//					states.insert(q);
//					transitions[initial_state][map.first] = q;
//					their_make_me[q] = map.second;

//					to_process.push_back(q);
//				}
//			}


//		// renomei os estados
//		// seta estados finais onde & => nullptr

//			return dfa_type();
}

}
}
