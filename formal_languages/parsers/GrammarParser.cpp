
#include "GrammarParser.hpp"

namespace formal_device
{
namespace parser
{

grammar::Regular make_regular_grammar_from_file(const string_type &file_path)
{
    std::ifstream grammar_file(file_path);

    if (!grammar_file.is_open())
        throw std::out_of_range("Achar exceção correta -> erro ao abrir arquivo!");

    grammar_file >> std::noskipws;
    //boost::spirit::istream_iterator first(grammar_file), last;

    return grammar::Regular();
    //    return make_regular_grammar();
}

grammar::Regular make_regular_grammar(string_type grammar)
{
    grammar = std::regex_replace( grammar, std::regex(" "), "" );
    IteratorWrapper first(grammar.begin()), last(grammar.end());

    vocabulary_set_type vn;
    vocabulary_set_type vt;
    production_map_type productions;
    symbol_type initial_symbol;

    new_non_terminal(first, last, vn, vt, productions, initial_symbol);

    return grammar::Regular(vn, vt, productions, initial_symbol);
}

void new_non_terminal(IteratorWrapper &begin, IteratorWrapper &end,
                      vocabulary_set_type &vn, vocabulary_set_type &vt,
                      production_map_type &productions, symbol_type &initial)
{
    bool is_initial = initial == symbol_type();

    string_type character(&(*begin.iterator()), &(*begin.iterator()) + 1);

    symbol_type current;
    if (std::regex_match(character, std::regex("[A-Z]")))
        current = symbol_type(character);
    else
        throw std::out_of_range("Simbolo não terminal invalido");

    vn.insert(current);
    if (is_initial)
        initial = current;

    begin.next();

    if (begin.iterator() != end.iterator())
    {
        if (*begin.iterator() != '-')
            throw std::out_of_range("Simbolo não terminal invalido");

        begin.next();
        if (*begin.iterator() != '>')
            throw std::out_of_range("Simbolo não terminal invalido");

        begin.next();

        new_productions(current, begin, end, vn, vt, productions, is_initial);

        if (*begin.iterator())
            new_non_terminal(begin, end, vn, vt, productions, initial);
    }
}

void new_productions(symbol_type current, IteratorWrapper &begin, IteratorWrapper &end,
                     vocabulary_set_type &vn, vocabulary_set_type &vt,
                     production_map_type &productions, bool is_initial)
{
    while (*begin.iterator() != '\n')
    {
        string_type character(&(*begin.iterator()), &(*begin.iterator()) + 1);

        if (std::regex_match(character, std::regex(is_initial? "[&a-z0-9]" : "[a-z0-9]")))
        {
            symbol_type terminal(character);
            vt.insert(terminal);

            begin.next();
            character = string_type(&(*begin.iterator()), &(*begin.iterator()) + 1);

            if (std::regex_match(character, std::regex("[A-Z]")))
            {
                symbol_type non_terminal(character);
                vn.insert(non_terminal);
                productions[current].insert(new grammar::NonTerminalProduction(terminal, non_terminal));

                begin.next();
            }
            else
            {
                productions[current].insert(new grammar::TerminalProduction(terminal));
            }
        }

        if (*begin.iterator() == '\n' || *begin.iterator() == *end.iterator())
            break;

        if (*begin.iterator() != '|')
            throw std::out_of_range("Produção não regular");

        begin.next();
    }

    if (*begin.iterator() != *end.iterator())
        begin.next();
}

} // namespace parser
} // namespace formal_device
