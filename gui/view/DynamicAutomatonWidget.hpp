#ifndef DYNAMICAUTOMATONWIDGET_HPP
#define DYNAMICAUTOMATONWIDGET_HPP

#include <QWidget>

#include <view/NewGrammarDialog.hpp>
#include <view/NewExpressionDialog.hpp>
#include <view/GrammarViewer.hpp>

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
    void new_grammar(QString grammar);
    void new_expression(QString grammar);

private slots:
    void on_m_new_grammar_btn_clicked();

private:
    Ui::DynamicAutomatonWidget *ui;
};

#endif // DYNAMICAUTOMATONWIDGET_HPP
