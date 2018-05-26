#ifndef GRAMMARVIEWER_HPP
#define GRAMMARVIEWER_HPP

#include <QDialog>
#include <formal_languages/devices/Grammar.hpp>

namespace Ui {
class GrammarViewer;
}

class GrammarViewer : public QDialog
{
    Q_OBJECT

public:
    using grammar_type = formal_device::grammar::Regular;

    explicit GrammarViewer(grammar_type grammar, QWidget *parent = 0);
    ~GrammarViewer();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GrammarViewer *ui;
    grammar_type m_grammar;
};

#endif // GRAMMARVIEWER_HPP
