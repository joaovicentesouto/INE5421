#ifndef NEWGRAMMARDIALOG_HPP
#define NEWGRAMMARDIALOG_HPP

#include <QDialog>
#include <formal_languages/parsers/GrammarParser.hpp>

namespace Ui {
class NewGrammarDialog;
}

class NewGrammarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewGrammarDialog(QWidget *parent = 0);
    ~NewGrammarDialog();

private slots:
    void on_m_ok_btn_clicked();

    void on_m_cancel_btn_clicked();

signals:
    void new_grammar(formal_device::grammar::Regular grammar);

private:
    Ui::NewGrammarDialog *ui;
};

#endif // NEWGRAMMARDIALOG_HPP
