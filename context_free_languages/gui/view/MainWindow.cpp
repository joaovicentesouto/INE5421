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

    // ***** Has Recursion ***** //

    QObject::connect(ui->dynamicGrammar, SIGNAL(has_recursion()),
                     m_facade, SLOT(has_recursion()));

    // ***** N-Step Factoring ***** //

    QObject::connect(m_facade, SIGNAL(set_static_grammar(std::string, std::string)),
                     ui->staticGrammar, SLOT(set_grammar(std::string, std::string)));

    // ***** Update Static Grammar Data ***** //

    QObject::connect(m_facade, SIGNAL(update_dynamic_grammar_data(std::string)),
                     ui->dynamicGrammar, SLOT(set_dynamic_grammar_data(std::string)));

    // ***** Update History View ***** //

    QObject::connect(m_facade, SIGNAL(insert_grammar_name(std::string, bool)),
                     this, SLOT(set_grammar_name(std::string, bool)));

    // ***** Update Facade Grammar With Selected Grammar ***** //

    QObject::connect(this, SIGNAL(another_grammar_selected(std::string)),
                     m_facade, SLOT(change_grammar(std::string)));

    // ***** Update Dynamic Grammar With Selected Grammar ***** //

    QObject::connect(m_facade, SIGNAL(set_dynamic_grammar(std::string)),
                     ui->dynamicGrammar, SLOT(set_dynamic_grammar(std::string)));

    // ***** Update Static Grammar Data With Resulted Data Grammar ***** //

    QObject::connect(m_facade, SIGNAL(update_static_grammar_data(std::string)),
                     ui->staticGrammar, SLOT(set_grammar_data(std::string)));

    // ***** Update Grammar History ***** //

    QObject::connect(ui->staticGrammar, SIGNAL(select_grammar(std::string)),
                     this, SLOT(select_grammar(std::string)));

    // ***** Update Grammar History ***** //

    QObject::connect(ui->dynamicGrammar, SIGNAL(clean_main()),
                     this, SLOT(clean_history()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_facade;
}

void MainWindow::clean_history()
{
    for (int i = 0; i < ui->history->count(); i++)
        ui->history->item(i)->setBackgroundColor(QColor("#ffffff"));
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

void MainWindow::set_grammar_name(std::string name, bool paint)
{
    QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(name));

    if (paint) {
        for (int i = 0; i < ui->history->count(); i++)
            ui->history->item(i)->setBackgroundColor(QColor("#ffffff"));
        item->setBackgroundColor(QColor("#71d773"));
    }

    ui->history->addItem(item);
}

void MainWindow::select_grammar(std::string grammar_name)
{
    for (int i = 0; i < ui->history->count(); i++) {
        if (ui->history->item(i)->text().toStdString() == grammar_name)
            ui->history->item(i)->setBackgroundColor(QColor("#71d773"));
        else
            ui->history->item(i)->setBackgroundColor(QColor("#ffffff"));
    }

    ui->history->clearSelection();
    emit another_grammar_selected(grammar_name);
}

void MainWindow::on_history_itemClicked(QListWidgetItem *item)
{
    for (int i = 0; i < ui->history->count(); i++)
        ui->history->item(i)->setBackgroundColor(QColor("#ffffff"));

    item->setBackgroundColor(QColor("#71d773"));
    ui->history->clearSelection();
    emit another_grammar_selected(item->text().toStdString());
}
