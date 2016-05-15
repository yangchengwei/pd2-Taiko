#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Start_2->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Start_clicked()
{
    game2.timer->stop();
    game.show();
    game.startGame();
    ui->Start_2->setVisible(true);
}

void MainWindow::on_Exit_clicked()
{
    this->close();
}

void MainWindow::on_Start_2_clicked()
{
    game.timer->stop();
    game2.show();
    game2.startGame();
}
