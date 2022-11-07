#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsSimpleTextItem>

class Score : public QGraphicsTextItem{
    Q_OBJECT

private:
    int playerScore;
    int playTime;

public:
    Score(QGraphicsItem * parent = nullptr);
    int getScore();
    int getPlayTime();

public slots:
    void increaseScore();
    void increaseTime();
};

#endif // SCORE_H
