#ifndef NEWEXPRESSIONDIALOG_HPP
#define NEWEXPRESSIONDIALOG_HPP

#include <QDialog>
#include <formal_languages/devices/RegularExpression.hpp>
#include <formal_languages/parsers/ExpressionParser.hpp>

namespace Ui {
class NewExpressionDialog;
}

class NewExpressionDialog : public QDialog
{
    Q_OBJECT

public:
    using expression_type_ptr = formal_device::expression::regular_ptr;

    explicit NewExpressionDialog(QWidget *parent = 0);
    ~NewExpressionDialog();

signals:
    void new_expression(expression_type_ptr expression);

private slots:
    void on_m_ok_btn_clicked();

    void on_m_cancel_btn_clicked();

private:
    Ui::NewExpressionDialog *ui;
};

#endif // NEWEXPRESSIONDIALOG_HPP
