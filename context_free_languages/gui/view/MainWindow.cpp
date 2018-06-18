#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_facade(new Facade())
{
    ui->setupUi(this);

    ui->data->setReadOnly(true);

    // ***** New Grammar ***** //

    QObject::connect(ui->dynamicGrammar, SIGNAL(new_grammar(std::string)),
                     m_facade, SLOT(new_grammar(std::string)));

    QObject::connect(m_facade, SIGNAL(grammar_construction(bool)),
                     ui->dynamicGrammar, SLOT(grammar_construction(bool)));

    // ***** Grammar Changed ***** //

    QObject::connect(ui->dynamicGrammar, SIGNAL(grammar_changed()),
                     m_facade, SLOT(grammar_changed()));

    // ***** Grammar Not Validated ***** //

    QObject::connect(m_facade, SIGNAL(not_validated()),
                     ui->dynamicGrammar, SLOT(grammar_not_validated()));

    // ***** Factored ***** //

    QObject::connect(ui->dynamicGrammar, SIGNAL(factored()),
                     m_facade, SLOT(factored()));

    QObject::connect(m_facade, SIGNAL(factored_result(bool)),
                     ui->dynamicGrammar, SLOT(factored_result(bool)));

    // ***** Emptiness ***** //

    QObject::connect(ui->dynamicGrammar, SIGNAL(emptiness()),
                     m_facade, SLOT(emptiness()));

    QObject::connect(m_facade, SIGNAL(emptiness_result(bool)),
                     ui->dynamicGrammar, SLOT(emptiness_result(bool)));

    // ***** Finiteness ***** //

    QObject::connect(ui->dynamicGrammar, SIGNAL(finiteness()),
                     m_facade, SLOT(finiteness()));

    QObject::connect(m_facade, SIGNAL(finiteness_result(bool)),
                     ui->dynamicGrammar, SLOT(finiteness_result(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_facade;
}

void MainWindow::on_ownButton_clicked()
{
    emit make_own();
}

void MainWindow::on_simpleProductionButton_clicked()
{
    emit remove_simple_production();
}

void MainWindow::on_epsilonFreeButton_clicked()
{
    emit epsilon_free();
}

void MainWindow::on_inutileSymbolsButton_clicked()
{
    emit remove_inutile_symbols();
}

void MainWindow::on_deadSymbolsButton_clicked()
{
    emit remove_dead_symbols();
}

void MainWindow::on_unreachableSymbolsButton_clicked()
{
    emit remove_unreachable_Symbols();
}

void MainWindow::on_factoringButton_clicked()
{
    NumberDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_leftRecursionButton_clicked()
{
    emit remove_left_recursion();
}
