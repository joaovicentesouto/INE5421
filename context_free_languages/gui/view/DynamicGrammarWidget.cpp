#include "DynamicGrammarWidget.hpp"
#include "ui_DynamicGrammarWidget.h"
#include <iostream>

DynamicGrammarWidget::DynamicGrammarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DynamicGrammarWidget)
{
    ui->setupUi(this);
    ui->msg->setVisible(false);
    ui->grammarData->setReadOnly(true);
}

DynamicGrammarWidget::~DynamicGrammarWidget()
{
    delete ui;
}

void DynamicGrammarWidget::on_cleanButton_clicked()
{
    ui->grammar->clear();
    ui->msg->setVisible(false);
}

void DynamicGrammarWidget::on_validateButton_clicked()
{
    validation();
}

bool DynamicGrammarWidget::validation()
{
    if (emit new_grammar(ui->grammar->toPlainText().toStdString())) {
        ui->msg->setVisible(false);
        return true;
    }

    ui->msg->setText("Gramatica Invalida!");
    ui->msg->setStyleSheet("color:red");
    ui->msg->setVisible(true);
    return false;
}

void DynamicGrammarWidget::on_emptinessButton_clicked()
{
    if(!validation())
        return;

    if (emit emptiness()) {
        ui->msg->setText("Gramatica Gera a Linguagem Vazia!");
        ui->msg->setStyleSheet("color:black");
    } else {
        ui->msg->setText("Gramatica Nao Gera a Linguagem Vazia!");
        ui->msg->setStyleSheet("color:black");
    }
    ui->msg->setVisible(true);
}

void DynamicGrammarWidget::on_finitenessButton_clicked()
{
    if(!validation())
        return;

    if (emit finiteness()) {
        ui->msg->setText("Gramatica Gera uma Linguagem Finita!");
        ui->msg->setStyleSheet("color:black");
    } else {
        ui->msg->setText("Gramatica Gera uma Linguagem Infinita!");
        ui->msg->setStyleSheet("color:black");
    }
    ui->msg->setVisible(true);
}

void DynamicGrammarWidget::on_isFactoredButton_clicked()
{
    if(!validation())
        return;

    if (emit factored()) {
        ui->msg->setText("Gramatica Fatorada!");
        ui->msg->setStyleSheet("color:black");
    } else {
        ui->msg->setText("Gramatica Nao Fatorada!");
        ui->msg->setStyleSheet("color:black");
    }
    ui->msg->setVisible(true);
}

void DynamicGrammarWidget::on_recursionButton_clicked()
{
    if(!validation())
        return;

    if (emit has_recursion()) {
        ui->msg->setText("Gramatica Possui Recusao!");
        ui->msg->setStyleSheet("color:black");
    } else {
        ui->msg->setText("Gramatica Nao Possui Recursao!");
        ui->msg->setStyleSheet("color:black");
    }
    ui->msg->setVisible(true);

}

void DynamicGrammarWidget::set_msg_text(QString text)
{
    ui->msg->setText(text);
    ui->msg->setStyleSheet("color:black");
    ui->msg->setVisible(true);
}

void DynamicGrammarWidget::set_dynamic_grammar(std::string grammar)
{
    ui->grammar->setText(QString::fromStdString(grammar));

}

void DynamicGrammarWidget::set_dynamic_grammar_data(std::string data)
{
    ui->grammarData->setText(QString::fromStdString(data));
}
