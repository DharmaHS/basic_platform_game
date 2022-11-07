#include "Score.h"
#include <QFont>

Score::Score(QGraphicsItem * parent) : QGraphicsTextItem(parent){

    // initialize score and time as 0
    playerScore = 0;
    playTime = 0;

    //draw out the score
    setPlainText(QString("Score: ") + QString::number(playerScore) + QString(" PlayTime: ") + QString::number(playTime));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times", 16));
}

int Score::getScore(){
return playerScore;
}

int Score::getPlayTime(){
 return playTime;
}

void Score::increaseScore(){
    playerScore += 10;
    setPlainText(QString("Score: ") + QString::number(playerScore) + QString(" PlayTime: ") + QString::number(playTime));
}

void Score::increaseTime(){
    playTime += 1;
    setPlainText(QString("Score: ") + QString::number(playerScore) + QString(" PlayTime: ") + QString::number(playTime));
}

