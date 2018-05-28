#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <control/Facade.hpp>
#include <view/BooleanDialog.hpp>

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
    void on_m_or_btn_clicked();

    void on_m_concat_btn_clicked();

    void on_m_and_btn_clicked();

    void on_m_diff_btn_clicked();

    void on_m_contains_btn_clicked();

    void on_m_equality_btn_clicked();

    void on_m_swap_clicked();

    void on_actionLimpar_tudo_triggered();

signals:
    void new_automaton(unsigned machine, dfa_type automaton);
    void new_automaton(unsigned machine, ndfa_type automaton);
    void clean_up();

private:
    Ui::MainWindow *ui;
    Facade * m_facade;
};

#endif // MAINWINDOW_H
