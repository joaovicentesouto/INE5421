#include "ContextFreeGrammarParser.hpp"

namespace formal_device
{
namespace parser {

grammar_type grammar_parser(string_type grammar)
{
    non_terminal_set_type vn;
    terminal_set_type vt;
    production_map_type p;
    non_terminal_symbol_type s;

    vector_of_string_vector_type productions_line = split(grammar);

    for (auto line: productions_line) {

        production_type production;  // vector
        non_terminal_symbol_type generator;
        int i = 0;

        for (auto sequence: line) {
            switch (i) {

            case 0:
                if (!std::regex_match(sequence, std::regex("[A-Z][0-9]*")))
                    throw std::out_of_range("Simbolo Terminal invalido!");
                generator = non_terminal_symbol_type(sequence);
                vn.insert(generator);
                if (line == productions_line.front())
                    s = generator;
                i++;
                break;

            case 1:
                if (!std::regex_match(sequence, std::regex("->")))
                    throw std::out_of_range("Simbolo Terminal invalido!");
                i++;
                break;

            case 2:
                if (std::regex_match(sequence, std::regex("[A-Z][0-9]*"))) {
                    non_terminal_symbol_type *symbol = new non_terminal_symbol_type(sequence);
                    vn.insert(*symbol);
                    production.push_back(symbol_ptr_type(symbol));
                } else if (std::regex_match(sequence, std::regex("[a-z*0-9+-/()!@#$%&_={}?:;,.]*"))) {
                    terminal_symbol_type *symbol = new terminal_symbol_type(sequence);
                    vt.insert(*symbol);
                    production.push_back(symbol_ptr_type(symbol));
                } else
                    throw std::out_of_range("Simbolo Terminal invalido!");
                i++;
                break;

            case 3:
                if (std::regex_match(sequence, std::regex("[A-Z][0-9]*"))) {
                    non_terminal_symbol_type *symbol = new non_terminal_symbol_type(sequence);
                    vn.insert(*symbol);
                    production.push_back(symbol_ptr_type(symbol));
                } else if (std::regex_match(sequence, std::regex("[a-z*0-9+-/()!@#$%&_={}?:;,.]*"))) {
                    terminal_symbol_type *symbol = new terminal_symbol_type(sequence);
                    vt.insert(*symbol);
                    production.push_back(symbol_ptr_type(symbol));
                } else if (sequence == "|") {
                    p[generator].insert(production);
                    production = production_type();
                } else
                    throw std::out_of_range("Simbolo Terminal invalido!");
                break;

            default:
                throw std::out_of_range("Simbolo Terminal invalido!");
            }
        }
    }

    return grammar_type(vn, vt, p, s);
}

vector_of_string_vector_type split(string_type grammar)
{
    vector_of_string_vector_type productions_line;
    std::stringstream grammar_copy(grammar);
    string_type line;

    while (std::getline(grammar_copy, line)) {
        if (line.length() <= 0)
            continue;

        std::stringstream line_copy(line);
        string_vector_type lines;
        string_type production;

        while (std::getline(line_copy, production, ' ')) {
            if (production.length() <= 0)
                continue;
            lines.push_back(production);
        }
        if (lines.back().compare("|"))
            lines.push_back("|");
        productions_line.push_back(lines);
    }

    return productions_line;
}

}  // namespace parser
}  // namespace formal_device
