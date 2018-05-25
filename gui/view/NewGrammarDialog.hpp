#ifndef NEWGRAMMARDIALOG_HPP
#define NEWGRAMMARDIALOG_HPP

#include <QDialog>
#include <formal_languages/devices/Grammar.hpp>
#include <formal_languages/parsers/GrammarParser.hpp>

namespace Ui {
class NewGrammarDialog;
}

class NewGrammarDialog : public QDialog
{
    Q_OBJECT

public:
    using grammar_type = formal_device::grammar::Regular;

    explicit NewGrammarDialog(QWidget *parent = 0);
    ~NewGrammarDialog();

private slots:
    void on_m_ok_btn_clicked();

    void on_m_cancel_btn_clicked();

signals:
    void new_grammar(grammar_type grammar);

private:
    Ui::NewGrammarDialog *ui;
};

#endif // NEWGRAMMARDIALOG_HPP
