//! João Vicente Souto e Bruno Izaias Bonotto

#ifndef DESIMONETREE_H
#define DESIMONETREE_H

#include <formal_languages/components/DeSimoneTreeComponents.hpp>
#include <formal_languages/devices/RegularExpression.hpp>
#include <formal_languages/devices/FiniteAutomaton.hpp>

namespace formal_device
{
namespace manipulator
{

class DeSimoneTree
{
public:
    using dfa_type            = finite_automaton::Deterministic;
    using expression_ptr      = expression::regular_ptr;
    using de_simone_node_type = expression::DeSimoneNode;

    //! Constructor
    /*!
        \brief Build a DeSimone tree from the expression, where it itself creates the tree, then sews it.
        \param exp Regular expresion pointer.
    */
    DeSimoneTree(expression_ptr exp);

    //! Default Destructor
    /*!
        \brief Destroys root.
    */
    ~DeSimoneTree();

    //! Execute DeSimone Algorithm
    /*!
        \brief It creates states and their compositions, if there are no equivalents, until there are no new states.
        \return Automato deterministic from the tree.
    */
	dfa_type execute();

private:
    de_simone_node_type * m_root; //! Tree's root.
};

}   // namespace manipulator
}   // namespace formal_device

#endif // DESIMONETREE_H
