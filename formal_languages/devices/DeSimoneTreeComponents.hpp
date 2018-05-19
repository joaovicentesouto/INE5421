#ifndef DEVICES_DESIMONETREECOMPONENTES_HPP
#define DEVICES_DESIMONETREECOMPONENTES_HPP

#include <string>
#include <unordered_set>
#include <unordered_map>

namespace formal_device
{
namespace expression
{

// class State;
// class Hasher;
struct DeSimoneNode;

// using dfa_type = int;
using symbol_name_type = std::string;
using state_name_type = std::string; // usar o state?
using node_set_type = std::unordered_set<DeSimoneNode*>;
using composition_type = std::unordered_map<state_name_type, std::unordered_map<symbol_name_type, node_set_type>>;

struct DeSimoneNode
{
    virtual ~DeSimoneNode() = default;

    virtual void up(const state_name_type& state, composition_type & composition, node_set_type & marked) = 0;
    virtual void down(const state_name_type& state, composition_type & composition, node_set_type & marked) = 0;
    virtual void scape(const state_name_type& state, composition_type & composition, node_set_type & marked) = 0;
	virtual void to_sew(DeSimoneNode* target) = 0;
};

struct UnitNode : public DeSimoneNode
{
	UnitNode() = default;
	~UnitNode() = default;

    void up(const state_name_type& state, composition_type & composition, node_set_type & marked);
    void down(const state_name_type& state, composition_type & composition, node_set_type & marked);
    void scape(const state_name_type& state, composition_type & composition, node_set_type & marked);
	void to_sew(DeSimoneNode* target);

    symbol_name_type m_symbol{"&"};
	DeSimoneNode* m_seam{nullptr};
};

struct UnionNode : public DeSimoneNode
{
	UnionNode() = default;
	~UnionNode();

    void up(const state_name_type& state, composition_type & composition, node_set_type & marked);
    void down(const state_name_type& state, composition_type & composition, node_set_type & marked);
    void scape(const state_name_type& state, composition_type & composition, node_set_type & marked);
	void to_sew(DeSimoneNode* target);

	DeSimoneNode* m_left {nullptr};
	DeSimoneNode* m_right{nullptr};
};

struct ConcatenationNode : public DeSimoneNode
{
	ConcatenationNode() = default;
	~ConcatenationNode();

    void up(const state_name_type& state, composition_type & composition, node_set_type & marked);
    void down(const state_name_type& state, composition_type & composition, node_set_type & marked);
    void scape(const state_name_type& state, composition_type & composition, node_set_type & marked);
	void to_sew(DeSimoneNode* target);

	DeSimoneNode* m_left {nullptr};
	DeSimoneNode* m_right{nullptr};
};

struct ReflexiveNode : public DeSimoneNode
{
	ReflexiveNode() = default;
	~ReflexiveNode();

    void up(const state_name_type& state, composition_type & composition, node_set_type & marked);
    void down(const state_name_type& state, composition_type & composition, node_set_type & marked);
    void scape(const state_name_type& state, composition_type & composition, node_set_type & marked);
	void to_sew(DeSimoneNode* target);

	DeSimoneNode* m_left {nullptr};
	DeSimoneNode* m_seam {nullptr};
};

struct OptionalNode : public DeSimoneNode
{
	OptionalNode() = default;
	~OptionalNode();

    void up(const state_name_type& state, composition_type & composition, node_set_type & marked);
    void down(const state_name_type& state, composition_type & composition, node_set_type & marked);
    void scape(const state_name_type& state, composition_type & composition, node_set_type & marked);
	void to_sew(DeSimoneNode* target);

	DeSimoneNode* m_left {nullptr};
	DeSimoneNode* m_seam {nullptr};
};


}   // namespace expression
}   // namespace formal_device

#endif // DEVICES_DESIMONETREECOMPONENTES_HPP