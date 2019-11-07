#include "deldialog.h"
#include "ui_deldialog.h"

DelDialog::DelDialog(QString object, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelDialog)
{
    ui->setupUi(this);

    ui->label->setText("ID " + object);
}

DelDialog::~DelDialog()
{
    delete ui;
}

int DelDialog::getValue()
{
    return ui->spinBox->value();
}
