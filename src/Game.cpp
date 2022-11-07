#include "Game.h"
#include "BlockObj.h"
#include "Entity.h"
#include <vector>
#include <QTimer>
#include <QMessageBox>
#include <QScrollBar>

// Player must spawn at 0, 0

Game::Game(){
    // create a scene and spawn player
    scene = new QGraphicsScene();
    myPlayer = new Player();
    myPlayer->setObj(0, 0);
    scene->addItem(myPlayer);
    myPlayer->setFlag(QGraphicsItem::ItemIsFocusable);
    myPlayer->setFocus();

    // score related connections
    myScore = new Score();
    scene->addItem(myScore);
    QTimer * gameTimer = new QTimer();
    QTimer * tickTimer = new QTimer();
    connect(gameTimer, SIGNAL(timeout()), myScore, SLOT(increaseTime()));
    connect(tickTimer, SIGNAL(timeout()), this, SLOT(moveScreen()));
    connect(myPlayer, SIGNAL(increaseScore()), myScore, SLOT(increaseScore()));
    connect(myPlayer, SIGNAL(gameOver()), this, SLOT(gameOverScreen()));
    connect(myPlayer, SIGNAL(winGame()), this, SLOT(winGameScreen()));

    gameTimer->start(1000);
    tickTimer->start(30);
}

void Game::drawMap(int **mapArr){

    /*
    map data stored as 2D array
    0 = empty space
    1 = NormalEnemy
    2 = JumpingEnemy
    3 = ShootingEnemy
    4 = Mushroom
    5 = Flower
    6 = NormalBlock
    7 = BreakableBlock
    8 = SpringBlock
    9 = MoveBlock
    10 = SpikeBlock
    11 = FlameBlock
    12 = GoalBlock
    */

    for(int h = 0; h < HEIGHT; ++h) {

        for(int w = 0; w < 120; ++w){

            switch(mapArr[h][w]){
            case 0:{
                continue;
                }
            case 1:{
                NormalEnemy * block = new NormalEnemy();
                block->setObj(w, h);
                scene->addItem(block);
                if(editMode == true){
                    block->stopTimer();
                }
                break;
            }
            case 2:{
                JumpEnemy * block = new JumpEnemy();
                block->setObj(w, h);
                scene->addItem(block);
                if(editMode == true){
                    block->stopTimer();
                }
                break;
            }
            case 3:{
                ShootEnemy * block = new ShootEnemy();
                block->setObj(w, h);
                scene->addItem(block);
                if(editMode == true){
                    block->stopTimer();
                }
                break;
            }
            case 4:{
                Mushroom * block = new Mushroom();
                block->setObj(w, h);
                scene->addItem(block);
                break;
            }
            case 5:{
                Flower * block = new Flower();
                block->setObj(w, h);
                scene->addItem(block);
                break;
            }
            case 6:{
                NormalBlock * Block = new NormalBlock();
                Block->setObj(w, h);
                scene->addItem(Block);
                break;
            }
            case 7:{
                BreakableBlock * block = new BreakableBlock();
                block->setObj(w, h);
                scene->addItem(block);
                break;
            }
            case 8:{
                SpringBlock * block = new SpringBlock();
                block->setObj(w, h);
                scene->addItem(block);
                break;
            }
            case 9:{
                MoveBlock * block = new MoveBlock();
                block->setObj(w, h);
                scene->addItem(block);
                if(editMode == true){
                    block->stopTimer();
                }
                break;
            }
            case 10:{
                SpikeBlock * block = new SpikeBlock();
                block->setObj(w, h);
                scene->addItem(block);
                break;
            }
            case 11:{
                FlameBlock * block = new FlameBlock();
                block->setObj(w, h);
                scene->addItem(block);
                break;
            }
            case 12:{
                GoalBlock * block = new GoalBlock();
                block->setObj(w, h);
                scene->addItem(block);
                break;
            }
            }
        }
    }
}

void Game::startGame(){

    // set scene in view
    setScene(scene);
    resize(1280,720);

    // lock scrollbar
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Game::startEditMode(){
    editMode = true;
    myPlayer->clearFocus();
    scene->removeItem(myScore);
}

void Game::moveScreen(){
    if(myPlayer->x() > 120 && myPlayer->x() < 82 * 30){
        myScore->setPos(myPlayer->x() - 120, myScore->y());
    }

    horizontalScrollBar()->setValue(myPlayer->x() - 120);
}

// game over screen using message box
void Game::gameOverScreen(){

    hide();
    QString gameOverMsg = QString("GAME OVER!, Your score is: ") + QString::number(myScore->getScore())
            + QString(" You played for: ") + QString::number(myScore->getPlayTime()) + QString(" seconds.");
    QMessageBox::critical(this, "GAME OVER!", gameOverMsg);
    delete this;
    return;
}

void Game::winGameScreen(){
    hide();
    QString gameOverMsg = QString("CONGRADULATIONS! Your score is: ") + QString::number(myScore->getScore())
            + QString(" You played for: ") + QString::number(myScore->getPlayTime()) + QString(" seconds.");
    QMessageBox::information(this, "COMPLETE!", gameOverMsg);
    delete this;
    return;
}
