#ifndef STATICGRAMMARWIDGET_HPP
#define STATICGRAMMARWIDGET_HPP

#include <QWidget>

namespace Ui {
class StaticGrammarWidget;
}

class StaticGrammarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StaticGrammarWidget(QWidget *parent = 0);
    ~StaticGrammarWidget();

private slots:
    void on_updateButton_clicked();

private:
    Ui::StaticGrammarWidget *ui;
};

#endif // STATICGRAMMARWIDGET_HPP
