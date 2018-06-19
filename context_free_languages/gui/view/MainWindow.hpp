#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <control/Facade.hpp>
#include <view/NumberDialog.hpp>
#include <QListWidgetItem>

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
    void set_grammar_name(std::string, bool);

    void select_grammar(std::string grammar_name);
    void on_history_itemClicked(QListWidgetItem *item);

signals:
    void new_grammar(std::string grammar_text);
    void another_grammar_selected(std::string);

private:
    Ui::MainWindow *ui;
    Facade * m_facade;
};

#endif // MAINWINDOW_H
