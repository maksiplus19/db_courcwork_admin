#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets/QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QODBC3");
    db.setDatabaseName("DRIVER={SQL Server Native Client 11.0};SERVER=localhost\\SQLExpress;DATABASE=SerialTracker;Trusted_connection=yes");

    if (!db.open())
    {
        QMessageBox::critical(this, "Ошибка", "Не удалось подключться к базе данных");
    }

    model = new QSqlTableModel(this, db);
    model->setTable("Show");
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->resizeColumnToContents(2);
    ui->tableView->resizeColumnToContents(3);
    ui->tableView->resizeColumnToContents(5);


    query = QSqlQuery(db);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCreateShow_triggered()
{
    CreateShowDialog *dialog = new CreateShowDialog(this);
    if (!dialog->exec())
        return;
    if (!dialog->isOk)
        return;

    if (dialog->getDescription().isEmpty())
    {
        query.prepare("exec NewShow ':name', :year, :timing");
        query.bindValue(":name", dialog->getName());
        query.bindValue(":year", dialog->getYear());
        query.bindValue(":timing", dialog->getTiming());
    }
    else
    {
        query.prepare("exec NewShow ':name', :year, :timing, ':description'");
        query.bindValue(":name", dialog->getName());
        query.bindValue(":year", dialog->getYear());
        query.bindValue(":timing", dialog->getTiming());
        query.bindValue(":description", dialog->getDescription());
    }

    query.exec();
    query.next();
    if (query.value(0) == 0)
        QMessageBox::information(this, "Ошибка", "Не удалось выполнить действие");
    model->select();
}

void MainWindow::on_actionCreateEpisode_triggered()
{
    CreateEpisodeDialog *dialog = new CreateEpisodeDialog(this);
    if (!dialog->exec())
        return;
    if (!dialog->isOk)
        return;

    QString request = "exec NewEpisode " + QString().fromStdString(std::to_string(dialog->getShowId())) +
            ", " + QString().fromStdString(std::to_string(dialog->getSeason())) +
            ", " + QString().fromStdString(std::to_string(dialog->getSeries()));

    if (dialog->getName().isEmpty() && !dialog->getDescription().isEmpty())
    {
        request += ", null, '" + dialog->getDescription() + "'";
    }
    else
    {
        request += ", '" + dialog->getName() + "'";
        if (!dialog->getDescription().isEmpty())
            request += ", '" + dialog->getDescription() + "'";
    }
    query.exec(request);
    query.next();
    if (query.value(0) == 0)
        QMessageBox::information(this, "Ошибка", "Не удалось выполнить действие");
    model->select();
}

void MainWindow::on_actionDelShow_triggered()
{

}

void MainWindow::on_actionDelEpisode_triggered()
{

}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        model->setTable("Show");
    break;
    case 1:
        model->setTable("Episode");
    break;
    }
    model->select();
//    ui->tableView->resizeRowsToContents();
}
