#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <control/Facade.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Facade * m_facade;
};

#endif // MAINWINDOW_H
