#include "DeSimoneTreeComponents.hpp"

namespace formal_device
{
namespace expression
{

void UnitNode::up(const state_name_type& state, composition_type & composition, node_set_type & marked)
{
    scape(state, composition, marked);
}

void UnitNode::down(const state_name_type& state, composition_type & composition, node_set_type & marked)
{
	composition[state][m_symbol].insert(this);
}

void UnitNode::scape(const state_name_type& state, composition_type & composition, node_set_type & marked)
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

void UnionNode::up(const state_name_type& state, composition_type & composition, node_set_type & marked)
{
	m_right->scape(state, composition, marked);
}

void UnionNode::down(const state_name_type& state, composition_type & composition, node_set_type & marked)
{
	marked.insert(this);
	m_left->down(state, composition, marked);
	m_right->down(state, composition, marked);
}

void UnionNode::scape(const state_name_type& state, composition_type & composition, node_set_type & marked)
{
	m_right->up(state, composition, marked);
}

void UnionNode::to_sew(DeSimoneNode* target)
{
    m_left->to_sew(this);
    m_right->to_sew(target);
}


// -----------------------------------------------------------------------------------------------------
ConcatenationNode::~ConcatenationNode()
{
	delete m_left;
	delete m_right;
}

void ConcatenationNode::up(const state_name_type& state, composition_type & composition, node_set_type & marked)
{
	m_right->down(state, composition, marked);
}

void ConcatenationNode::down(const state_name_type& state, composition_type & composition, node_set_type & marked)
{
	m_left->down(state, composition, marked);
}

void ConcatenationNode::scape(const state_name_type& state, composition_type & composition, node_set_type & marked)
{
	m_right->up(state, composition, marked);
}

void ConcatenationNode::to_sew(DeSimoneNode* target)
{
    m_left->to_sew(this);
    m_right->to_sew(target);
}

// -----------------------------------------------------------------------------------------------------

ReflexiveNode::~ReflexiveNode()
{
	delete m_left;
}

void ReflexiveNode::up(const state_name_type& state, composition_type & composition, node_set_type & marked)
{
	if (marked.find(this) == marked.end())
		down(state, composition, marked);
	else
		if (m_seam)
			m_seam->up(state, composition, marked);
		else
			composition[state]["&"].insert(nullptr);

}

void ReflexiveNode::down(const state_name_type& state, composition_type & composition, node_set_type & marked)
{
	marked.insert(this);
	m_left->down(state, composition, marked);

	if (m_seam)
		m_seam->up(state, composition, marked);
	else
		composition[state]["&"].insert(nullptr);
}

void ReflexiveNode::scape(const state_name_type& state, composition_type & composition, node_set_type & marked)
{
	if (m_seam)
		m_seam->up(state, composition, marked);
	else
		composition[state]["&"].insert(nullptr);
}

void ReflexiveNode::to_sew(DeSimoneNode* target)
{
    m_left->to_sew(this);
	m_seam = target;
}

// -----------------------------------------------------------------------------------------------------

OptionalNode::~OptionalNode()
{
	delete m_left;
}

void OptionalNode::up(const state_name_type& state, composition_type & composition, node_set_type & marked)
{
	if (m_seam)
		m_seam->up(state, composition, marked);
	else
		composition[state]["&"].insert(nullptr);
}

void OptionalNode::down(const state_name_type& state, composition_type & composition, node_set_type & marked)
{
	marked.insert(this);
	m_left->down(state, composition, marked);
	if (m_seam)
        m_seam->up(state, composition, marked);
	else
		composition[state]["&"].insert(nullptr);
}

void OptionalNode::scape(const state_name_type& state, composition_type & composition, node_set_type & marked)
{
	if (m_seam)
		m_seam->up(state, composition, marked);
	else
		composition[state]["&"].insert(nullptr);
}

void OptionalNode::to_sew(DeSimoneNode* target)
{
    m_left->to_sew(this);
	m_seam = target;
}

// -----------------------------------------------------------------------------------------------------

}   // namespace expression
}   // namespace formal_device
