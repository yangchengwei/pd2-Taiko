#include "game.h"
#include "ui_game.h"
#include <QTimer>
#include <QString>
#include <QMessageBox>
#include <ctime>

#include <iostream>
using namespace std;

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    timer = new QTimer();
    ui->setupUi(this);
}

Game::~Game()
{
    delete ui;
}

void Game::startGame()
{
    int i;

    drum[0]=ui->drum_0;
    drum[1]=ui->drum_1;
    drum[2]=ui->drum_2;
    drum[3]=ui->drum_3;
    drum[4]=ui->drum_4;
    drum[5]=ui->drum_5;
    drum[6]=ui->drum_6;
    drum[7]=ui->drum_7;
    drum[8]=ui->drum_8;
    drum[9]=ui->drum_9;

    comboLabel[0]=ui->combo_1;
    comboLabel[1]=ui->combo_10;
    comboLabel[2]=ui->combo_100;

    disconnect(timer, SIGNAL(timeout()), this, SLOT(auto_play()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(countDown()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(setGame()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(mainGame()));
    timer->stop();

    countPath = ":/number_3.png";
    ui->countDown->setPixmap(QPixmap(countPath));
    ui->countDown->show();

    ui->bglayer->hide();
    ui->target->hide();
    ui->explosion->hide();
    ui->judgement->hide();
    ui->speed_up->hide();
    ui->speed_up->setPixmap(QPixmap(":/speed_up.png"));
    ui->playerchar->setPixmap(QPixmap(":/playerchar_0.png"));
    ui->comboballoon->setPixmap(QPixmap(""));
    ui->mtaiko_left->setPixmap(QPixmap(""));
    ui->mtaiko_right->setPixmap(QPixmap(""));
    ui->explosion->setPixmap(QPixmap(""));
    ui->judgement->setPixmap(QPixmap(""));
    ui->scoreTitle->setText("");
    ui->score->setText("");
    ui->timeTitle->setText("");
    ui->time->setText("");
    for (i=0 ; i<10 ; i++){
        drum[i]->setPixmap(QPixmap(""));
        drum[i]->setWhatsThis("NULL");
    }
    for (i=0 ; i<4 ; i++){
        speed_stage[i] = true;
    }
    for (i=0 ; i<3 ; i++){
        comboLabel[i]->setPixmap(QPixmap(""));
    }

    connect(timer, SIGNAL(timeout()), this, SLOT(countDown()));
    timer->setInterval(10);
    x = 180;
    y = 125;
    score = 0;
    speed = 2;
    speed_up_count = 0;
    combo = 0;
    max_combo = 0;
    player = 0;
    gameTime = 30000;
    recentDrum = NULL;
    autoPress = false;
    timer->start();
}

void Game::countDown()
{
    if (countPath == ":/go.png"){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(countDown()));
        setGame();
        return;
    }

    if (x < 280){
        x += 1;
        ui->countDown->move(x, y);
    }
    else{
        x = 180;
        ui->countDown->move(x, y);
        if (countPath == ":/number_3.png"){
            countPath = ":/number_2.png";
        }
        else if (countPath == ":/number_2.png"){
            countPath = ":/number_1.png";
        }
        else if (countPath == ":/number_1.png"){
            countPath = ":/go.png";
            ui->countDown->setGeometry(180,125,200,76);
            timer->setInterval(1000);
        }
        ui->countDown->setPixmap(QPixmap(countPath));
    }
}

void Game::setGame()
{
    ui->countDown->hide();
    ui->bglayer->show();
    ui->target->show();
    ui->judgement->show();
    ui->explosion->show();
    ui->scoreTitle->setText("SCORE :");
    ui->score->setText("0");
    ui->timeTitle->setText("TIME :");
    ui->time->setText("30");

    connect(timer, SIGNAL(timeout()), this, SLOT(mainGame()));
    timer->setInterval(10);

}

void Game::mainGame(){
    int i, j;
    srand(time(NULL));

    //===== game time =====
    if (gameTime == 0){
        ui->time->setText(QString::number(0));
        QMessageBox::information(this, "game over",
                                 QString("Your score is ").append(QString::number(score)).append(",\n")
                                 .append("Max combo : ").append(QString::number(max_combo)).append("."));
        timer->stop();
        this->close();
    }
    gameTime -= 10;

    //===== score & time =====
    ui->score->setText(QString::number(score));
    ui->time->setText(QString::number(gameTime/1000 + 1));

    //===== combo =====
    int number[3];

    number[0] =  combo        % 10;
    number[1] = (combo /  10) % 10;
    number[2] = (combo / 100) % 10;

    if (combo == 0){
        ui->comboballoon->setPixmap(QPixmap(""));
        for (i=0 ; i<3 ; i++){
            comboLabel[i]->setPixmap(QPixmap(""));
        }
    }
    else{
        ui->comboballoon->setPixmap(QPixmap(":/comboballoon.png"));
        for (i=0 ; i<3 ; i++){
            switch (number[i]) {
            case 0:
                comboLabel[i]->setPixmap(QPixmap(":/number_0.png"));
                break;
            case 1:
                comboLabel[i]->setPixmap(QPixmap(":/number_1.png"));
                break;
            case 2:
                comboLabel[i]->setPixmap(QPixmap(":/number_2.png"));
                break;
            case 3:
                comboLabel[i]->setPixmap(QPixmap(":/number_3.png"));
                break;
            case 4:
                comboLabel[i]->setPixmap(QPixmap(":/number_4.png"));
                break;
            case 5:
                comboLabel[i]->setPixmap(QPixmap(":/number_5.png"));
                break;
            case 6:
                comboLabel[i]->setPixmap(QPixmap(":/number_6.png"));
                break;
            case 7:
                comboLabel[i]->setPixmap(QPixmap(":/number_7.png"));
                break;
            case 8:
                comboLabel[i]->setPixmap(QPixmap(":/number_8.png"));
                break;
            case 9:
                comboLabel[i]->setPixmap(QPixmap(":/number_9.png"));
                break;
            default:
                comboLabel[i]->setPixmap(QPixmap(""));
                break;
            }
        }
        if (combo < 100){
            comboLabel[2]->setPixmap(QPixmap(""));
        }
        if (combo < 10){
            comboLabel[1]->setPixmap(QPixmap(""));
        }
    }

    //===== speed =====
    if (combo == 0){
        speed = 2;
        speed_up_count = 0;
        for (i=0 ; i<4 ; i++){
            speed_stage[i] = true;
        }
    }
    if (speed_up_count > 0){
        if (speed_up_count == 2000){
            speed += 1;
        }
        speed_up_count -= 10;
        ui->speed_up->show();
    }
    else {
        ui->speed_up->hide();
        if (combo == 10 && speed_stage[0]){
            speed_up_count = 2000;
            speed_stage[0] = false;
        }
        else if (combo == 30 && speed_stage[1]){
            speed_up_count = 2000;
            speed_stage[1] = false;
        }
        else if (combo == 60 && speed_stage[2]){
            speed_up_count = 2000;
            speed_stage[2] = false;
        }
        else if (combo == 100 && speed_stage[3]){
            speed_up_count = 2000;
            speed_stage[3] = false;
        }
    }

    //===== player =====
    player = (gameTime / 100) % 6 + 1;
    switch (player){
    case 1:
        ui->playerchar->setPixmap(QPixmap(":/playerchar_1.png"));
        break;
    case 2:
        ui->playerchar->setPixmap(QPixmap(":/playerchar_2.png"));
        break;
    case 3:
        ui->playerchar->setPixmap(QPixmap(":/playerchar_3.png"));
        break;
    case 4:
        ui->playerchar->setPixmap(QPixmap(":/playerchar_4.png"));
        break;
    case 5:
        ui->playerchar->setPixmap(QPixmap(":/playerchar_5.png"));
        break;
    case 6:
        ui->playerchar->setPixmap(QPixmap(":/playerchar_6.png"));
        break;
    }

    //===== drum =====
    for (i=0 ; i<10 ; i++){
        if (drum[i]->x() > 10 && drum[i]->x() <= 30){
            recentDrum = drum[i];
        }
        if (recentDrum != NULL && recentDrum->x() <= 10){
            if (recentDrum->whatsThis() != "NULL"){   //player doesn't get the drum
                combo = 0;
            }
            recentDrum = NULL;
        }

        if (drum[i]->x() < -60){
            drum[i]->move(drum[(i+9)%10]->x()+60, drum[i]->y());
            rand();rand();             //make j be more random
            j = rand()%5;
            switch (j){
            case 0:
                drum[i]->setPixmap(QPixmap(":/drum_red_small.png"));
                drum[i]->setWhatsThis("drum_red_small");
                break;
            case 1:
                drum[i]->setPixmap(QPixmap(":/drum_blue_small.png"));
                drum[i]->setWhatsThis("drum_blue_small");
                break;
            case 2:
                drum[i]->setPixmap(QPixmap(":/drum_red_big.png"));
                drum[i]->setWhatsThis("drum_red_big");
                break;
            case 3:
                drum[i]->setPixmap(QPixmap(":/drum_blue_big.png"));
                drum[i]->setWhatsThis("drum_blue_big");
                break;
            default:
                drum[i]->setPixmap(QPixmap(""));
                drum[i]->setWhatsThis("NULL");
            }
        }
        else{
            drum[i]->move(drum[i]->x() - speed, drum[i]->y());
        }
    }
}

void Game::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_F){
        ui->mtaiko_left->setPixmap(QPixmap(":/mtaikoflash_red_left.png"));
    }
    else if(event->key() == Qt::Key_J){
        ui->mtaiko_right->setPixmap(QPixmap(":/mtaikoflash_red_right.png"));
    }
    else if(event->key() == Qt::Key_D){
        ui->mtaiko_left->setPixmap(QPixmap(":/mtaikoflash_blue_left.png"));
    }
    else if(event->key() == Qt::Key_K){
        ui->mtaiko_right->setPixmap(QPixmap(":/mtaikoflash_blue_right.png"));
    }
    else
        return;

    //===== NULL =====
    if (recentDrum == NULL){
        ui->judgement->setPixmap(QPixmap(":/judgement_notok.png"));
        combo = 0;
        return;
    }

    //===== red drum =====
//cout<<recentDrum->whatsThis().toStdString()<<endl;
    if ((recentDrum->whatsThis() == QString("drum_red_small") ||
         recentDrum->whatsThis() == QString("drum_red_big"))  &&
        (event->key() == Qt::Key_F || event->key() == Qt::Key_J))
    {
        if (recentDrum->x() > 15 && recentDrum->x() <= 25){
            recentDrum->setPixmap(QPixmap(""));
            recentDrum->setWhatsThis("NULL");
            ui->judgement->setPixmap(QPixmap(":/judgement_good.png"));
            ui->explosion->setPixmap(QPixmap(":/explosion_good.png"));
            score += 2;
            combo += 1;
            max_combo = (combo > max_combo) ? combo : max_combo;
        }
        else if (recentDrum->x() > 10 && recentDrum->x() <= 30){
            recentDrum->setPixmap(QPixmap(""));
            recentDrum->setWhatsThis("NULL");
            ui->judgement->setPixmap(QPixmap(":/judgement_ok.png"));
            ui->explosion->setPixmap(QPixmap(":/explosion_ok.png"));
            score += 1;
            combo += 1;
            max_combo = (combo > max_combo) ? combo : max_combo;
        }
        else {
            ui->judgement->setPixmap(QPixmap(":/judgement_notok.png"));
            combo = 0;
        }

        return;
    }


    //===== blue drum =====
    if ((recentDrum->whatsThis() == QString("drum_blue_small") ||
         recentDrum->whatsThis() == QString("drum_blue_big"))  &&
        (event->key() == Qt::Key_D || event->key() == Qt::Key_K))
    {
        if (recentDrum->x() > 15 && recentDrum->x() <= 25){
            recentDrum->setPixmap(QPixmap(""));
            recentDrum->setWhatsThis("NULL");
            ui->judgement->setPixmap(QPixmap(":/judgement_good.png"));
            ui->explosion->setPixmap(QPixmap(":/explosion_good.png"));
            score += 2;
            combo += 1;
            max_combo = (combo > max_combo) ? combo : max_combo;
        }
        else if (recentDrum->x() > 10 && recentDrum->x() <= 30){
            recentDrum->setPixmap(QPixmap(""));
            recentDrum->setWhatsThis("NULL");
            ui->judgement->setPixmap(QPixmap(":/judgement_ok.png"));
            ui->explosion->setPixmap(QPixmap(":/explosion_ok.png"));
            score += 1;
            combo += 1;
            max_combo = (combo > max_combo) ? combo : max_combo;
        }
        else {
            ui->judgement->setPixmap(QPixmap(":/judgement_notok.png"));
            combo = 0;
        }

        return;
    }

    //===== NULL =====
    ui->judgement->setPixmap(QPixmap(":/judgement_notok.png"));
    combo = 0;

    return;
}

void Game::keyReleaseEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_F){
        ui->mtaiko_left->setPixmap(QPixmap(""));
    }
    else if(event->key() == Qt::Key_J){
        ui->mtaiko_right->setPixmap(QPixmap(""));
    }
    else if(event->key() == Qt::Key_D){
        ui->mtaiko_left->setPixmap(QPixmap(""));
    }
    else if(event->key() == Qt::Key_K){
        ui->mtaiko_right->setPixmap(QPixmap(""));
    }
    else
        return;
    ui->judgement->setPixmap(QPixmap(""));
    ui->explosion->setPixmap(QPixmap(""));
}

void Game::on_Auto_clicked()
{
    if (!autoPress){
        autoPress = true;
        connect(timer, SIGNAL(timeout()), this, SLOT(auto_play()));
    }
    else{
        autoPress = false;
        disconnect(timer, SIGNAL(timeout()), this, SLOT(auto_play()));
    }
}

void Game::auto_play()
{
    if (recentDrum == NULL) return;
    if (recentDrum->x() > 15 && recentDrum->x() <= 25){
        if (recentDrum->whatsThis() == "drum_red_small"){
            QKeyEvent* event1 = new QKeyEvent(QEvent::KeyPress, Qt::Key_F, Qt::NoModifier);
            QKeyEvent* event2 = new QKeyEvent(QEvent::KeyRelease, Qt::Key_F, Qt::NoModifier);
            qApp->postEvent((QObject*)this,(QEvent *)event1);
            qApp->postEvent((QObject*)this,(QEvent *)event2);
        }
        else if (recentDrum->whatsThis() == "drum_red_big"){
            QKeyEvent* event1 = new QKeyEvent(QEvent::KeyPress, Qt::Key_J, Qt::NoModifier);
            QKeyEvent* event2 = new QKeyEvent(QEvent::KeyRelease, Qt::Key_J, Qt::NoModifier);
            qApp->postEvent((QObject*)this,(QEvent *)event1);
            qApp->postEvent((QObject*)this,(QEvent *)event2);
        }
        else if (recentDrum->whatsThis() == "drum_blue_small"){
            QKeyEvent* event1 = new QKeyEvent(QEvent::KeyPress, Qt::Key_D, Qt::NoModifier);
            QKeyEvent* event2 = new QKeyEvent(QEvent::KeyRelease, Qt::Key_D, Qt::NoModifier);
            qApp->postEvent((QObject*)this,(QEvent *)event1);
            qApp->postEvent((QObject*)this,(QEvent *)event2);
        }
        else if (recentDrum->whatsThis() == "drum_blue_big"){
            QKeyEvent* event1 = new QKeyEvent(QEvent::KeyPress, Qt::Key_K, Qt::NoModifier);
            QKeyEvent* event2 = new QKeyEvent(QEvent::KeyRelease, Qt::Key_K, Qt::NoModifier);
            qApp->postEvent((QObject*)this,(QEvent *)event1);
            qApp->postEvent((QObject*)this,(QEvent *)event2);
        }
    }
}

void Game::on_restart_clicked()
{
    startGame();
}

void Game::on_exit_clicked()
{
    timer->stop();
    this->close();
}
