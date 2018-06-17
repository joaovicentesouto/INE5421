#include "Facade.hpp"

Facade::Facade()
{
}

Facade::~Facade()
{
}

void Facade::grammar_changed()
{
    validated = false;
}

void Facade::new_grammar(std::string grammar_text)
{
    try {
        m_grammar = formal_device::parser::grammar_parser(grammar_text);
        validated = true;
        emit grammar_construction(true);
    } catch (const std::exception& e) {
        validated = false;
        emit grammar_construction(false);
    }
}

void Facade::factored()
{
    if (!validated) {
        emit not_validated();
        return;
    }
    emit factored_result(m_grammar.is_factored());
}

void Facade::emptiness()
{
    if (!validated) {
        emit not_validated();
        return;
    }
    emit emptiness_result(m_grammar.emptiness());
}

void Facade::finiteness()
{
    if (!validated) {
        emit not_validated();
        return;
    }
    emit finiteness_result(m_grammar.finitiness());
}
