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
    ui->grammarData->clear();
    ui->msg->setVisible(false);
    emit clean_main();
}

void DynamicGrammarWidget::on_validateButton_clicked()
{
    if (validation()) {
        ui->msg->setText("Validated with successfully!");
        ui->msg->setStyleSheet("color:green");
        ui->msg->setVisible(true);
    }
}

bool DynamicGrammarWidget::validation()
{
    std::string message = emit new_grammar(ui->grammar->toPlainText().toStdString());

    if (message == "Validated with successfully!")
        return true;

    ui->msg->setText(QString::fromStdString(message));
    ui->msg->setStyleSheet("color:red");
    ui->msg->setVisible(true);
    return false;
}

void DynamicGrammarWidget::on_emptinessButton_clicked()
{
    if(!validation())
        return;

    if (emit emptiness()) {
        ui->msg->setText("L(G) is empty!");
        ui->msg->setStyleSheet("color:black");
    } else {
        ui->msg->setText("L(G) is not empty!");
        ui->msg->setStyleSheet("color:black");
    }
    ui->msg->setVisible(true);
}

void DynamicGrammarWidget::on_finitenessButton_clicked()
{
    if(!validation())
        return;

    if (emit finiteness()) {
        ui->msg->setText("L(G) is finite!");
        ui->msg->setStyleSheet("color:black");
    } else {
        ui->msg->setText("L(G) is not finite!");
        ui->msg->setStyleSheet("color:black");
    }
    ui->msg->setVisible(true);
}

void DynamicGrammarWidget::on_isFactoredButton_clicked()
{
    if(!validation())
        return;

    if (emit factored()) {
        ui->msg->setText("G is factored!");
        ui->msg->setStyleSheet("color:black");
    } else {
        ui->msg->setText("G is not factored!");
        ui->msg->setStyleSheet("color:black");
    }
    ui->msg->setVisible(true);
}

void DynamicGrammarWidget::on_recursionButton_clicked()
{
    if(!validation())
        return;

    if (emit has_recursion()) {
        ui->msg->setText("G has recursion on left!");
        ui->msg->setStyleSheet("color:black");
    } else {
        ui->msg->setText("G has not recursion on left!");
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
