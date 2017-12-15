#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

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
    void on_bookmarkListView_activated(const QModelIndex &index);
    void on_bookmarkListView_clicked(const QModelIndex &index);
    void on_commandInput_returnPressed();

private:
    Ui::MainWindow *ui;

    void loadBookmarks();

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void showEvent(QShowEvent *event) override;
};

#endif // MAINWINDOW_H
