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
    void new_grammar(std::string grammar_text);

    void factored();
    void emptiness();
    void finiteness();

signals:
    void grammar_construction(bool);
    void factored_result(bool);
    void emptiness_result(bool);
    void finiteness_result(bool);
    void not_validated();

private:
     ContextFree m_grammar;
     bool validated = false;
};

#endif // FACADE_H
