#include "DynamicAutomatonWidget.hpp"
#include "ui_DynamicAutomatonWidget.h"

DynamicAutomatonWidget::DynamicAutomatonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DynamicAutomatonWidget)
{
    ui->setupUi(this);
}

DynamicAutomatonWidget::~DynamicAutomatonWidget()
{
    delete ui;
}

void DynamicAutomatonWidget::name(QString name)
{
    ui->m_name_machine->setText(name);
}

void DynamicAutomatonWidget::on_m_new_grammar_btn_clicked()
{
    NewGrammarDialog dialog(this);

    QObject::connect(&dialog, SIGNAL(new_grammar(grammar_type)),
                        this, SLOT  (new_grammar(grammar_type)));
    dialog.exec();
}

void DynamicAutomatonWidget::new_grammar(grammar_type new_grammar)
{

}

void DynamicAutomatonWidget::on_m_new_exp_btn_clicked()
{
    NewExpressionDialog dialog(this);

    QObject::connect(&dialog, SIGNAL(new_expression(expression_type_ptr)),
                        this, SLOT  (new_expression(expression_type_ptr)));
    dialog.exec();
}

void DynamicAutomatonWidget::new_expression(expression_type_ptr new_expression)
{

}

