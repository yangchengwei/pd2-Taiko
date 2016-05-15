#ifndef GAME2_H
#define GAME2_H

#include <QWidget>
#include <QLabel>
#include <QKeyEvent>

namespace Ui {
class Game2;
}

class Game2 : public QWidget
{
    Q_OBJECT

public:
    explicit Game2(QWidget *parent = 0);
    ~Game2();

    QTimer *timer;
    void startGame();

private:
    Ui::Game2 *ui;
    QLabel* drum[10];
    QLabel* comboLabel[3];
    QString countPath;
    QLabel* recentDrum;
    int x, y;
    int score;
    int speed;
    int speed_up_count;
    bool speed_stage[4];
    int gameTime;
    int combo;
    int max_combo;
    int player;

    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

private slots:
    void countDown();
    void setGame();
    void mainGame();
    void setTarget(int, int);
    void on_restart_clicked();
    void on_exit_clicked();
};

#endif // GAME2_H
