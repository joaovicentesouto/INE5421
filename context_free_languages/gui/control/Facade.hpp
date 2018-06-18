//! João Vicente Souto e Bruno Izaias Bonotto

#ifndef FACADE_H
#define FACADE_H

#include <QObject>
#include <QString>

#include <context_free_languages/model/parsers/ContextFreeGrammarParser.hpp>

using namespace formal_device::grammar;

class Facade : public QObject
{
    Q_OBJECT

public:
    Facade();
    ~Facade();

public slots:
    void grammar_changed();
    bool new_grammar(std::string grammar_text);

    bool factored();
    bool emptiness();
    bool finiteness();
    bool grammar_validated();

    void make_own();
    void epsilon_free();
    void factoring(uint n);
    void remove_dead_symbols();
    void remove_left_recursion();
    void remove_inutile_symbols();
    void remove_simple_production();
    void remove_unreachable_symbols();

signals:
    void set_static_grammar(std::string grammar);

private:
     ContextFree m_grammar;
     bool validated = false;
};

#endif // FACADE_H
