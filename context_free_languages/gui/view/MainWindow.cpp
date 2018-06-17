#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_facade(new Facade())
{
    ui->setupUi(this);

    ui->data->setReadOnly(true);
    ui->result->setReadOnly(true);

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

    // ***** Factorizable ***** //

    QObject::connect(ui->dynamicGrammar, SIGNAL(factorizable()),
                     m_facade, SLOT(factorizable()));

    QObject::connect(m_facade, SIGNAL(factorizable_result(bool)),
                     ui->dynamicGrammar, SLOT(factorizable_result(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_facade;
}

//void MainWindow::on_m_or_btn_clicked()
//{
//    Facade::automaton_type_ptr m1 = ui->m_machine_1->current_machine();
//    Facade::automaton_type_ptr m2 = ui->m_machine_2->current_machine();

//    if (m1.get() && m2.get())
//        m_facade->union_(m1, m2);
//}

//void MainWindow::on_m_concat_btn_clicked()
//{
//    Facade::automaton_type_ptr m1 = ui->m_machine_1->current_machine();
//    Facade::automaton_type_ptr m2 = ui->m_machine_2->current_machine();

//    if (m1.get() && m2.get())
//        m_facade->concatenation(m1, m2);
//}

//void MainWindow::on_m_and_btn_clicked()
//{
//    Facade::automaton_type_ptr m1 = ui->m_machine_1->current_machine();
//    Facade::automaton_type_ptr m2 = ui->m_machine_2->current_machine();

//    if (m1.get() && m2.get())
//        m_facade->intersection(m1, m2);
//}

//void MainWindow::on_m_diff_btn_clicked()
//{
//    Facade::automaton_type_ptr m1 = ui->m_machine_1->current_machine();
//    Facade::automaton_type_ptr m2 = ui->m_machine_2->current_machine();

//    if (m1.get() && m2.get())
//        m_facade->difference(m1, m2);
//}

//void MainWindow::on_m_contains_btn_clicked()
//{
//    Facade::automaton_type_ptr m1 = ui->m_machine_1->current_machine();
//    Facade::automaton_type_ptr m2 = ui->m_machine_2->current_machine();

//    QString answer("T(M1) não está contida em T(M2)");

//    if (m1.get() && m2.get())
//    {
//        if (m_facade->is_contained(m1, m2))
//            answer = "T(M1) está contida em T(M2)";

//        BooleanDialog dialog(answer, this);
//        dialog.exec();
//    }
//}

//void MainWindow::on_m_equality_btn_clicked()
//{
//    Facade::automaton_type_ptr m1 = ui->m_machine_1->current_machine();
//    Facade::automaton_type_ptr m2 = ui->m_machine_2->current_machine();

//    QString answer("T(M1) != T(M2)");

//    if (m1.get() && m2.get())
//    {
//        if (m_facade->equivalence(m1, m2))
//            answer = "T(M1) = T(M2)";

//        BooleanDialog dialog(answer, this);
//        dialog.exec();
//    }
//}

//void MainWindow::on_m_swap_clicked()
//{
//    Facade::automaton_type_ptr m1 = ui->m_machine_1->current_machine();
//    Facade::automaton_type_ptr m2 = ui->m_machine_2->current_machine();

//    const dfa_type*   dfa_m1 = m1->derived_ptr<dfa_type>();
//    const ndfa_type* ndfa_m1 = m1->derived_ptr<ndfa_type>();
//    const dfa_type*   dfa_m2 = m2->derived_ptr<dfa_type>();
//    const ndfa_type* ndfa_m2 = m2->derived_ptr<ndfa_type>();

//    if (dfa_m2)
//        emit new_automaton(11, *dfa_m2);
//    else if (ndfa_m2)
//        emit new_automaton(11, *ndfa_m2);

//    if (dfa_m1)
//        emit new_automaton(12, *dfa_m1);
//    else if (ndfa_m1)
//        emit new_automaton(12, *ndfa_m1);
//}

//void MainWindow::on_actionLimpar_tudo_triggered()
//{
//    emit clean_up();
//}
