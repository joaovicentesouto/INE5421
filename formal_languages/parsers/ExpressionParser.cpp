#include "ExpressionParser.hpp"

namespace formal_device
{
namespace parser
{

regular_ptr make_regular_expression(const string_type & file_path)
{
    std::ifstream t(file_path);
    string_type exp((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    //exp.erase( std::remove_if(exp.begin(), exp.end(), std::isspace), exp.end());

    string_iterator_type begin = exp.begin();
    string_iterator_type end   = exp.end();

    regular_ptr current_exp(new empty_type());

    while (begin != end)
        if (*begin == '|')
            current_exp = current_exp | parse(begin, end);
        else
            current_exp = current_exp + parse(begin, end);

    return current_exp;
}

regular_ptr parse(string_iterator_type &begin, const string_iterator_type &end)
{
    if (begin == end)
        return new empty_type();

    string_type caracter(&(*begin), &(*begin) + 1);

    if (*begin == '(')
    {
        auto exp = parse(++begin, end);

        if (*begin != ')')
            throw std::out_of_range("Expressão mal formada");

        switch (*begin) {
        case '*':
            return exp ^ expression::Operation::Star;

        case '+':
            return exp ^ expression::Operation::Plus;

        case '?':
            return exp ^ expression::Operation::Optional;

        default:
            return exp;
        }
    }
    else if (std::regex_match(caracter, std::regex("[a-z0-9]")))
    {
        regular_ptr exp(new unit_type(*begin));

        ++begin;

        if (begin == end)
            return exp;

        caracter = string_type(&(*begin), &(*begin) + 1);

        if (std::regex_match(caracter, std::regex("[a-z0-9]")) || *begin == '(')
            return exp + parse(begin, end);

        switch (*begin) {
        case '*':
            exp = exp ^ expression::Operation::Star;

        case '+':
            exp = exp ^ expression::Operation::Plus;

        case '?':
            exp = exp ^ expression::Operation::Optional;

        default:
            break;
        }

        if (*(++begin) == '|')
            return exp | parse(begin, end);
        else
            return exp + parse(begin, end);
    }

    if (*begin == '*' || *begin == '+' || *begin == '+' || *begin == ')')
        throw std::out_of_range("Expressão mal formada");

    return new empty_type();
}

} // namespace parser
} // namespace formal_device
