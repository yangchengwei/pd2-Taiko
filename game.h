#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QLabel>
#include <QKeyEvent>

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();

    QTimer *timer;
    void startGame();

private:
    Ui::Game *ui;
    QLabel* drum[10];
    QLabel* comboLabel[3];
    QString countPath;
    QLabel* recentDrum;
    int x, y;
    int score;
    int speed;
    int speed_up_count;
    bool speed_stage[4];
    bool autoPress;
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
    void auto_play();
    void on_Auto_clicked();
    void on_restart_clicked();
    void on_exit_clicked();
};

#endif // GAME_H
