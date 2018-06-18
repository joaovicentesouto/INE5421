#ifndef STATICGRAMMARWIDGET_HPP
#define STATICGRAMMARWIDGET_HPP

#include <QWidget>
#include <string>

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
    void set_grammar(std::string grammar);

private:
    Ui::StaticGrammarWidget *ui;
};

#endif // STATICGRAMMARWIDGET_HPP
