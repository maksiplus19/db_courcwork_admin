#ifndef CREATEEPISODEDIALOG_H
#define CREATEEPISODEDIALOG_H

#include <QDialog>

namespace Ui {
class CreateEpisodeDialog;
}

class CreateEpisodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateEpisodeDialog(QWidget *parent = 0);
    ~CreateEpisodeDialog();

    int getShowId() const;

    int getSeason() const;

    int getSeries() const;

    QString getName() const;

    QString getDescription() const;

    bool isOk = true;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CreateEpisodeDialog *ui;

    int showId;
    int season;
    int series;
    QString name;
    QString description;
};

#endif // CREATEEPISODEDIALOG_H
