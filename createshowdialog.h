#ifndef CREATESHOWDIALOG_H
#define CREATESHOWDIALOG_H

#include <QtWidgets/QDialog>

namespace Ui {
class CreateShowDialog;
}

class CreateShowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateShowDialog(QWidget *parent = 0);
    ~CreateShowDialog();

    int getYear() const;

    int getTiming() const;

    QString getName() const;

    QString getDescription() const;

    bool isOk = true;
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CreateShowDialog *ui;
    int year;
    int timing;
    QString name;
    QString description;
};

#endif // CREATESHOWDIALOG_H
