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
    using dfa_type = finite_automaton::Deterministic;

    DeSimoneTree(expression::RegularPointer exp);
    ~DeSimoneTree();

	dfa_type execute();

private:
    expression::DeSimoneNode * m_root;
};

}   // namespace manipulator
}   // namespace formal_device

#endif // DESIMONETREE_H
