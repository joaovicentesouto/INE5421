#include "NewAutomatonDialog.hpp"
#include "ui_NewAutomatonDialog.h"
#include <iostream>

NewAutomatonDialog::NewAutomatonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAutomatonDialog)
{
    ui->setupUi(this);
    ui->automatonTable->setColumnCount(1);
    ui->automatonTable->horizontalHeader()->hide();
    ui->automatonTable->verticalHeader()->hide();
    ui->automatonTable->insertRow(ui->automatonTable->rowCount());

    QTableWidgetItem *item = new QTableWidgetItem("+");
    item->setFlags(Qt::NoItemFlags);

    ui->automatonTable->setItem(0, 0, item);
}

NewAutomatonDialog::~NewAutomatonDialog()
{
    delete ui;
}

void NewAutomatonDialog::on_btnAddLine_clicked()
{
    ui->automatonTable->insertRow(ui->automatonTable->rowCount());
}

void NewAutomatonDialog::on_btnDeleteLine_clicked()
{
    int i = 0, j = -1;
    for (auto k : ui->automatonTable->selectionModel()->selectedIndexes()) {
        if (j == k.row() || k.row() == 0)
            continue;
        j = k.row();
        ui->automatonTable->removeRow(k.row() - i++);
    }
}

void NewAutomatonDialog::on_btnAddColumn_clicked()
{
    ui->automatonTable->insertColumn(ui->automatonTable->columnCount());
    ui->automatonTable->setItem(0, ui->automatonTable->columnCount() - 1, new QTableWidgetItem(""));
    ui->automatonTable->item(0, ui->automatonTable->columnCount() - 1)->setBackground(QColor("#ff6969"));
}

void NewAutomatonDialog::on_btnDeleteColumn_clicked()
{
    int i = 0, j = -1;
    for (auto k : ui->automatonTable->selectionModel()->selectedIndexes()) {
        if (j == k.column() || k.column() == 0)
            continue;
        j = k.column();
        ui->automatonTable->removeColumn(k.column() - i++);
    }

}

void NewAutomatonDialog::on_btnCancel_clicked()
{
    this->close();
}

void NewAutomatonDialog::on_btnOK_clicked()
{

}

void NewAutomatonDialog::on_btnClean_clicked()
{
    ui->automatonTable->setRowCount(0);
    ui->automatonTable->setColumnCount(1);
    ui->automatonTable->insertRow(ui->automatonTable->rowCount());

    QTableWidgetItem *item = new QTableWidgetItem("+");
    item->setFlags(Qt::NoItemFlags);

    ui->automatonTable->setItem(0, 0, item);

}

void NewAutomatonDialog::on_automatonTable_itemChanged(QTableWidgetItem *item)
{
    if (item->row() == item->column() && item->column() == 0)
        return;

    if (item->row() == 0) {
        if (item->text().size() == 1) {
            for (int j = 1; j < ui->automatonTable->columnCount() - 1; j++) {
                if (j == item->column())
                    continue;
                if (ui->automatonTable->item(0, j)->text().compare(item->text()) == 0) {
                    ui->automatonTable->item(item->row(), item->column())->setBackground(QColor("#ff6969"));
                    return;
                }
            }
        } else {
            ui->automatonTable->item(item->row(), item->column())->setBackground(QColor("#ff6969"));
            return;
        }
    }

    ui->automatonTable->item(item->row(), item->column())->setBackground(QColor("#ffffff"));
}
