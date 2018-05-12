#include "FiniteAutomatonParser.hpp"

namespace formal_device
{
namespace parser
{

auto make_finite_automaton(const std::string &file)
{
    return finite_automaton::Deterministic();
}

} // namespace parser
} // namespace formal_device
