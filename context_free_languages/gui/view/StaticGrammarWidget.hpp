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
    void set_grammar(std::string grammar, std::string grammar_name);
    void set_grammar_data(std::string data);

signals:
    void set_dynamic_grammar(std::string);
    void select_grammar(std::string);

private:
    Ui::StaticGrammarWidget *ui;
    std::string m_grammar_name;
};

#endif // STATICGRAMMARWIDGET_HPP
