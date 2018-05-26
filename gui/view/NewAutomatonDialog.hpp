#ifndef NEWAUTOMATONDIALOG_H
#define NEWAUTOMATONDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>
#include <formal_languages/devices/FiniteAutomaton.hpp>

namespace Ui {
class NewAutomatonDialog;
}

class NewAutomatonDialog : public QDialog
{
    Q_OBJECT

public:
    using dfa_type = formal_device::finite_automaton::Deterministic;
    using ndfa_type = formal_device::finite_automaton::NonDeterministic;

    explicit NewAutomatonDialog(unsigned number, QWidget *parent = 0);
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

signals:
    void new_automaton(unsigned machine, QString automaton);
    void new_automaton(unsigned machine, dfa_type automaton);
    void new_automaton(unsigned machine, ndfa_type automaton);

private:
    Ui::NewAutomatonDialog *ui;
    unsigned m_number;
};

#endif // NEWAUTOMATONDIALOG_H
