#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include "createshowdialog.h"
#include "createepisodedialog.h"
#include <QtSql/QSqlError>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionCreateShow_triggered();

    void on_actionCreateEpisode_triggered();

    void on_actionDelShow_triggered();

    void on_actionDelEpisode_triggered();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
    QSqlQuery query;
};

#endif // MAINWINDOW_H
