#ifndef BOOLEANDIALOG_HPP
#define BOOLEANDIALOG_HPP

#include <QDialog>
#include <QString>

namespace Ui {
class BooleanDialog;
}

class BooleanDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BooleanDialog(QString answer, QWidget *parent = 0);
    ~BooleanDialog();

private slots:
    void on_m_close_clicked();

private:
    Ui::BooleanDialog *ui;
};

#endif // BOOLEANDIALOG_HPP
