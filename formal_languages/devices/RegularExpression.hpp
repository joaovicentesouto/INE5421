#ifndef DEVICES_REGULAREXPRESSION_HPP
#define DEVICES_REGULAREXPRESSION_HPP

#include <unordered_set>

namespace formal_device
{
namespace expression
{

class State;
struct DeSimoneNode;
using dfa_type = int;
using string_type = std::string;
using state_type = State;
using composition_type = int;
using node_set_type = std::unordered_set<DeSimoneNode*>;

struct DeSimoneNode
{
	~DeSimoneNode() = default;

	virtual void up(const state_type& state, composition_type & composition, node_set_type & marked) = 0;
	virtual void down(const state_type& state, composition_type & composition, node_set_type & marked) = 0;
	virtual void scape(const state_type& state, composition_type & composition, node_set_type & marked) = 0;
	virtual void to_sew(DeSimoneNode* target) = 0;
}

struct UnitNode : public DeSimoneNode
{
	UnitNode() = default;
	~UnitNode() = default;

	void up(const state_type& state, composition_type & composition, node_set_type & marked);
	void down(const state_type& state, composition_type & composition, node_set_type & marked);
	void scape(const state_type& state, composition_type & composition, node_set_type & marked);
	void to_sew(DeSimoneNode* target);

	string_type m_symbol{"&"};
	DeSimoneNode* m_seam{nullptr};
};

struct UnionNode : public DeSimoneNode
{
	UnionNode() = default;
	~UnionNode();

	void up(const state_type& state, composition_type & composition, node_set_type & marked);
	void down(const state_type& state, composition_type & composition, node_set_type & marked);
	void scape(const state_type& state, composition_type & composition, node_set_type & marked);
	void to_sew(DeSimoneNode* target);

	DeSimoneNode* m_left {nullptr};
	DeSimoneNode* m_right{nullptr};
};

struct ConcatenationNode : public DeSimoneNode
{
	ConcatenationNode() = default;
	~ConcatenationNode();

	void up(const state_type& state, composition_type & composition, node_set_type & marked);
	void down(const state_type& state, composition_type & composition, node_set_type & marked);
	void scape(const state_type& state, composition_type & composition, node_set_type & marked);
	void to_sew(DeSimoneNode* target);

	DeSimoneNode* m_left {nullptr};
	DeSimoneNode* m_right{nullptr};
};

struct ReflexiveNode : public DeSimoneNode
{
	ReflexiveNode() = default;
	~ReflexiveNode();

	void up(const state_type& state, composition_type & composition, node_set_type & marked);
	void down(const state_type& state, composition_type & composition, node_set_type & marked);
	void scape(const state_type& state, composition_type & composition, node_set_type & marked);
	void to_sew(DeSimoneNode* target);

	DeSimoneNode* m_left {nullptr};
	DeSimoneNode* m_seam {nullptr};
};

struct OptionalNode : public DeSimoneNode
{
	OptionalNode() = default;
	~OptionalNode();

	void up(const state_type& state, composition_type & composition, node_set_type & marked);
	void down(const state_type& state, composition_type & composition, node_set_type & marked);
	void scape(const state_type& state, composition_type & composition, node_set_type & marked);
	void to_sew(DeSimoneNode* target);

	DeSimoneNode* m_left {nullptr};
	DeSimoneNode* m_seam {nullptr};
};


}   // namespace expression
}   // namespace formal_device

#include <formal_languages/devices/RegularExpressionComponents.hpp>

namespace formal_device
{
namespace expression
{

class DeSimoneTree
{
public:
	// using dfa_type;

	DeSimoneTree() = default;
	~DeSimoneTree() = default;

	// dfa_type execute()
	// 	{

	// 	queue_type<state_type> to_process;
	// 	dfa_state_map_type<state_type, set_type<Node*>> their_make_me;

	// 	dfa_map_type<state_type, map_type<symbol_type, set_type<Node*>> composição;

	// 	symbol_set_type alphabet;
	// 	state_set_type states;
	// 	state_set_type final_state;
	// 	transition_map_type transitions;
	// 	int new_id = 0;

	// 	// initial state
	// 	state_type initial_state("q" + std::to_string(i++));
	// 	states.insert(initial_state);

	// 	{
	// 	set_type<Node*> visitados;
	// 	queue_type<Node*> marcados;

	// 	// cria composicao do estado inicial
	// 	m_root->down(initial_state, composição,
	// 	  marcados, visitados);

	// 	// constroi estados destinos
	// 	for (auto map : composição[initial_state])
	// 	for ... cada mapa
	// 	{
	// 	alphabet.insert(map.first);
	// 	state_type q("q" + std::to_string(i++));
	// 	states.insert(q);
	// 	transitions[initial_state][map.first] = q;
	// 	their_make_me[q] = map.second;

	// 	to_process.push_back(q);
	// 	}

	// 	while (!to_process.empty())
	// 	{
	// 	auto current = to_process.deque();

	// 	auto predecessor = predecessores[current];

	// 	set_type<Node*> visitados;
	// 	queue_type<Node*> marcados;

	// 	for (auto node : their_make_me)
	// 	node.up(current, composição, marcados, visitados);

	// 	for (auto state : states)
	// 	{
	// 	for (auto symbol : alphabet)
	// 	{
	// 	if (composição[current][symbol] ==
	// 	composição[state][symbol])
	// 	{
	// 	// elimina current
	// 	}
	// 	}
	// 	}

	// 	// constroi estados destinos
	// 	for (auto map : composição[initial_state])
	// 	for ... cada mapa
	// 	{
	// 	alphabet.insert(map.first);
	// 	state_type q("q" + std::to_string(i++));
	// 	states.insert(q);
	// 	transitions[initial_state][map.first] = q;
	// 	their_make_me[q] = map.second;

	// 	to_process.push_back(q);
	// 	}
	// 	}
	// 	}

	// 	// renomei os estados
	// 	// seta estados finais onde & => nullptr

	// 	return dfa_type();
	//  }

private:
	DeSimoneNode * m_root;
};

}   // namespace expression
}   // namespace formal_device

#endif // DEVICES_REGULAREXPRESSION_HPP
