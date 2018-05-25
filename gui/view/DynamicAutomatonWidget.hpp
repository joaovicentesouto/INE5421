#ifndef DYNAMICAUTOMATONWIDGET_HPP
#define DYNAMICAUTOMATONWIDGET_HPP

#include <QWidget>

//#include <formal_languages/devices/RegularExpression.hpp>
//#include <formal_languages/devices/Grammar.hpp>
//#include <formal_languages/devices/RegularExpression.hpp>

#include <view/NewGrammarDialog.hpp>
#include <view/NewExpressionDialog.hpp>

namespace Ui {
class DynamicAutomatonWidget;
}

class DynamicAutomatonWidget : public QWidget
{
    Q_OBJECT

public:
    using grammar_type        = formal_device::grammar::Regular;
    using expression_type_ptr = formal_device::expression::regular_ptr;

    explicit DynamicAutomatonWidget(QWidget *parent = 0);
    ~DynamicAutomatonWidget();

    void name(QString name);

public slots:
    void new_grammar(grammar_type grammar);
    void new_expression(expression_type_ptr expression);

private slots:
    void on_m_new_grammar_btn_clicked();

    void on_m_new_exp_btn_clicked();

private:
    Ui::DynamicAutomatonWidget *ui;
};

#endif // DYNAMICAUTOMATONWIDGET_HPP
