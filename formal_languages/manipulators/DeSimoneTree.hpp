#ifndef DESIMONETREE_H
#define DESIMONETREE_H

#include <formal_languages/components/DeSimoneTreeComponents.hpp>
#include <formal_languages/devices/RegularExpression.hpp>
#include <formal_languages/devices/FiniteAutomaton.hpp>

namespace formal_device
{
namespace expression
{

class DeSimoneTree
{
public:
	using dfa_type = finite_automaton::Deterministic;

    DeSimoneTree(RegularPointer exp);
    ~DeSimoneTree();

	dfa_type execute();
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

#endif // DESIMONETREE_H
