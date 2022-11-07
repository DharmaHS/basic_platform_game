#include "Entity.h"
#include "BlockObj.h"
#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QPainter>

Entity::Entity(){

    QTimer * entityTimer = new QTimer();
    connect(entityTimer, SIGNAL(timeout()), this, SLOT(updateGround()));
    connect(entityTimer, SIGNAL(timeout()), this, SLOT(gravityPull()));

    entityTimer->start(30);

}

// set objects as 30 by 30 blocks and follow grid
void Entity::setObj(int xOrigin, int yOrigin){

    setRect(xOrigin * 30, yOrigin * 30, 30, 30);
}

bool Entity::intersectWithBlock(const type_info& collideObject){

    if(collideObject == typeid(NormalBlock)
            || collideObject == typeid(BreakableBlock)
            || collideObject == typeid(SpringBlock)
            || collideObject == typeid(MoveBlock)
            || collideObject == typeid(FlameBlock)){
        return true;
    }
    return false;
}

void Entity::updateGround(){
    isTouchingGround = false;
    return;
}

void Entity::gravityPull(){

    // if is touching the ground, don't apply gravity
    if(isTouchingGround == true){
        return;
    }   // if not touching the ground, accelerate downwards
    else if(isTouchingGround == false){
        yVel += gravityAccel;
    }

    // set terminal velocity of falling
    if(yVel > +15){
        yVel = 15;
    }

    // update y position
    setPos(x(), y() + yVel);

    // ground collision
    QList<QGraphicsItem *> collisionItems = collidingItems();
    for(int i = 0, n = collisionItems.size(); i < n; ++i){
        if(intersectWithBlock(typeid(*(collisionItems[i]))) == true){
            if(scenePos().y() + 30 + boundingRect().bottom() > collisionItems[i]->boundingRect().top()){
                yVel = 0;
                setPos(x(), collisionItems[i]->boundingRect().bottom() - boundingRect().bottom() - 30);
                isTouchingGround = true;
            }
        }
    }
}

NormalEnemy::NormalEnemy(){

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(30);
}

void NormalEnemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(QImage(":/image/GameImage/NormalEnemy.png"));
    painter->fillRect(rect, brush);
}

void NormalEnemy::stopTimer(){
    timer->stop();
}



void NormalEnemy::move(){
    setPos(x() + direction * 3, y());

    // bounce right if hit wall on left
    QList<QGraphicsItem *> collisionItems = collidingItems();
    for(int i = 0, n = collisionItems.size(); i < n; ++i){
        if(intersectWithBlock(typeid(*(collisionItems[i]))) == true){
            if(direction == -1 && scenePos().x() + boundingRect().left() < collisionItems[i]->boundingRect().right()
                    && scenePos().y() + boundingRect().bottom() - 1 > collisionItems[i]->boundingRect().top()
                    ){
                direction = 1;
                setPos(x() + 5, y());
            }
        }
    }

    // bounce left if hit wall on right
    collisionItems = collidingItems();
    for(int i = 0, n = collisionItems.size(); i < n; ++i){
        if(intersectWithBlock(typeid(*(collisionItems[i]))) == true){
            if(direction == 1 && scenePos().x() + 30 + boundingRect().right() > collisionItems[i]->boundingRect().left()
                    && scenePos().y() + boundingRect().bottom() - 1 > collisionItems[i]->boundingRect().top()
                    ){
                direction = -1;
                setPos(x() - 5, y());
            }
        }
    }
}


JumpEnemy::JumpEnemy(){
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(jump()));

    timer->start(2000);
}

void JumpEnemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(QImage(":/image/GameImage/JumpEnemy.png"));
    painter->fillRect(rect, brush);
}

void JumpEnemy::jump(){
    setPos(x(), y() - 10);
    yVel = - 15;
}

void JumpEnemy::stopTimer(){
    timer->stop();
}

ShootEnemy::ShootEnemy(){
    moveTimer = new QTimer();
    changeTimer = new QTimer();
    shootTimer = new QTimer();
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    connect(changeTimer, SIGNAL(timeout()), this, SLOT(changeDirection()));
    connect(shootTimer, SIGNAL(timeout()), this, SLOT(shoot()));

    moveTimer->start(30);
    changeTimer->start(1200);
    shootTimer->start(2000);

}

void ShootEnemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(QImage(":/image/GameImage/ShootEnemy.png"));
    painter->fillRect(rect, brush);
}

void ShootEnemy::stopTimer(){
    moveTimer->stop();
    changeTimer->stop();
    shootTimer->stop();
}

void ShootEnemy::move(){
    setPos(x() + direction * 2, y());
}

void ShootEnemy::changeDirection(){
    if(direction == 1){
        direction = -1;
    }
    else {
        direction = 1;
    }
}

void ShootEnemy::shoot(){
    EnemyBullet * myBullet = new EnemyBullet();
    myBullet->shootBullet(direction);
    myBullet->setPos(scenePos().x() + boundingRect().left() + 10, scenePos().y() + boundingRect().top() + 10);
    scene()->addItem(myBullet);
}

void Mushroom::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(QImage(":/image/GameImage/Mushroom.png"));
    painter->fillRect(rect, brush);
}

void Flower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(QImage(":/image/GameImage/Flower.png"));
    painter->fillRect(rect, brush);
}
