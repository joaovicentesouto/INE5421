//! João Vicente Souto e Bruno Izaias Bonotto

#ifndef FACADE_H
#define FACADE_H

#include <QObject>
#include <QString>

#include <context_free_languages/model/parsers/ContextFreeGrammarParser.hpp>
#include <context_free_languages/gui/control/Printer.hpp>

using namespace formal_device::grammar;

class Facade : public QObject
{
    Q_OBJECT

public:
    Facade();
    ~Facade();

private slots:
    std::string construct_grammar_data(ContextFree grammar);
    void make_change(ContextFree grammar, std::string result_data, bool first = true);

public slots:
    std::string new_grammar(std::string grammar_text);

    bool factored();
    bool emptiness();
    bool finiteness();
    bool has_recursion();

    void make_own();
    void epsilon_free();
    bool factoring(uint n);
    void remove_dead_symbols();
    void remove_left_recursion();
    void remove_inutile_symbols();
    void remove_simple_production();
    void remove_unreachable_symbols();
    void change_grammar(std::string name);

signals:
    void set_dynamic_grammar(std::string);
    void insert_grammar_name(std::string, bool);
    void update_static_grammar_data(std::string);
    void update_dynamic_grammar_data(std::string);
    void set_static_grammar(std::string, std::string, bool);

private:
     ContextFree m_grammar;
     std::set<ContextFree> grammars_history;
     std::map<std::string, ContextFree> grammar_mapping;
};

#endif // FACADE_H
