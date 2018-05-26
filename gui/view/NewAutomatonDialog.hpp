#ifndef NEWAUTOMATONDIALOG_H
#define NEWAUTOMATONDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
class NewAutomatonDialog;
}

class NewAutomatonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewAutomatonDialog(QWidget *parent = 0);
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

private:
    Ui::NewAutomatonDialog *ui;
};

#endif // NEWAUTOMATONDIALOG_H
