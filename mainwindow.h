#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"
#include "game2.h"
#include <QMainWindow>

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
    void on_Start_clicked();

    void on_Exit_clicked();

    void on_Start_2_clicked();

private:
    Ui::MainWindow *ui;
    Game game;
    Game2 game2;
};

#endif // MAINWINDOW_H
