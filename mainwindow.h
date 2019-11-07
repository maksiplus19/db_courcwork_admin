#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "createshowdialog.h"
#include "createepisodedialog.h"
#include "deldialog.h"

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

    void on_timer_timeout();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *showModel;
    QSqlTableModel *episodeModel;
    QSqlTableModel *joinModel;
    QSqlQuery query;

    QTimer *timer;
};

#endif // MAINWINDOW_H
