#include "ExpressionParser.hpp"

namespace formal_device
{
namespace parser
{

regular_ptr make_regular_expression_from_file(const string_type & file_path)
{
    //std::ifstream t(file_path);
    //string_type exp((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    //exp.erase( std::remove_if(exp.begin(), exp.end(), std::isspace), exp.end());

    return regular_ptr(new epsilon_type());
}

regular_ptr make_regular_expression(string_type exp)
{
    exp = std::regex_replace( exp, std::regex(" "), "" );
    IteratorWrapper begin(exp.begin()), end(exp.end());

    regular_ptr current_exp(new empty_type());

    while (begin.iterator() != end.iterator())
    {
        if (*begin.iterator() == ')')
            throw std::out_of_range("Expressão mal formada");

        if (*begin.iterator() == '|')
        {
            begin.next();
            current_exp = current_exp | union_parser(begin, end);
        }
        else
            current_exp = current_exp + parse(begin, end);
    }

    return current_exp;
}

regular_ptr union_parser(IteratorWrapper &begin, const IteratorWrapper &end)
{
    auto exp = parse(begin, end);

    if (*begin.iterator() == '|')
    {
        begin.next();
        return exp | union_parser(begin, end);
    }

    return exp;
}

regular_ptr parse(IteratorWrapper &begin, const IteratorWrapper &end)
{
    if (begin.iterator() == end.iterator())
        return new empty_type();

    string_type caracter(&(*begin.iterator()), &(*begin.iterator()) + 1);

    if (std::regex_match(caracter, std::regex("[A-Z]")))
        throw std::out_of_range("Expressão mal formada: A-Z");

    if (*begin.iterator() == '(')
    {
        begin.next();
        auto exp = parse(begin, end);

        while (*begin.iterator() == '|')
        {
            begin.next();
            exp = exp | parse(begin, end);
        }

        if (*begin.iterator() != ')')
            throw std::out_of_range("Expressão mal formada: begin != )");

        begin.next();

        switch (*begin.iterator()) {
        case '*':
            exp = exp ^ expression::Operation::Star;
            break;

        case '+':
            exp = exp ^ expression::Operation::Plus;
            break;

        case '?':
            exp = exp ^ expression::Operation::Optional;
            break;

        default:
            break;
        }

        if (*begin.iterator() == ')')
            return exp;

        if (begin.iterator() != end.iterator())
        {
            caracter = string_type(&(*begin.iterator()), &(*begin.iterator()) + 1);

            if (*begin.iterator() != '(')
                if (!std::regex_match(caracter, std::regex("[a-z0-9]")))
                    begin.next();

            return exp + parse(begin, end);
        }

        return exp;
    }
    else if (std::regex_match(caracter, std::regex("[a-z0-9]")))
    {
        regular_ptr exp(new unit_type(*begin.iterator()));

        begin.next();

        if (begin.iterator() == end.iterator() ||
                *begin.iterator() == ')')
            return exp;

        caracter = string_type(&(*begin.iterator()), &(*begin.iterator()) + 1);

        if (std::regex_match(caracter, std::regex("[a-z0-9]"))
                || *begin.iterator() == '(')
            return exp + parse(begin, end);

        switch (*begin.iterator()) {
        case '*':
            exp = exp ^ expression::Operation::Star;
            begin.next();
            break;

        case '+':
            exp = exp ^ expression::Operation::Plus;
            begin.next();
            break;

        case '?':
            exp = exp ^ expression::Operation::Optional;
            begin.next();
            break;

        default:
            break;
        }

        if (*begin.iterator() == '|')
            return exp;
        else
            return exp + parse(begin, end);
    }

    if (*begin.iterator() == '*' || *begin.iterator() == '+')
        throw std::out_of_range("Expressão mal formada: Operandos alinhados");

    if (*begin.iterator() == '&')
    {
        begin.next();
        return new epsilon_type();
    }

    return new empty_type();
}

} // namespace parser
} // namespace formal_device
