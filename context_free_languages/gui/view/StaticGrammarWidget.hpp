#ifndef STATICGRAMMARWIDGET_HPP
#define STATICGRAMMARWIDGET_HPP

#include <QWidget>
#include <QListWidgetItem>
#include <string>
#include <map>

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
    void set_grammar(std::string grammar, std::string grammar_name, bool first = true);
    void set_grammar_data(std::string data);

    void on_history_itemClicked(QListWidgetItem *item);

signals:
    void select_grammar(std::string);

private:
    Ui::StaticGrammarWidget *ui;
    std::string m_grammar_name;
    std::string m_result_grammar_name;
    std::map<std::string, std::string> m_result_to_original_name;
    std::map<std::string, std::string> m_name_to_grammar;
    std::map<std::string, std::string> m_name_to_data;
};

#endif // STATICGRAMMARWIDGET_HPP
