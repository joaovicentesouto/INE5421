#ifndef STATICAUTOMATONWIDGET_HPP
#define STATICAUTOMATONWIDGET_HPP

#include <QWidget>
#include <QListWidget>
#include <control/Facade.hpp>
#include <control/Filler.hpp>

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

private slots:
    void on_m_history_itemClicked(QListWidgetItem *item);

private:
    Ui::StaticAutomatonWidget *ui;

    Facade * m_facade;
    Facade::automaton_type_ptr m_current;
};

#endif // STATICAUTOMATONWIDGET_HPP
