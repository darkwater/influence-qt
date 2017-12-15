#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bookmarkdelegate.h"
#include <QAbstractItemModel>
#include <QDebug>
#include <QProcess>
#include <QStringList>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Set window flags
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::FramelessWindowHint;
    flags |= Qt::WindowStaysOnTopHint;
    setWindowFlags(flags);

    // TODO: Show on each virtual desktop

    // Load application stylesheet
    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString stylesheet = QString(file.readAll());
    setStyleSheet(stylesheet);

    // TODO: Load user stylesheet

    ui->setupUi(this);
    ui->bookmarkListView->setItemDelegate(new BookmarkDelegate());
    loadBookmarks();
}

void MainWindow::loadBookmarks()
{
    QStringList *bookmarks = new QStringList();

    // Open bookmarks file
    // TODO: adjust path
    QFile file("/home/dark/.config/influence/bookmarks.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return; // TODO: Handle better

    // Read bookmarks from file
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (line.at(line.length() - 1) == '\n')
            line.chop(1);
        bookmarks->append(line);
    }

    // Feed bookmarks into list view
    QAbstractItemModel *bookmarkModel = new QStringListModel(*bookmarks);
    ui->bookmarkListView->setModel(bookmarkModel);
}

void MainWindow::showEvent(QShowEvent * /* event */)
{
    ui->commandInput->setFocus();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        qApp->quit();
    }
}

void MainWindow::on_bookmarkListView_clicked(const QModelIndex &index)
{
    on_bookmarkListView_activated(index);
}

void MainWindow::on_bookmarkListView_activated(const QModelIndex &index)
{
    QString command = index.data().toString();
    if (command.length() == 0) return;

    QProcess::startDetached("sh", QStringList() << "-c" << command);
    qApp->quit();
}

void MainWindow::on_commandInput_returnPressed()
{
    QString command = ui->commandInput->text();
    QProcess::startDetached("sh", QStringList() << "-c" << command);
    qApp->quit();
}

MainWindow::~MainWindow()
{
    delete ui;
}
