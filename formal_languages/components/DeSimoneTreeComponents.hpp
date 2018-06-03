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

    //! Default Destructor DeSimoneNode
    /*!
        \brief For the implementation of a pure interface.
    */
    virtual ~DeSimoneNode() = default;

    //! Empty check
    /*!
        \brief Verifies that it is the expression that represents the empty.
        \return True if is a empty node.
    */
    virtual bool is_empty() = 0;

    //! Up operation
    /*!
        \brief When you climb a node, it implements new actions.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    virtual void up(const state_name_type& state, composition_type & composition, node_set_type & marked) = 0;

    //! Down operation
    /*!
        \brief When you go down a knot, they make certain decisions.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    virtual void down(const state_name_type& state, composition_type & composition, node_set_type & marked) = 0;

    //! Scape operation
    /*!
        \brief Escapes if it is union or concatenation, otherwise it goes up.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    virtual void scape(const state_name_type& state, composition_type & composition, node_set_type & marked) = 0;

    //! Sew operation
    /*!
        \brief Defines who your Constura is if it is not a union or concatenation.
        \param target Node that will be the seam of another node.
    */
    virtual void to_sew(DeSimoneNode* target) = 0;
};

struct UnitNode : public DeSimoneNode
{
    //! Default Construct UnitNode
    /*!
        \brief Build a UnitNode with symbol & and seamless.
    */
	UnitNode() = default;

    //! Default Destructor UnitNode
    /*!
        \brief It simply destroys its attributes.
    */
	~UnitNode() = default;

    //! Empty check
    /*!
        \brief Verifies that it is the expression that represents the empty.
        \return True if is a empty node.
    */
    bool is_empty();

    //! Up operation
    /*!
        \brief It does nothing because we will never climb 1 1 unit node.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    void up(const state_name_type& state, composition_type & composition, node_set_type & marked);

    //! Down operation
    /*!
        \brief Adds the node and the symbol in the composition of the States and up on seam.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    void down(const state_name_type& state, composition_type & composition, node_set_type & marked);

    //! Scape operation
    /*!
        \brief It goes up.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    void scape(const state_name_type& state, composition_type & composition, node_set_type & marked);

    //! Sew operation
    /*!
        \brief Defines the seam being the target.
        \param target New seam.
    */
    void to_sew(DeSimoneNode* target);

    symbol_name_type m_symbol{"&"}; //! Symbol value
    DeSimoneNode* m_seam{nullptr};  //! Seam pointer
};

struct UnionNode : public DeSimoneNode
{
    //! Default Construct UnionNode
    /*!
        \brief Build a UnionNode with nullptr children.
    */
	UnionNode() = default;

    //! Default Destructor UnioNode
    /*!
        \brief Destroys your children.
    */
	~UnionNode();

    //! Empty check
    /*!
        \brief Verifies that it is the expression that represents the empty.
        \return True if is a empty node.
    */
    bool is_empty();

    //! Up operation
    /*!
        \brief Escapes through the son on the right until it finally goes up.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    void up(const state_name_type& state, composition_type & composition, node_set_type & marked);

    //! Down operation
    /*!
        \brief It marks and descends on the son of the left and the son on the right.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    void down(const state_name_type& state, composition_type & composition, node_set_type & marked);

    //! Scape operation
    /*!
        \brief Escapes by the son on the right.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    void scape(const state_name_type& state, composition_type & composition, node_set_type & marked);

    //! Sew operation
    /*!
        \brief It sends itself as sewing to the son of the left and sends the target to be sewing of the son of the right.
        \param target New seam.
    */
    void to_sew(DeSimoneNode* target);

	DeSimoneNode* m_left {nullptr}; //! Node pointer
    DeSimoneNode* m_right{nullptr}; //! Node pointer
};

struct ConcatenationNode : public DeSimoneNode
{
    //! Default Construct ConcatenationNode
    /*!
        \brief Build a ConcatenationNode with nullptr children.
    */
	ConcatenationNode() = default;

    //! Default Destructor ConcatenationNode
    /*!
        \brief Destroys your children.
    */
	~ConcatenationNode();

    //! Empty check
    /*!
        \brief Verifies that it is the expression that represents the empty.
        \return True if is a empty node.
    */
    bool is_empty();

    //! Up operation
    /*!
        \brief Get down on the son on the right.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    void up(const state_name_type& state, composition_type & composition, node_set_type & marked);

    //! Down operation
    /*!
        \brief It marks and descends only on the son on the left.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    void down(const state_name_type& state, composition_type & composition, node_set_type & marked);

    //! Scape operation
    /*!
        \brief Escapes by the son on the right.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    void scape(const state_name_type& state, composition_type & composition, node_set_type & marked);

    //! Sew operation
    /*!
        \brief It sends itself as sewing to the son of the left and sends the target to be sewing of the son of the right.
        \param target New seam.
    */
    void to_sew(DeSimoneNode* target);

	DeSimoneNode* m_left {nullptr}; //! Node pointer
    DeSimoneNode* m_right{nullptr}; //! Node pointer
};

struct ReflexiveNode : public DeSimoneNode
{
    //! Default Construct ReflexiveNode
    /*!
        \brief Build a ReflexiveNode with nullptr child and seamless.
    */
	ReflexiveNode() = default;

    //! Default Destructor ReflexiveNode
    /*!
        \brief Destroys your child.
    */
	~ReflexiveNode();

    //! Empty check
    /*!
        \brief Verifies that it is the expression that represents the empty.
        \return True if is a empty node.
    */
    bool is_empty();

    //! Up operation
    /*!
        \brief You go down on the kid if it's not marked and then you go upstairs.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    void up(const state_name_type& state, composition_type & composition, node_set_type & marked);

    //! Down operation
    /*!
        \brief It marks and descends on the son.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    void down(const state_name_type& state, composition_type & composition, node_set_type & marked);

    //! Scape operation
    /*!
        \brief It goes up.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    void scape(const state_name_type& state, composition_type & composition, node_set_type & marked);

    //! Sew operation
    /*!
        \brief It sends itself to be the sewing of the son of the left and defines the target as its seam.
        \param target New seam.
    */
    void to_sew(DeSimoneNode* target);

	DeSimoneNode* m_left {nullptr}; //! Node pointer
    DeSimoneNode* m_seam {nullptr}; //! Seam pointer
};

struct OptionalNode : public DeSimoneNode
{
    //! Default Construct OptionalNode
    /*!
        \brief Build a ReflexiveNode with nullptr child and seamless.
    */
	OptionalNode() = default;

    //! Default Destructor OptionalNode
    /*!
        \brief Destroys your child.
    */
	~OptionalNode();

    //! Empty check
    /*!
        \brief Verifies that it is the expression that represents the empty.
        \return True if is a empty node.
    */
    bool is_empty();

    //! Up operation
    /*!
        \brief It just goes up in the seam.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    void up(const state_name_type& state, composition_type & composition, node_set_type & marked);

    //! Down operation
    /*!
        \brief It marks and descends on the son.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    void down(const state_name_type& state, composition_type & composition, node_set_type & marked);

    //! Scape operation
    /*!
        \brief It goes up.
        \param state Target State of the creation of the composition.
        \param composition Set of composition of the states.
        \param marked Set of nodes already visited.
    */
    void scape(const state_name_type& state, composition_type & composition, node_set_type & marked);

    //! Sew operation
    /*!
        \brief It sends itself to be the sewing of the son of the left and defines the target as its seam.
        \param target New seam.
    */
    void to_sew(DeSimoneNode* target);

	DeSimoneNode* m_left {nullptr}; //! Node pointer
    DeSimoneNode* m_seam {nullptr}; //! Seam pointer
};


}   // namespace expression
}   // namespace formal_device

#endif // DEVICES_DESIMONETREECOMPONENTES_HPP
