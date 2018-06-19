#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_facade(new Facade())
{
    ui->setupUi(this);

    // ***** New Grammar ***** //

    QObject::connect(ui->dynamicGrammar, SIGNAL(new_grammar(std::string)),
                     m_facade, SLOT(new_grammar(std::string)));

    // ***** Factored ***** //

    QObject::connect(ui->dynamicGrammar, SIGNAL(factored()),
                     m_facade, SLOT(factored()));

    // ***** Emptiness ***** //

    QObject::connect(ui->dynamicGrammar, SIGNAL(emptiness()),
                     m_facade, SLOT(emptiness()));

    // ***** Finiteness ***** //

    QObject::connect(ui->dynamicGrammar, SIGNAL(finiteness()),
                     m_facade, SLOT(finiteness()));

    // ***** N-Step Factoring ***** //

    // ***** Update Dynamic Grammar ***** //

    QObject::connect(ui->staticGrammar, SIGNAL(set_dynamic_grammar(QString)),
                     ui->dynamicGrammar, SLOT(set_dynamic_grammar(QString)));

    // ***** Update Dynamic Grammar Data ***** //

    QObject::connect(m_facade, SIGNAL(update_grammar_data(std::string)),
                     ui->dynamicGrammar, SLOT(set_dynamic_grammar_data(std::string)));

    // ***** Update History View ***** //

    QObject::connect(m_facade, SIGNAL(insert_grammar_name(std::string)),
                     this, SLOT(set_grammar_name(std::string)));

    // ***** Update Static Grammar ***** //

    QObject::connect(m_facade, SIGNAL(set_static_grammar(std::string, std::string)),
                     ui->staticGrammar, SLOT(set_grammar(std::string, std::string)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_facade;
}

void MainWindow::on_factoringButton_clicked()
{
    if(!ui->dynamicGrammar->validation())
        return;

    NumberDialog * dialog = new NumberDialog(this);

    QObject::connect(dialog, SIGNAL(factoring(uint)), m_facade, SLOT(factoring(uint)));
    QObject::connect(dialog, SIGNAL(set_msg_text(QString)), ui->dynamicGrammar, SLOT(set_msg_text(QString)));

    dialog->exec();
}

void MainWindow::on_ownButton_clicked()
{
    if(ui->dynamicGrammar->validation()) {
        m_facade->make_own();
        ui->dynamicGrammar->set_msg_text("Transformaçao em Propria Realizada com Sucesso!");
    }
}

void MainWindow::on_simpleProductionButton_clicked()
{
    if(ui->dynamicGrammar->validation()) {
        m_facade->remove_simple_production();
        ui->dynamicGrammar->set_msg_text("Remoçao de Produçoes Simples Realizada com Sucesso!");
    }
}

void MainWindow::on_epsilonFreeButton_clicked()
{
    if(ui->dynamicGrammar->validation()) {
        m_facade->epsilon_free();
        ui->dynamicGrammar->set_msg_text("Transformaçao em Epsilon-Livre Realizada com Sucesso!");
    }
}

void MainWindow::on_inutileSymbolsButton_clicked()
{
    if(ui->dynamicGrammar->validation()) {
        m_facade->remove_inutile_symbols();
        ui->dynamicGrammar->set_msg_text("Remoçao de Simbolos Inuteis Realizada com Sucesso!");
    }
}

void MainWindow::on_deadSymbolsButton_clicked()
{
    if(ui->dynamicGrammar->validation()) {
        m_facade->remove_dead_symbols();
        ui->dynamicGrammar->set_msg_text("Remoçao de Simbolos Inferteis Realizada com Sucesso!");
    }
}

void MainWindow::on_unreachableSymbolsButton_clicked()
{
    if(ui->dynamicGrammar->validation()) {
        m_facade->remove_unreachable_symbols();
        ui->dynamicGrammar->set_msg_text("Remoçao de Simbolos Inalcançaveis Realizada com Sucesso!");
    }
}

void MainWindow::on_leftRecursionButton_clicked()
{
    if(ui->dynamicGrammar->validation()) {
        m_facade->remove_left_recursion();
        ui->dynamicGrammar->set_msg_text("Remoçao de Recurçao a Esquerda Realizada com Sucesso!");
    }
}

void MainWindow::set_grammar_name(std::string name)
{
    ui->history->addItem(new QListWidgetItem(QString::fromStdString(name)));
}
