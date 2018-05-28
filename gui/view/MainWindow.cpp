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
    ui->m_result_machine->set_facade(m_facade);

    QObject::connect(m_facade, SIGNAL(update_automaton_to_m1(const dfa_type&, QString)),
                     ui->m_machine_1, SLOT (update_automaton(const dfa_type&, QString)));
    QObject::connect(m_facade, SIGNAL(update_automaton_to_m1(const ndfa_type&, QString)),
                     ui->m_machine_1, SLOT (update_automaton(const ndfa_type&, QString)));

    QObject::connect(m_facade, SIGNAL(update_automaton_to_m2(const dfa_type&, QString)),
                     ui->m_machine_2, SLOT (update_automaton(const dfa_type&, QString)));
    QObject::connect(m_facade, SIGNAL(update_automaton_to_m2(const ndfa_type&, QString)),
                     ui->m_machine_2, SLOT (update_automaton(const ndfa_type&, QString)));

    QObject::connect(m_facade, SIGNAL(update_result(Facade::automaton_ptr_container_type&)),
                     ui->m_result_machine, SLOT (update_result(Facade::automaton_ptr_container_type&)));

    QObject::connect(ui->m_result_machine, SIGNAL(new_automaton(unsigned, dfa_type)),
                                  m_facade, SLOT (new_automaton(unsigned, dfa_type)));

    QObject::connect(ui->m_result_machine, SIGNAL(new_automaton(unsigned, ndfa_type)),
                                  m_facade, SLOT (new_automaton(unsigned, ndfa_type)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_facade;
}

void MainWindow::on_m_or_btn_clicked()
{
    Facade::automaton_type_ptr m1 = ui->m_machine_1->current_machine();
    Facade::automaton_type_ptr m2 = ui->m_machine_2->current_machine();

    if (m1.get() && m2.get())
        m_facade->union_(m1, m2);
}

void MainWindow::on_m_concat_btn_clicked()
{
    Facade::automaton_type_ptr m1 = ui->m_machine_1->current_machine();
    Facade::automaton_type_ptr m2 = ui->m_machine_2->current_machine();

    if (m1.get() && m2.get())
        m_facade->concatenation(m1, m2);
}

void MainWindow::on_m_and_btn_clicked()
{
    Facade::automaton_type_ptr m1 = ui->m_machine_1->current_machine();
    Facade::automaton_type_ptr m2 = ui->m_machine_2->current_machine();

    if (m1.get() && m2.get())
        m_facade->intersection(m1, m2);
}

void MainWindow::on_m_diff_btn_clicked()
{
    Facade::automaton_type_ptr m1 = ui->m_machine_1->current_machine();
    Facade::automaton_type_ptr m2 = ui->m_machine_2->current_machine();

    if (m1.get() && m2.get())
        m_facade->difference(m1, m2);
}

void MainWindow::on_m_contains_btn_clicked()
{
    Facade::automaton_type_ptr m1 = ui->m_machine_1->current_machine();
    Facade::automaton_type_ptr m2 = ui->m_machine_2->current_machine();

    QString answer("T(M1) não está contida em T(M2)");

    if (m1.get() && m2.get())
        if (m_facade->contains(m2, m1))
        {
            answer = "T(M1) está contida em T(M2)";
        }

    BooleanDialog dialog(answer, this);
    dialog.exec();
}

void MainWindow::on_m_equality_btn_clicked()
{
    Facade::automaton_type_ptr m1 = ui->m_machine_1->current_machine();
    Facade::automaton_type_ptr m2 = ui->m_machine_2->current_machine();

    QString answer("T(M1) != T(M2)");

    if (m1.get() && m2.get())
        if (m_facade->equivalence(m1, m2))
        {
            answer = "T(M1) = T(M2)";
        }

    BooleanDialog dialog(answer, this);
    dialog.exec();
}
