#ifndef AUTOMATONWIDGET_HPP
#define AUTOMATONWIDGET_HPP

#include <QWidget>

namespace Ui {
class AutomatonWidget;
}

class AutomatonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AutomatonWidget(QWidget *parent = 0);
    ~AutomatonWidget();

private:
    Ui::AutomatonWidget *ui;
};

#endif // AUTOMATONWIDGET_HPP
