#ifndef DYNAMICGRAMMARWIDGET_HPP
#define DYNAMICGRAMMARWIDGET_HPP

#include <QWidget>

namespace Ui {
class DynamicGrammarWidget;
}

class DynamicGrammarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DynamicGrammarWidget(QWidget *parent = 0);
    ~DynamicGrammarWidget();

private:
    Ui::DynamicGrammarWidget *ui;
};

#endif // DYNAMICGRAMMARWIDGET_HPP
