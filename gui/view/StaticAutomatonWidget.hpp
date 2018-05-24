#ifndef STATICAUTOMATONWIDGET_HPP
#define STATICAUTOMATONWIDGET_HPP

#include <QWidget>

namespace Ui {
class StaticAutomatonWidget;
}

class StaticAutomatonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StaticAutomatonWidget(QWidget *parent = 0);
    ~StaticAutomatonWidget();

private:
    Ui::StaticAutomatonWidget *ui;
};

#endif // STATICAUTOMATONWIDGET_HPP
