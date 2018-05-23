#include "../catch.hpp"

#include <formal_languages/manipulators/Printer.hpp>
#include <sstream>

using namespace formal_device;

TEST_CASE("Printer: FA Deterministic", "[printer][finite_automaton]")
{
    finite_automaton::Deterministic det;
    finite_automaton::NonDeterministic non_det;
    grammar::Regular reg_grammar;

    std::cout << "FROM cout: " << det << ", " << non_det << ", " << reg_grammar << std::endl;

    std::stringstream ss;

    ss << det;
    std::cout << "FROM stringstream: " << ss.str() << std::endl;

    CHECK(true);
}
