#ifndef NEWAUTOMATONDIALOG_H
#define NEWAUTOMATONDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>
#include <control/Filler.hpp>
#include <context_free_languages/model/devices/FiniteAutomaton.hpp>
#include <context_free_languages/model/parsers/FiniteAutomatonParser.hpp>
#include <memory>
#include "ui_NewAutomatonDialog.h"
#include <iostream>
#include <string>

namespace Ui {
class NewAutomatonDialog;
}

class NewAutomatonDialog : public QDialog
{
    Q_OBJECT

public:
    using dfa_type = formal_device::finite_automaton::Deterministic;
    using ndfa_type = formal_device::finite_automaton::NonDeterministic;
    using automaton_type_ptr = std::shared_ptr<formal_device::finite_automaton::GenericAutomaton>;

    explicit NewAutomatonDialog(unsigned number, automaton_type_ptr f_automaton, QWidget *parent = 0);
    ~NewAutomatonDialog();

private slots:
    void on_btnAddLine_clicked();
    void on_btnDeleteLine_clicked();
    void on_btnAddColumn_clicked();
    void on_btnDeleteColumn_clicked();
    void on_btnCancel_clicked();
    void on_btnOK_clicked();
    void on_btnClean_clicked();

    void on_automatonTable_itemChanged(QTableWidgetItem *item);
    void symbol_care(QTableWidgetItem *item);
    void symbol_verification();
    void state_repaint(QTableWidgetItem *item);
    void state_care(QTableWidgetItem *item);
    void state_verification();
    void transition_care(QTableWidgetItem *item);
    bool transition_verification(QString state);

    ndfa_type create_machine();

signals:
    void new_automaton(unsigned machine, dfa_type automaton);
    void new_automaton(unsigned machine, ndfa_type automaton);

private:
    Ui::NewAutomatonDialog *ui;
    unsigned m_number;
    bool initialization = true;
    bool verification = true;
};

#endif // NEWAUTOMATONDIALOG_H
