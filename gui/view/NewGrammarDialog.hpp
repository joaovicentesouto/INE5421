#ifndef NEWGRAMMARDIALOG_HPP
#define NEWGRAMMARDIALOG_HPP

#include <QDialog>

namespace Ui {
class NewGrammarDialog;
}

class NewGrammarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewGrammarDialog(QWidget *parent = 0);
    ~NewGrammarDialog();

private:
    Ui::NewGrammarDialog *ui;
};

#endif // NEWGRAMMARDIALOG_HPP
