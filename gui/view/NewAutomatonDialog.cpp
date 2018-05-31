#include "NewAutomatonDialog.hpp"
#include "ui_NewAutomatonDialog.h"
#include <iostream>
#include <string>

NewAutomatonDialog::NewAutomatonDialog(unsigned number, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAutomatonDialog),
    m_number(number)
{
    ui->setupUi(this);
    ui->error_message->setVisible(false);
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
    ui->automatonTable->setItem(ui->automatonTable->rowCount() - 1, 0, new QTableWidgetItem(""));
    ui->automatonTable->item(ui->automatonTable->rowCount() - 1, 0)->setBackground(QColor("#ff6969"));
}

void NewAutomatonDialog::on_btnDeleteLine_clicked()
{
    int i = 0;
    for (auto k : ui->automatonTable->selectionModel()->selectedIndexes()) {
        if (k.row() == 0)
            continue;
        ui->automatonTable->removeRow(k.row() - i++);
    }

    for (int i = 0; i < ui->automatonTable->rowCount(); i++)
        for (int j = 0; j < ui->automatonTable->columnCount(); j++) {
            if (i == j && j == 0)
                continue;
            if (i == 0)
                symbol_care(ui->automatonTable->item(i, j));
            if (j == 0)
                state_care(ui->automatonTable->item(i, j));
            else
                transition_care(ui->automatonTable->item(i, j));
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
    bool correctness = true;

    if (ui->automatonTable->rowCount() == 1)
        correctness = false;

    for (int i = 0; i < ui->automatonTable->rowCount() && correctness; i++)
        for (int j = 0; j < ui->automatonTable->columnCount() && correctness; j++) {
            if (ui->automatonTable->item(i, j) == nullptr || (i == j && j == 0))
                continue;

            if (ui->automatonTable->item(i, j)->backgroundColor().name().compare("#ff6969") == 0)
                correctness = false;
        }

    if (!correctness) {
        ui->error_message->setVisible(true);
    } else {
        emit new_automaton(m_number, create_machine());
        this->close();
    }

}

formal_device::finite_automaton::NonDeterministic NewAutomatonDialog::create_machine()
{
    std::set<std::string> symbols;
    for (int j = 1; j < ui->automatonTable->columnCount(); j++)
        symbols.insert(ui->automatonTable->item(0, j)->text().toStdString());

    std::set<std::string> states;
    for (int i = 1; i < ui->automatonTable->rowCount(); i++)
        states.insert(ui->automatonTable->item(i, 0)->text().toStdString());

    std::map<std::string, std::map<std::string, std::set<std::string>>> transitions;
    for (int i = 1; i < ui->automatonTable->rowCount(); i++) {
        for (int j = 1; j < ui->automatonTable->columnCount(); j++) {
            std::set<std::string> trans_states;
            if (ui->automatonTable->item(i, j) == nullptr || ui->automatonTable->item(i, j)->text().size() == 0) {
                transitions[ui->automatonTable->item(i, 0)->text().toStdString()][ui->automatonTable->item(0, j)->text().toStdString()] = trans_states;
                continue;
            }

            std::string segment = ui->automatonTable->item(i, j)->text().toStdString();
            segment.erase(std::remove(segment.begin(), segment.end(), ' '), segment.end());

            int k = segment.size();
            QString state = "";
            std::set<std::string> state_set;

            for (auto aux : segment) {
                QString character(aux);
                k--;

                if (character.compare(",") == 0) {
                    state_set.insert(state.toStdString());
                    state = "";
                } else {
                    state += character;
                    if (k == 0)
                        state_set.insert(state.toStdString());
                }
            }

            std::string state_name = ui->automatonTable->item(i, 0)->text().toStdString();
            state_name.erase(std::remove(state_name.begin(), state_name.end(), '*'), state_name.end());
            state_name.erase(std::remove(state_name.begin(), state_name.end(), '-'), state_name.end());
            state_name.erase(std::remove(state_name.begin(), state_name.end(), '>'), state_name.end());

            transitions[state_name][ui->automatonTable->item(0, j)->text().toStdString()] = state_set;
        }
    }
    return formal_device::parser::create_automaton(symbols, states, transitions);
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

int global_control = 1;

void NewAutomatonDialog::on_automatonTable_itemChanged(QTableWidgetItem *item)
{
    if (global_control)
        global_control--;
    else
        return;

    if ((item->row() == item->column() && item->column() == 0)) {
        global_control++;
        return;
    }

    if (item->row() == 0)
        symbol_care(item);

    if (item->column() == 0)
        state_care(item);

    if (item->column() > 0 && item->row() > 0)
        transition_care(item);

    global_control++;
}

void NewAutomatonDialog::symbol_care(QTableWidgetItem *item)
{
    if (item->text().size() != 1) {
        item->setBackground(QColor("#ff6969"));
        return;
    }
    for (auto character : QString("'!@#$%&*()-_=+§|ABCDEFGHIJKLMNOPQRSTUVWXYZ,<.>;:/?]}º[{ª\\\""))
        if (item->text().compare(character) == 0) {
            item->setBackground(QColor("#ff6969"));
            return;
        }

    symbol_verification();
}

void NewAutomatonDialog::symbol_verification()
{
    for (int j = 1; j < ui->automatonTable->columnCount(); j++) {
        if (ui->automatonTable->item(0, j)->text().size() != 1)
            continue;
        bool paint = true;
        for (auto character : QString("'!@#$%&*()-_=+§|ABCDEFGHIJKLMNOPQRSTUVWXYZ,<.>;:/?]}º[{ª\\\""))
            if (ui->automatonTable->item(0, j)->text().compare(character) == 0)
                paint = false;

        if (paint)
            ui->automatonTable->item(0, j)->setBackground(QColor("#ffffff"));
    }

    for (int i = 1; i < ui->automatonTable->columnCount() - 1; i++) {
        if (ui->automatonTable->item(0, i)->text().size() == 0)
            continue;

        for (int j = (i + 1); j < ui->automatonTable->columnCount(); j++) {
            if (ui->automatonTable->item(0, j)->text().size() == 0)
                continue;

            if (ui->automatonTable->item(0, i)->text().compare(ui->automatonTable->item(0, j)->text()) == 0) {
                ui->automatonTable->item(0, i)->setBackground(QColor("#ff6969"));
                ui->automatonTable->item(0, j)->setBackground(QColor("#ff6969"));
            }
        }
    }
}

void NewAutomatonDialog::state_care(QTableWidgetItem *item)
{
    int i = 0;
    bool paint = true;

    if (item->row() == 1)
        i = 3;

    for (auto character : item->text()) {
        switch (i) {

        case 0:
            if (character == '*')
                i = 1;
            if (character == 'q')
                i = 2;
            break;

        case 1:
            if (character == 'q')
                i = 2;
            break;

        case 2:
            paint = true;
            for (auto symbol : "0123456789")
                if (character == symbol)
                    paint = false;
            if (paint) {
                item->setBackground(QColor("#ff6969"));
                return;
            }
            break;

        case 3:
            if (character == '*')
                i = 4;
            if (character == '-')
                i = 5;
            break;

        case 4:
            if (character == '-')
                i = 5;
            break;

        case 5:
            if (character == '>')
                i = 1;
            break;
        }
    }

    if (paint) {
        item->setBackground(QColor("#ff6969"));
        return;
    }

    state_verification();
}

void NewAutomatonDialog::state_verification()
{
    for (int j = 1; j < ui->automatonTable->rowCount(); j++) {
        if (ui->automatonTable->item(j, 0)->text().size() < 2)
            continue;
        state_repaint(ui->automatonTable->item(j, 0));
    }

    for (int i = 1; i < ui->automatonTable->rowCount() - 1; i++) {
        if (ui->automatonTable->item(i, 0)->text().size() == 0)
            continue;

        std::string i_segment = ui->automatonTable->item(i, 0)->text().toStdString();

        i_segment.erase(std::remove(i_segment.begin(), i_segment.end(), '*'), i_segment.end());
        i_segment.erase(std::remove(i_segment.begin(), i_segment.end(), '-'), i_segment.end());
        i_segment.erase(std::remove(i_segment.begin(), i_segment.end(), '>'), i_segment.end());

        for (int j = (i + 1); j < ui->automatonTable->rowCount(); j++) {
            if (ui->automatonTable->item(j, 0)->text().size() == 0)
                continue;

            std::string j_segment = ui->automatonTable->item(j, 0)->text().toStdString();

            j_segment.erase(std::remove(j_segment.begin(), j_segment.end(), '*'), j_segment.end());
            j_segment.erase(std::remove(j_segment.begin(), j_segment.end(), '-'), j_segment.end());
            j_segment.erase(std::remove(j_segment.begin(), j_segment.end(), '>'), j_segment.end());

            if (i_segment.compare(j_segment) == 0) {
                ui->automatonTable->item(i, 0)->setBackground(QColor("#ff6969"));
                ui->automatonTable->item(j, 0)->setBackground(QColor("#ff6969"));
            }
        }
    }

    for (int i = 1; i < ui->automatonTable->rowCount(); i++)
        for (int j = 1; j < ui->automatonTable->columnCount(); j++)
            transition_care(ui->automatonTable->item(i, j));
}

void NewAutomatonDialog::state_repaint(QTableWidgetItem *item)
{
    int i = 0;
    bool paint = false;

    if (item->row() == 1)
        i = 3;

    for (auto character : item->text()) {
        switch (i) {

        case 0:
            if (character == '*')
                i = 1;
            if (character == 'q')
                i = 2;
            break;

        case 1:
            if (character == 'q')
                i = 2;
            break;

        case 2:
            paint = false;
            for (auto symbol : "0123456789")
                if (character == symbol)
                    paint = true;
            break;

        case 3:
            if (character == '*')
                i = 4;
            if (character == '-')
                i = 5;
            break;

        case 4:
            if (character == '-')
                i = 5;
            break;

        case 5:
            if (character == '>')
                i = 1;
            break;
        }
    }

    if (paint)
        item->setBackground(QColor("#ffffff"));
}

void NewAutomatonDialog::transition_care(QTableWidgetItem *item)
{
    if (item == nullptr)
        return;

    std::string segment = item->text().toStdString();
    segment.erase(std::remove(segment.begin(), segment.end(), ' '), segment.end());

    if (item->text().size() == 0) {
        item->setBackground(QColor("#ffffff"));
        return;
    }

    int i = 0;
    QString state;
    bool paint = true;

    for (auto character : segment) {

        switch (i) {
        case 0:
            if (character == ' ')
                break;
            if (character == 'q') {
                paint = true;
                state = "q";
                i = 1;
                break;
            }
            item->setBackground(QColor("#ff6969"));
            return;

        case 1:
            for (auto number : "0123456789")
                if (character == number) {
                    state += number;
                    paint = false;
                    i = 2;
                }
            if (i == 1) {
                item->setBackground(QColor("#ff6969"));
                return;
            }
            break;

        case 2:
            if (character == ' ') {
                i = 3;
                break;
            }
            if (character == ',') {
                if (transition_verification(state)) {
                    paint = true;
                    i = 0;
                    break;
                }
                item->setBackground(QColor("#ff6969"));
                return;
            }
            paint = true;
            for (auto number : "0123456789")
                if (character == number) {
                    state += number;
                    paint = false;
                }
            if (paint) {
                item->setBackground(QColor("#ff6969"));
                return;
            }
            break;

        case 3:
            if (character == ' ')
                break;
            if (character == ',') {
                if (transition_verification(state)) {
                    paint = true;
                    i = 0;
                    break;
                }
            }
            item->setBackground(QColor("#ff6969"));
            return;
        }
    }

    if (paint || !transition_verification(state))
        item->setBackground(QColor("#ff6969"));
    else
        item->setBackground(QColor("#ffffff"));
}

bool NewAutomatonDialog::transition_verification(QString state)
{
    for (int j = 1; j < ui->automatonTable->rowCount(); j++) {

        std::string segment = ui->automatonTable->item(j, 0)->text().toStdString();

        segment.erase(std::remove(segment.begin(), segment.end(), '*'), segment.end());
        segment.erase(std::remove(segment.begin(), segment.end(), '-'), segment.end());
        segment.erase(std::remove(segment.begin(), segment.end(), '>'), segment.end());

        if (segment.compare(state.toStdString()) == 0)
            return true;
    }
    return false;
}
