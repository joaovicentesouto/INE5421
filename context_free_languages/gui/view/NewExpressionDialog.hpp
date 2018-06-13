#ifndef NEWEXPRESSIONDIALOG_HPP
#define NEWEXPRESSIONDIALOG_HPP

#include <QDialog>
#include <context_free_languages/model/devices/RegularExpression.hpp>
#include <context_free_languages/model/parsers/ExpressionParser.hpp>

namespace Ui {
class NewExpressionDialog;
}

class NewExpressionDialog : public QDialog
{
    Q_OBJECT

public:
    using expression_type_ptr = formal_device::expression::regular_ptr;

    explicit NewExpressionDialog(unsigned number, QWidget *parent = 0);
    ~NewExpressionDialog();

signals:
    void new_expression(unsigned machine, expression_type_ptr expression);

private slots:
    void on_m_ok_btn_clicked();
    void on_m_cancel_btn_clicked();

private:
    Ui::NewExpressionDialog *ui;
    unsigned m_number;
};

#endif // NEWEXPRESSIONDIALOG_HPP
