#include "Bullet.h"
#include "BlockObj.h"
#include "Entity.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QPainter>

Bullet::Bullet(){
    setRect(0, 0, 10, 10);

    QTimer * timer = new QTimer();

    connect(timer, SIGNAL(timeout()), this, SLOT(moveBullet()));

    timer->start(30);

}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(QImage(":/image/GameImage/Projectile.png"));
    painter->fillRect(rect, brush);
}

void Bullet::shootBullet(int& direction){
    this->direction = direction;
}

bool Bullet::checkCollision(const type_info& collideObject){

    if(collideObject == typeid(NormalBlock)
            || collideObject == typeid(BreakableBlock)
            || collideObject == typeid(SpringBlock)
            || collideObject == typeid(MoveBlock)
            || collideObject == typeid(SpikeBlock)
            || collideObject == typeid(FlameBlock)){
        return true;
    }
    return false;
}

void Bullet::moveBullet(){

    // move bullet and update range
    setPos(x() + 10 * direction, y());
    range += 10;

    // check if colided with block
    // delete bullet
    QList<QGraphicsItem *> collisionItems = collidingItems();
    for(int i = 0, n = collisionItems.size(); i < n; ++i){
        if(checkCollision(typeid(*(collisionItems[i]))) == true){
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    // if bullet traveled more than range
    // delete bullet
    if(range > 1300){
        scene()->removeItem(this);
        delete this;
        return;
    }
}

PlayerBullet::PlayerBullet(){
    QTimer * timer = new QTimer();

    // constantly check if kill enemy
    connect(timer, SIGNAL(timeout()), this, SLOT(killEnemy()));

    timer->start(30);
}

bool PlayerBullet::intersectWithEnemy(const type_info &collideObject){

    if(collideObject == typeid(NormalEnemy)
            || collideObject == typeid(JumpEnemy)
            || collideObject == typeid(ShootEnemy)){
        return true;
    }
    return false;
}

void PlayerBullet::killEnemy(){

    // if bullet collides with enemy
    // delete both
    QList<QGraphicsItem *> collisionItems = collidingItems();
    for(int i = 0, n = collisionItems.size(); i < n; ++i){
        if(intersectWithEnemy(typeid(*(collisionItems[i]))) == true){
            scene()->removeItem(collisionItems[i]);
            scene()->removeItem(this);
            delete collisionItems[i];
            delete this;
            return;
        }
    }
}

