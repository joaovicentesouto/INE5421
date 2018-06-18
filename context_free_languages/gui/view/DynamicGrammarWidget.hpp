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

    void grammar_not_validated();

private slots:
    void on_grammar_textChanged();
    void on_cleanButton_clicked();
    void on_validateButton_clicked();
    void on_emptinessButton_clicked();
    void on_finitenessButton_clicked();
    void on_isFactoredButton_clicked();

public slots:
    void set_msg_text(QString text);

signals:
    bool factored();
    bool emptiness();
    bool finiteness();
    void grammar_changed();
    bool validated_grammar();
    bool new_grammar(std::string grammar_text);

private:
    Ui::DynamicGrammarWidget *ui;
};

#endif // DYNAMICGRAMMARWIDGET_HPP
