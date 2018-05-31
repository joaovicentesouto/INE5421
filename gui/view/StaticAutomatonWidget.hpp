#ifndef STATICAUTOMATONWIDGET_HPP
#define STATICAUTOMATONWIDGET_HPP

#include <QWidget>
#include <QListWidget>

#include <control/Facade.hpp>
#include <control/Filler.hpp>
#include <view/GrammarViewer.hpp>

#include <formal_languages/manipulators/DevicesConverter.hpp>

namespace Ui {
class StaticAutomatonWidget;
}

class StaticAutomatonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StaticAutomatonWidget(QWidget *parent = 0);
    ~StaticAutomatonWidget();

    void set_facade(Facade * facade);

public slots:
    void update_result(Facade::automaton_ptr_container_type& result);
    void clean_up();

private slots:
    void on_m_history_itemClicked(QListWidgetItem *item);

    void on_m_grammar_clicked();

    void on_m_to_m1_clicked();

    void on_m_to_m2_clicked();

signals:
    void new_automaton(unsigned machine, dfa_type automaton);
    void new_automaton(unsigned machine, ndfa_type automaton);

private:
    Ui::StaticAutomatonWidget *ui;

    Facade * m_facade;
    Facade::automaton_type_ptr m_current;
    unsigned                   m_current_item;
};

#endif // STATICAUTOMATONWIDGET_HPP
