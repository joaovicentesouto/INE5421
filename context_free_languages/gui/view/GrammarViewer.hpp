#ifndef GRAMMARVIEWER_HPP
#define GRAMMARVIEWER_HPP

#include <QDialog>
#include <context_free_languages/model/devices/Grammar.hpp>

namespace Ui {
class GrammarViewer;
}

class GrammarViewer : public QDialog
{
    Q_OBJECT

public:
    using grammar_type = formal_device::grammar::Regular;
    using string_type = grammar_type::string_type;
    using sentences_set = grammar_type::set_type<string_type>;

    explicit GrammarViewer(grammar_type grammar, QWidget *parent = 0);
    explicit GrammarViewer(sentences_set sentences, QWidget *parent = 0);

    ~GrammarViewer();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GrammarViewer *ui;
    grammar_type m_grammar;
};

#endif // GRAMMARVIEWER_HPP
