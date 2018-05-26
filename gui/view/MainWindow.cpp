#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_facade(new Facade())
{
    ui->setupUi(this);
    ui->m_machine_1->name(1);
    ui->m_machine_2->name(2);

    ui->m_machine_1->set_facade(m_facade);
    ui->m_machine_2->set_facade(m_facade);

    QObject::connect(m_facade, SIGNAL(update_automaton_to_m1(const dfa_type&, QString)),
                     ui->m_machine_1, SLOT (update_automaton(const dfa_type&, QString)));
    QObject::connect(m_facade, SIGNAL(update_automaton_to_m1(const ndfa_type&, QString)),
                     ui->m_machine_1, SLOT (update_automaton(const ndfa_type&, QString)));

    QObject::connect(m_facade, SIGNAL(update_automaton_to_m2(const dfa_type&, QString)),
                     ui->m_machine_2, SLOT (update_automaton(const dfa_type&, QString)));
    QObject::connect(m_facade, SIGNAL(update_automaton_to_m2(const ndfa_type&, QString)),
                     ui->m_machine_2, SLOT (update_automaton(const ndfa_type&, QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_facade;
}
