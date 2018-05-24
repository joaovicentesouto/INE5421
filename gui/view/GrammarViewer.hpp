#ifndef GRAMMARVIEWER_HPP
#define GRAMMARVIEWER_HPP

#include <QDialog>

namespace Ui {
class GrammarViewer;
}

class GrammarViewer : public QDialog
{
    Q_OBJECT

public:
    explicit GrammarViewer(QWidget *parent = 0);
    ~GrammarViewer();

private:
    Ui::GrammarViewer *ui;
};

#endif // GRAMMARVIEWER_HPP
