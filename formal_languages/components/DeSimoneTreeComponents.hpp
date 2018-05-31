#ifndef DEVICES_DESIMONETREECOMPONENTES_HPP
#define DEVICES_DESIMONETREECOMPONENTES_HPP

#include <string>
#include <set>
#include <map>

namespace formal_device
{
namespace expression
{

struct DeSimoneNode
{
    using string_type      = std::string;
    using symbol_name_type = string_type;
    using state_name_type  = string_type;
    using node_set_type    = std::set<DeSimoneNode*>;
    using composition_type = std::map<state_name_type, std::map<symbol_name_type, node_set_type>>;

    virtual ~DeSimoneNode() = default;

    virtual bool is_empty() = 0;

    virtual void up(const state_name_type& state, composition_type & composition, node_set_type & marked) = 0;
    virtual void down(const state_name_type& state, composition_type & composition, node_set_type & marked) = 0;
    virtual void scape(const state_name_type& state, composition_type & composition, node_set_type & marked) = 0;
    virtual void to_sew(DeSimoneNode* target) = 0;
};

struct UnitNode : public DeSimoneNode
{
	UnitNode() = default;
	~UnitNode() = default;

    bool is_empty();

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

    bool is_empty();

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

    bool is_empty();

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

    bool is_empty();

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

    bool is_empty();

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
