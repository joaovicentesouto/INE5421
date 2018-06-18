#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <control/Facade.hpp>
#include <view/NumberDialog.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ownButton_clicked();
    void on_factoringButton_clicked();
    void on_deadSymbolsButton_clicked();
    void on_epsilonFreeButton_clicked();
    void on_leftRecursionButton_clicked();
    void on_inutileSymbolsButton_clicked();
    void on_simpleProductionButton_clicked();
    void on_unreachableSymbolsButton_clicked();

signals:
    void make_own();
    void epsilon_free();
    void remove_dead_symbols();
    void remove_left_recursion();
    void remove_inutile_symbols();
    void remove_simple_production();
    void remove_unreachable_Symbols();
    void new_grammar(std::string grammar_text);

private:
    Ui::MainWindow *ui;
    Facade * m_facade;
};

#endif // MAINWINDOW_H
