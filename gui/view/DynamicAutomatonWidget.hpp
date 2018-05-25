#ifndef DYNAMICAUTOMATONWIDGET_HPP
#define DYNAMICAUTOMATONWIDGET_HPP

#include <QWidget>

//#include <formal_languages/devices/RegularExpression.hpp>
//#include <formal_languages/devices/Grammar.hpp>
//#include <formal_languages/devices/RegularExpression.hpp>

#include <view/NewGrammarDialog.hpp>

namespace Ui {
class DynamicAutomatonWidget;
}

class DynamicAutomatonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DynamicAutomatonWidget(QWidget *parent = 0);
    ~DynamicAutomatonWidget();

    void name(QString name);

public slots:
    void new_grammar(formal_device::grammar::Regular grammar);
    void new_expression(QString grammar);

private slots:
    void on_m_new_grammar_btn_clicked();

private:
    Ui::DynamicAutomatonWidget *ui;
};

#endif // DYNAMICAUTOMATONWIDGET_HPP
