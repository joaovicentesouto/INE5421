//! João Vicente Souto e Bruno Izaias Bonotto

#include "../catch.hpp"

#include <context_free_languages/model/components/GrammarComponents.hpp>

using namespace formal_device::grammar;

TEST_CASE("Symbols", "[grammar][symbol]")
{
    SymbolPointer a(new TerminalSymbol("a"));
    CHECK(a->is_terminal());
    CHECK(a->value() == "a");
}
