#include "DynamicGrammarWidget.hpp"
#include "ui_DynamicGrammarWidget.h"
#include <iostream>

DynamicGrammarWidget::DynamicGrammarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DynamicGrammarWidget)
{
    ui->setupUi(this);
    ui->msg->setVisible(false);
}

DynamicGrammarWidget::~DynamicGrammarWidget()
{
    delete ui;
}

void DynamicGrammarWidget::on_cleanButton_clicked()
{
    ui->grammar->clear();
    ui->msg->setVisible(false);
    emit grammar_changed();
}

void DynamicGrammarWidget::on_validateButton_clicked()
{
    emit new_grammar(ui->grammar->toPlainText().toStdString());
}

void DynamicGrammarWidget::on_emptinessButton_clicked()
{
    emit emptiness();
}

void DynamicGrammarWidget::on_finitenessButton_clicked()
{
    emit finiteness();
}

void DynamicGrammarWidget::on_isFactoredButton_clicked()
{
    emit factored();
}

void DynamicGrammarWidget::on_grammar_textChanged()
{
    emit grammar_changed();
}

void DynamicGrammarWidget::grammar_construction(bool contructed)
{
    if (contructed) {
        ui->msg->setText("Gramatica Validada!");
        ui->msg->setStyleSheet("color:green");
    } else {
        ui->msg->setText("Gramatica Invalida!");
        ui->msg->setStyleSheet("color:red");
    }
    ui->msg->setVisible(true);
}

void DynamicGrammarWidget::grammar_not_validated()
{
    ui->msg->setText("Gramatica Nao Validada!");
    ui->msg->setStyleSheet("color:red");
    ui->msg->setVisible(true);
}

void DynamicGrammarWidget::factored_result(bool result)
{
    if (result) {
        ui->msg->setText("Gramatica Fatorada!");
        ui->msg->setStyleSheet("color:black");
    } else {
        ui->msg->setText("Gramatica Nao Fatorada!");
        ui->msg->setStyleSheet("color:black");
    }
    ui->msg->setVisible(true);
}

void DynamicGrammarWidget::emptiness_result(bool result)
{
    if (result) {
        ui->msg->setText("Gramatica Gera a Linguagem Vazia!");
        ui->msg->setStyleSheet("color:black");
    } else {
        ui->msg->setText("Gramatica Nao Gera a Linguagem Vazia!");
        ui->msg->setStyleSheet("color:black");
    }
    ui->msg->setVisible(true);
}

void DynamicGrammarWidget::finiteness_result(bool result)
{
    if (result) {
        ui->msg->setText("Gramatica Gera uma Linguagem Finita!");
        ui->msg->setStyleSheet("color:black");
    } else {
        ui->msg->setText("Gramatica Gera uma Linguagem Infinita!");
        ui->msg->setStyleSheet("color:black");
    }
    ui->msg->setVisible(true);
}
