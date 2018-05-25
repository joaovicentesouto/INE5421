#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->m_machine_1->name("Máquina 1");
    ui->m_machine_2->name("Máquina 2");
}

MainWindow::~MainWindow()
{
    delete ui;
}
