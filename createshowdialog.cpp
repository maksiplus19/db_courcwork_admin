#include "createshowdialog.h"
#include "ui_createshowdialog.h"

CreateShowDialog::CreateShowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateShowDialog)
{
    ui->setupUi(this);
}

CreateShowDialog::~CreateShowDialog()
{
    delete ui;
}

int CreateShowDialog::getYear() const
{
    return year;
}

int CreateShowDialog::getTiming() const
{
    return timing;
}

QString CreateShowDialog::getName() const
{
    return name;
}

QString CreateShowDialog::getDescription() const
{
    return description;
}

void CreateShowDialog::on_buttonBox_accepted()
{
    name = ui->nameEdit->text();
    if (name == "")
        isOk &= false;
    year = ui->yearSpin->value();
    timing = ui->timingSpin->value();
    description = ui->textEdit->toPlainText();
}

void CreateShowDialog::on_buttonBox_rejected()
{
    isOk = false;
}
