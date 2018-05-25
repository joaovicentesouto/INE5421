
#include "GrammarParser.hpp"

namespace formal_device
{
namespace grammar
{
namespace parser
{

using symbol_type                  = Regular::symbol_type;
using terminal_production_type     = Regular::terminal_production_type;
using non_terminal_production_type = Regular::non_terminal_production_type;
using production_type_ptr          = Regular::production_type_ptr;

using vocabulary_set_type          = Regular::vocabulary_set_type;
using production_map_type          = Regular::production_map_type;
using pair_production_type         = Regular::pair_production_type;

Regular make_regular_grammar_from_file(const string_type &file_path)
{
    std::ifstream grammar_file(file_path);

    if (!grammar_file.is_open())
        throw std::out_of_range("Achar exceção correta -> erro ao abrir arquivo!");

    grammar_file >> std::noskipws;
    boost::spirit::istream_iterator first(grammar_file), last;

    return Regular();
//    return make_regular_grammar();
}

Regular make_regular_grammar(string_type grammar)
{
    auto first(grammar.begin()), last(grammar.end());

    ast::Document doc;
    bool parsed = phrase_parse(first, last, parser::document, parser::ascii::blank, doc);

    if (!parsed)
        throw std::out_of_range("Gramática mal formatado");

    vocabulary_set_type vn;
    vocabulary_set_type vt;
    production_map_type productions;
    symbol_type initial_symbol;
    bool initial = true;

    for (auto line : doc.m_lines)
    {
        symbol_type non_terminal(line.m_symbol.substr(line.m_symbol.size()-1, 1));
        vn.insert(non_terminal);

        for (auto production : line.m_productions)
        {
            production_type_ptr prod;

            if (production.m_production.size() == 1)
            {
                symbol_type symb(symbol_type(production.m_production));
                vt.insert(symb);
                prod = new terminal_production_type(symb);
            }
            else
            {
                symbol_type term(symbol_type(production.m_production.substr(0,1)));
                symbol_type non_term(symbol_type(production.m_production.substr(1,1)));
                vt.insert(term);
                vn.insert(non_term);
                prod = new non_terminal_production_type(term, non_term);
            }

            productions[non_terminal].insert(prod);
        }

        if (initial)
        {
            initial_symbol = non_terminal;
            initial = false;
        }
    }

    return Regular(std::move(vn), std::move(vt), std::move(productions), std::move(initial_symbol));
}

}
} // namespace parser
} // namespace formal_device
