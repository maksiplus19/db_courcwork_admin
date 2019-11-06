#include "createepisodedialog.h"
#include "ui_createepisodedialog.h"

CreateEpisodeDialog::CreateEpisodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateEpisodeDialog)
{
    ui->setupUi(this);
}

CreateEpisodeDialog::~CreateEpisodeDialog()
{
    delete ui;
}

int CreateEpisodeDialog::getShowId() const
{
    return showId;
}

int CreateEpisodeDialog::getSeason() const
{
    return season;
}

int CreateEpisodeDialog::getSeries() const
{
    return series;
}

QString CreateEpisodeDialog::getName() const
{
    return name;
}

QString CreateEpisodeDialog::getDescription() const
{
    return description;
}

void CreateEpisodeDialog::on_buttonBox_accepted()
{
    showId = ui->showSpin->value();
    name = ui->nameEdit->text();
    season = ui->seasonSpin->value();
    series = ui->seriesSpin->value();
    description = ui->textEdit->toPlainText();
}
