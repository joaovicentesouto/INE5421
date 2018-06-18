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
    void new_grammar(std::string grammar_text);

private:
    Ui::MainWindow *ui;
    Facade * m_facade;
};

#endif // MAINWINDOW_H
