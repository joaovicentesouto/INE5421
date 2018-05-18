#include "RegularExpression.hpp"

namespace formal_device
{
namespace expression
{

void UnitNode::up(const state_type& state, composition_type & composition, state_set_type & marked)
{

}

void UnitNode::down(const state_type& state, composition_type & composition, state_set_type & marked)
{
	composition[state][m_symbol].insert(this);
}

void UnitNode::scape(const state_type& state, composition_type & composition, state_set_type & marked)
{
	if (m_seam)
		m_seam->up(state, composition, marked);
	else
		composition[state]["&"].insert(nullptr);
}

void UnitNode::to_sew(DeSimoneNode* target)
{
	m_seam = target;
}

// -----------------------------------------------------------------------------------------------------

UnionNode::~UnionNode()
{
	delete m_left;
	delete m_right;
}

void UnionNode::up(const state_type& state, composition_type & composition, state_set_type & marked)
{
	m_right->scape(state, composition, marked);
}

void UnionNode::down(const state_type& state, composition_type & composition, state_set_type & marked)
{
	marked.insert(this);
	m_left->down(state, composition, marked);
	m_right->down(state, composition, marked);
}

void UnionNode::scape(const state_type& state, composition_type & composition, state_set_type & marked)
{
	m_right->up(state, composition, marked);
}

void UnionNode::to_sew(DeSimoneNode* target)
{
	m_left.to_sew(this);
	m_right.to_sew(target);
}


// -----------------------------------------------------------------------------------------------------
ConcatenationNode::~ConcatenationNode()
{
	delete m_left;
	delete m_right;
}

void ConcatenationNode::up(const state_type& state, composition_type & composition, state_set_type & marked)
{
	m_right->down(state, composition, marked);
}

void ConcatenationNode::down(const state_type& state, composition_type & composition, state_set_type & marked)
{
	m_left->down(state, composition, marked);
}

void ConcatenationNode::scape(const state_type& state, composition_type & composition, state_set_type & marked)
{
	m_right->up(state, composition, marked);
}

void ConcatenationNode::to_sew(DeSimoneNode* target)
{
	m_left.to_sew(this);
	m_right.to_sew(target);
}

// -----------------------------------------------------------------------------------------------------

ReflexiveNode::~ReflexiveNode()
{
	delete m_left;
}

void ReflexiveNode::up(const state_type& state, composition_type & composition, state_set_type & marked)
{
	if (marked.find(this) == marked.end())
		down(state, composition, marked);
	else
		if (m_seam)
			m_seam->up(state, composition, marked);
		else
			composition[state]["&"].insert(nullptr);

}

void ReflexiveNode::down(const state_type& state, composition_type & composition, state_set_type & marked)
{
	marked.insert(this);
	m_left->down(state, composition, marked);

	if (m_seam)
		m_seam->up(state, composition, marked);
	else
		composition[state]["&"].insert(nullptr);
}

void ReflexiveNode::scape(const state_type& state, composition_type & composition, state_set_type & marked)
{
	if (m_seam)
		m_seam->up(state, composition, marked);
	else
		composition[state]["&"].insert(nullptr);
}

void ReflexiveNode::to_sew(DeSimoneNode* target)
{
	m_left.to_sew(this);
	m_seam = target;
}

// -----------------------------------------------------------------------------------------------------

OptionalNode::~OptionalNode()
{
	delete m_left;
}

void OptionalNode::up(const state_type& state, composition_type & composition, state_set_type & marked)
{
	if (m_seam)
		m_seam->up(state, composition, marked);
	else
		composition[state]["&"].insert(nullptr);
}

void OptionalNode::down(const state_type& state, composition_type & composition, state_set_type & marked)
{
	marked.insert(this);
	m_left->down(state, composition, marked);
	if (m_seam)
		m_seam->down(state, composition, marked);
	else
		composition[state]["&"].insert(nullptr);
}

void OptionalNode::scape(const state_type& state, composition_type & composition, state_set_type & marked)
{
	if (m_seam)
		m_seam->up(state, composition, marked);
	else
		composition[state]["&"].insert(nullptr);
}

void OptionalNode::to_sew(DeSimoneNode* target)
{
	m_left.to_sew(this);
	m_seam = target;
}

// -----------------------------------------------------------------------------------------------------

DeSimoneTree::DeSimoneTree(RegularPointer exp)
{
	m_root = exp.node_myself();
	m_root.to_sew(nullptr);
}

DeSimoneTree::~DeSimoneTree()
{
	delete m_root;
}

DeSimoneTree::dfa_type DeSimoneTree::execute()
{
	using state_type = string_type; // dfa_type::state_type;
	using state_queue_type = std::deque<state_type>;
	template <class T, class U> using dfa_map_type = dfa_type::map_type<T, U>;

	using symbol_type = string_type;
	using node_set_type = std::unordened_set<DeSimoneNode*>;
	template <class T, class U> using map_type = std::unordened_map<T, U>;

	state_queue_type to_process;

	dfa_map_type<state_type, node_set_type> their_make_me;
	dfa_map_type<state_type, map_type<symbol_type, node_set_type> composição;

	symbol_set_type alphabet;
	state_set_type states;
	state_set_type final_state;
	transition_map_type transitions;
	int new_id = 0;

		// initial state
	state_type initial_state("q" + std::to_string(i++));
	states.insert(initial_state);

	node_set_type visitados;
	queue_type<Node*> marcados;

		// cria composicao do estado inicial
	m_root->down(initial_state, composição, marcados);

		// constroi estados destinos
	for (auto map : composição[initial_state])
		for ... cada mapa
		{
			alphabet.insert(map.first);
			state_type q("q" + std::to_string(i++));
			states.insert(q);
			transitions[initial_state][map.first] = q;
			their_make_me[q] = map.second;

			to_process.push_back(q);
		}

		while (!to_process.empty())
		{
			auto current = to_process.deque();

			auto predecessor = predecessores[current];

			node_set_type visitados;
			queue_type<Node*> marcados;

			for (auto node : their_make_me)
				node.up(current, composição, marcados, visitados);

			for (auto state : states)
			{
				for (auto symbol : alphabet)
				{
					if (composição[current][symbol] ==
						composição[state][symbol])
					{
		// elimina current
					}
				}
			}

		// constroi estados destinos
			for (auto map : composição[initial_state])
				for ... cada mapa
				{
					alphabet.insert(map.first);
					state_type q("q" + std::to_string(i++));
					states.insert(q);
					transitions[initial_state][map.first] = q;
					their_make_me[q] = map.second;

					to_process.push_back(q);
				}
			}


		// renomei os estados
		// seta estados finais onde & => nullptr

			return dfa_type();
}

}   // namespace expression
}   // namespace formal_device
