#ifndef NEWEXPRESSIONDIALOG_HPP
#define NEWEXPRESSIONDIALOG_HPP

#include <QDialog>

namespace Ui {
class NewExpressionDialog;
}

class NewExpressionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewExpressionDialog(QWidget *parent = 0);
    ~NewExpressionDialog();

private:
    Ui::NewExpressionDialog *ui;
};

#endif // NEWEXPRESSIONDIALOG_HPP
