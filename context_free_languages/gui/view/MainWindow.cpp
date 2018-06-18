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

    // ***** Grammar Changed ***** //

    QObject::connect(ui->dynamicGrammar, SIGNAL(grammar_changed()),
                     m_facade, SLOT(grammar_changed()));

    // ***** Grammar Validated ***** //

    QObject::connect(ui->dynamicGrammar, SIGNAL(validated_grammar()),
                     m_facade, SLOT(grammar_validated()));

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

    QObject::connect(m_facade, SIGNAL(set_static_grammar(std::string)),
                     ui->staticGrammar, SLOT(set_grammar(std::string)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_facade;
}

void MainWindow::on_factoringButton_clicked()
{
    if(!m_facade->grammar_validated()) {
        ui->dynamicGrammar->grammar_not_validated();
        return;
    }

    NumberDialog * dialog = new NumberDialog(this);

    QObject::connect(dialog, SIGNAL(factoring(uint)), m_facade, SLOT(factoring(uint)));
    QObject::connect(dialog, SIGNAL(set_msg_text(QString)), ui->dynamicGrammar, SLOT(set_msg_text(QString)));

    dialog->exec();
}

void MainWindow::on_ownButton_clicked()
{
    if(m_facade->grammar_validated()) {
        m_facade->make_own();
        ui->dynamicGrammar->set_msg_text("Transformaçao em Propria Realizada com Sucesso!");
    } else
        ui->dynamicGrammar->grammar_not_validated();
}

void MainWindow::on_simpleProductionButton_clicked()
{
    if(m_facade->grammar_validated()) {
        m_facade->make_own();
        ui->dynamicGrammar->set_msg_text("Remoçao de Produçoes Simples Realizada com Sucesso!");
    } else
        ui->dynamicGrammar->grammar_not_validated();
}

void MainWindow::on_epsilonFreeButton_clicked()
{
    if(m_facade->grammar_validated()) {
        m_facade->make_own();
        ui->dynamicGrammar->set_msg_text("Transformaçao em Epsilon-Livre Realizada com Sucesso!");
    } else
        ui->dynamicGrammar->grammar_not_validated();
}

void MainWindow::on_inutileSymbolsButton_clicked()
{
    if(m_facade->grammar_validated()) {
        m_facade->make_own();
        ui->dynamicGrammar->set_msg_text("Remoçao de Simbolos Inuteis Realizada com Sucesso!");
    } else
        ui->dynamicGrammar->grammar_not_validated();
}

void MainWindow::on_deadSymbolsButton_clicked()
{
    if(m_facade->grammar_validated()) {
        m_facade->make_own();
        ui->dynamicGrammar->set_msg_text("Remoçao de Simbolos Inferteis Realizada com Sucesso!");
    } else
        ui->dynamicGrammar->grammar_not_validated();
}

void MainWindow::on_unreachableSymbolsButton_clicked()
{
    if(m_facade->grammar_validated()) {
        m_facade->make_own();
        ui->dynamicGrammar->set_msg_text("Remoçao de Simbolos Inalcançaveis Realizada com Sucesso!");
    } else
        ui->dynamicGrammar->grammar_not_validated();
}

void MainWindow::on_leftRecursionButton_clicked()
{
    if(m_facade->grammar_validated()) {
        m_facade->make_own();
        ui->dynamicGrammar->set_msg_text("Remoçao de Recurçao a Esquerda Realizada com Sucesso!");
    } else
        ui->dynamicGrammar->grammar_not_validated();
}
