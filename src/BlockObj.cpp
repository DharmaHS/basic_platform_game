#include "BlockObj.h"
#include "TrapSensor.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QPainter>
#include <QPixmap>
#include <QImage>

BlockObj::BlockObj(){

}

// set objects as 30 by 30 blocks and follow grid
void BlockObj::setObj(int xOrigin, int yOrigin){

    setRect(xOrigin * 30, yOrigin * 30, 30, 30);
}

void NormalBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(QImage(":/image/GameImage/NormalBlock.png"));
    painter->fillRect(rect, brush);
}

void BreakableBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(QImage(":/image/GameImage/BreakableBlock.png"));
    painter->fillRect(rect, brush);
}

void SpringBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(QImage(":/image/GameImage/SpringBlock.png"));
    painter->fillRect(rect, brush);
}

MoveBlock::MoveBlock(){

    moveTimer = new QTimer();
    directionTimer = new QTimer();
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    connect(directionTimer, SIGNAL(timeout()), this, SLOT(changeDirection()));

    moveTimer->start(30);
    directionTimer->start(2000);
}

void MoveBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(QImage(":/image/GameImage/MoveBlock.png"));
    painter->fillRect(rect, brush);
}

void MoveBlock::stopTimer(){
    moveTimer->stop();
    directionTimer->stop();
}

void MoveBlock::move(){
    setPos(x(), y() + direction * 2);
}

void MoveBlock::changeDirection(){
    if(direction == 1){
        direction = -1;
    }
    else {
        direction = 1;
    }
}

void SpikeBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(QImage(":/image/GameImage/SpikeBlock.png"));
    painter->fillRect(rect, brush);
}

FlameBlock::FlameBlock(){

    QTimer * flameTimer = new QTimer();
    QTimer * playerTimer = new QTimer();    
    connect(flameTimer, SIGNAL(timeout()), this, SLOT(shootFlame()));
    connect(playerTimer, SIGNAL(timeout()), this, SLOT(checkSensor()));

    flameTimer->start(3000);
    playerTimer->start(30);
}

void FlameBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(QImage(":/image/GameImage/FlameBlock.png"));
    painter->fillRect(rect, brush);
}

// create a sensor if no sensor exist, and constantly check sensor
void FlameBlock::checkSensor(){

    if(haveSensor == false){
        mySensor = new TrapSensor();
        mySensor->setObj(boundingRect().left() - 5 * 30, boundingRect().top() - 5 * 30);
        scene()->addItem(mySensor);
        haveSensor = true;
    }

    connect(mySensor, SIGNAL(playerIsNear()), this, SLOT(turnOnFlame()));
    connect(mySensor, SIGNAL(playerIsNotNear()), this, SLOT(turnOffFlame()));
}

void FlameBlock::turnOnFlame(){
    switchOn = true;
}

void FlameBlock::turnOffFlame(){
    switchOn = false;
}

void FlameBlock::shootFlame(){
    if(switchOn == true){
        Flame * flameBlock1 = new Flame();
        Flame * flameBlock2 = new Flame();
        flameBlock1->setObj(boundingRect().left() / 30 + 1, (boundingRect().top() - 30) / 30);
        flameBlock2->setObj(boundingRect().left() / 30 + 1, (boundingRect().top()) / 30);

        scene()->addItem(flameBlock1);
        scene()->addItem(flameBlock2);
    }

}

// Flames despawn after a while
Flame::Flame(){
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(despawnFlame()));

    timer->start(1500);
}

void Flame::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(QImage(":/image/GameImage/Flame.png"));
    painter->fillRect(rect, brush);
}

void Flame::despawnFlame(){
    scene()->removeItem(this);
    delete this;
    return;
}

void GoalBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(QImage(":/image/GameImage/GoalBlock.png"));
    painter->fillRect(rect, brush);
}
