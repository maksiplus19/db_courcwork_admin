#ifndef DELDIALOG_H
#define DELDIALOG_H

#include <QDialog>

namespace Ui {
class DelDialog;
}

class DelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DelDialog(QString object, QWidget *parent = 0);
    ~DelDialog();

    int getValue();

private:
    Ui::DelDialog *ui;
};

#endif // DELDIALOG_H
