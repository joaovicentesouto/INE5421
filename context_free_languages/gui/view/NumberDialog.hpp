#ifndef NUMBERDIALOG_HPP
#define NUMBERDIALOG_HPP

//#include <QDialog>
#include <QDialog>
namespace Ui {
class NumberDialog;
}

class NumberDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NumberDialog(QWidget *parent = 0);
    ~NumberDialog();

private slots:
    void on_cancelButton_clicked();
    void on_confirmButton_clicked();

signals:
    void factoring(uint n);
    void set_msg_text(QString);

private:
    Ui::NumberDialog *ui;
};

#endif // NUMBERDIALOG_HPP
