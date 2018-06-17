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

private slots:
    void on_cleanButton_clicked();
    void on_validateButton_clicked();

    void grammar_construction(bool contructed);

    void on_emptinessButton_clicked();
    void on_finitenessButton_clicked();
    void on_isFactoredButton_clicked();

    void factored_result(bool);
    void emptiness_result(bool);
    void finiteness_result(bool);

    void on_grammar_textChanged();
    void grammar_not_validated();

signals:
    void factored();
    void emptiness();
    void finiteness();
    void grammar_changed();
    void new_grammar(std::string grammar_text);

private:
    Ui::DynamicGrammarWidget *ui;
};

#endif // DYNAMICGRAMMARWIDGET_HPP
