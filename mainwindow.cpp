#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->joinView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    db = QSqlDatabase::addDatabase("QODBC3");
    db.setDatabaseName("DRIVER={SQL Server Native Client 11.0};SERVER=localhost\\SQLExpress;DATABASE=SerialTracker;Trusted_connection=yes");

    if (!db.open())
    {
        QMessageBox::critical(this, "Ошибка", "Не удалось подключться к базе данных");
    }

    showModel = new QSqlTableModel(this, db);
    showModel->setTable("Show");
    showModel->select();

    ui->showTable->setModel(showModel);
    ui->showTable->resizeColumnToContents(0);
    ui->showTable->resizeColumnToContents(1);
    ui->showTable->resizeColumnToContents(2);
    ui->showTable->resizeColumnToContents(3);
    ui->showTable->resizeColumnToContents(5);

    episodeModel = new QSqlTableModel(this, db);
    episodeModel->setTable("Episode");
    episodeModel->select();

    ui->episodeTable->setModel(episodeModel);
    ui->episodeTable->resizeColumnToContents(0);
    ui->episodeTable->resizeColumnToContents(1);
    ui->episodeTable->resizeColumnToContents(2);
    ui->episodeTable->resizeColumnToContents(3);
    ui->episodeTable->resizeColumnToContents(4);

    joinModel = new QSqlTableModel(this, db);
    joinModel->setTable("ShowEpisodeView");
    joinModel->select();

    ui->joinView->setModel(joinModel);
    ui->joinView->resizeColumnsToContents();

    query = QSqlQuery(db);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
    timer->start(500);
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
    showModel->select();
    joinModel->select();
    ui->joinView->resizeColumnsToContents();
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
    episodeModel->select();
    joinModel->select();
    ui->joinView->resizeColumnsToContents();

    ui->episodeTable->resizeColumnToContents(0);
    ui->episodeTable->resizeColumnToContents(1);
    ui->episodeTable->resizeColumnToContents(2);
    ui->episodeTable->resizeColumnToContents(3);
    ui->episodeTable->resizeColumnToContents(4);
}

void MainWindow::on_actionDelShow_triggered()
{
    DelDialog *dialog = new DelDialog("сериала");
    if (dialog->exec() == 0)
        return;

    query.exec("exec DelShow " + QString::fromStdString(std::to_string(dialog->getValue())));
    showModel->select();
    joinModel->select();
    ui->joinView->resizeColumnsToContents();

    ui->showTable->resizeColumnToContents(0);
    ui->showTable->resizeColumnToContents(1);
    ui->showTable->resizeColumnToContents(2);
    ui->showTable->resizeColumnToContents(3);
    ui->showTable->resizeColumnToContents(5);
}

void MainWindow::on_actionDelEpisode_triggered()
{
    DelDialog *dialog = new DelDialog("серии");
    if (dialog->exec() == 0)
        return;

    query.exec("exec DelEpisode " + QString::fromStdString(std::to_string(dialog->getValue())));
    episodeModel->select();
    joinModel->select();
    ui->joinView->resizeColumnsToContents();

    ui->episodeTable->resizeColumnToContents(0);
    ui->episodeTable->resizeColumnToContents(1);
    ui->episodeTable->resizeColumnToContents(2);
    ui->episodeTable->resizeColumnToContents(3);
    ui->episodeTable->resizeColumnToContents(4);
}

void MainWindow::on_timer_timeout()
{
    joinModel->select();
    ui->joinView->resizeColumnsToContents();
}
