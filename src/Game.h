#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include "Player.h"
#include "Score.h"

class Game : public QGraphicsView{
    Q_OBJECT

public:
    QGraphicsScene * scene;

protected:
    const static int HEIGHT = 12;
    const static int WIDTH = 120;
    Player * myPlayer;
    Score * myScore;
    bool editMode = false;

public:
    Game();
    void drawMap(int ** mapArr);
    void startGame();

    // disables player
    // hides score
    // set flag to stop timer
    // for moving entity
    void startEditMode();

public slots:
    void moveScreen();
    void gameOverScreen();
    void winGameScreen();
};

#endif // GAME_H
