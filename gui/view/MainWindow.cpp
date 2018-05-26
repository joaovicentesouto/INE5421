#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_facade(new Facade())
{
    ui->setupUi(this);
    ui->m_machine_1->name("Máquina 1");
    ui->m_machine_2->name("Máquina 2");

    ui->m_machine_1->set_facade(m_facade);
    ui->m_machine_2->set_facade(m_facade);

    QObject::connect(m_facade, SIGNAL(update_automaton_to_m1(dfa_type)),
                     ui->m_machine_1, SLOT (update_automaton(dfa_type)));
    QObject::connect(m_facade, SIGNAL(update_automaton_to_m1(ndfa_type)),
                     ui->m_machine_1, SLOT (update_automaton(ndfa_type)));

    QObject::connect(m_facade, SIGNAL(update_automaton_to_m2(dfa_type)),
                     ui->m_machine_2, SLOT (update_automaton(dfa_type)));
    QObject::connect(m_facade, SIGNAL(update_automaton_to_m2(ndfa_type)),
                     ui->m_machine_2, SLOT (update_automaton(ndfa_type)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_facade;
}
