#include "Player.h"
#include "BlockObj.h"
#include "Entity.h"
#include "Bullet.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>

Player::Player(){

    QTimer * timer = new QTimer;

    connect(timer, SIGNAL(timeout()), this, SLOT(updateGround()));
    connect(timer, SIGNAL(timeout()), this, SLOT(gravityPull()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateVelocity()));
    connect(timer, SIGNAL(timeout()), this, SLOT(checkCollision()));
    connect(timer, SIGNAL(timeout()), this, SLOT(entityInteraction()));


    timer->start(30);
}

void Player::setObj(int xOrigin, int yOrigin){
    setRect(xOrigin * 30, yOrigin * 30, 30, 30);

}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QRectF rect = boundingRect();
    QBrush brush(QImage(":/image/GameImage/Player1.png"));
    if(state == 0){
        brush.setTextureImage(QImage(":/image/GameImage/Player1.png"));
    }
    if(state == 1){
        brush.setTextureImage(QImage(":/image/GameImage/Player2.png"));
    }
    if(state == 2){
        brush.setTextureImage(QImage(":/image/GameImage/Player3.png"));
    }
    painter->fillRect(rect, brush);
}

void Player::keyPressEvent(QKeyEvent * event){

    if(event->key() == Qt::Key_Left){
        movePlayer(-10);
        facingDirection = -1;
    }
    if(event->key() == Qt::Key_Right){
        movePlayer(10);
        facingDirection = 1;
    }
    if(event->key() == Qt::Key_Up){
        jump();
    }
    if(event->key() == Qt::Key_Space){
        if(this->state == 2){
            PlayerBullet * myBullet = new PlayerBullet();
            myBullet->shootBullet(facingDirection);
            myBullet->setPos(x() + 10, y() + 10);
            scene()->addItem(myBullet);
        }

    }

}

void Player::movePlayer(int direction){
    xVel += direction;
}

void Player::jump(){

    if(isTouchingGround == true){
    setPos(x(), y() - 30);
    yVel -= jumpAccel;
    }

    return;
}

bool Player::intersectWithBlock(const type_info& collideObject){

    if(collideObject == typeid(NormalBlock)
            || collideObject == typeid(BreakableBlock)
            || collideObject == typeid(SpringBlock)
            || collideObject == typeid(MoveBlock)
            || collideObject == typeid(FlameBlock)){
        return true;
    }
    return false;
}

bool Player::intersectWithEnemy(const type_info& collideObject){

    if(collideObject == typeid(NormalEnemy)
            || collideObject == typeid(JumpEnemy)
            || collideObject == typeid(ShootEnemy)){
        return true;
    }
    return false;
}

void Player::takeDamage(){
    // if player is small
    // die
    if(this->state == 0){
        scene()->removeItem(this);
        emit gameOver();
        delete this;
        return;
    }

    // if player is not small
    // change state and bounce them off
    if(this->state == 1 || this->state == 2){
        this->state -= 1;
        yVel = 0;
        if(facingDirection == 1){
            setPos(x() - 30, y());
            xVel = -5;
        }
        else if(facingDirection == -1){
            setPos(x() + 30, y());
            xVel = 5;
        }
    }

    updateState();
}

void Player::updateState(){
    // TODO: change character sprite
    //update();
}

void Player::updateGround(){
    isTouchingGround = false;
    return;
}

void Player::gravityPull(){

    // if is touching the ground, don't apply gravity
    if(isTouchingGround == true){
        return;
    }   // if not touching the ground, accelerate downwards
    else if(isTouchingGround == false){
        yVel += gravityAccel;
    }
}

void Player::updateVelocity(){

    // limit terminal velocity
    if(yVel > 15){
        yVel = 15;
    }
    if(yVel < -25){
        yVel = -25;
    }
    if(xVel > 10){
        xVel = 10;
    }
    if(xVel < -10){
        xVel = -10;
    }

    // horizontal momentum
    if(xVel > 0){
        xVel -= 0.5;
    }
    if(xVel < 0){
        xVel += 0.5;
    }

}

void Player::checkCollision(){

    setPos(x() + xVel, y());
    // if moving right
    // and collides with a block's left
    // push player left
    if(xVel > 0){
        QList<QGraphicsItem *> collisionItems = collidingItems();
        for(int i = 0, n = collisionItems.size(); i < n; ++i){
            if(intersectWithBlock(typeid(*(collisionItems[i]))) == true){
                if(x() + 30 > collisionItems[i]->boundingRect().left()
                        && x() + 30 < collisionItems[i]->boundingRect().left() + 10
                        && y() >= collisionItems[i]->boundingRect().top()){
                    xVel = 0;
                    setPos(collisionItems[i]->boundingRect().left() - 30 - 1, y());
                }
            }
        }
    }

    // if moving left
    // and collides with a block's right
    // push player right
    if(xVel < 0){
        QList<QGraphicsItem *> collisionItems = collidingItems();
        for(int i = 0, n = collisionItems.size(); i < n; ++i){
            if(intersectWithBlock(typeid(*(collisionItems[i]))) == true){
                if(x() < collisionItems[i]->boundingRect().right()
                        && x() > collisionItems[i]->boundingRect().right() - 10
                        && y() >= collisionItems[i]->boundingRect().top()
                        ){
                    xVel = 0;
                    setPos(collisionItems[i]->boundingRect().right() + 2, y());
                }
            }
        }
    }

    setPos(x(), y() + yVel);

    // need to check spring block
    // before collision of normal block
    // jump high if land on it
    if(yVel > 0){
        QList<QGraphicsItem *> collisionItems = collidingItems();
        for(int i = 0, n = collisionItems.size(); i < n; ++i){
            if(typeid(*(collisionItems[i])) == typeid(SpringBlock)){
                if(y() + 30 > collisionItems[i]->boundingRect().top()
                        && y() + 30 < collisionItems[i]->boundingRect().top() + 30){
                    yVel = -25;
                    setPos(x(), collisionItems[i]->boundingRect().top() - 60);
                }
            }
        }
    }

    // if moving down (falling)
    // and collides with a block's top
    // push player up (land)
    if(yVel >= 0){
        QList<QGraphicsItem *> collisionItems = collidingItems();
        for(int i = 0, n = collisionItems.size(); i < n; ++i){
            if(intersectWithBlock(typeid(*(collisionItems[i]))) == true){
                if(y() + 30 > collisionItems[i]->boundingRect().top() + + collisionItems[i]->y()
                        && y() + 30 < collisionItems[i]->boundingRect().top() + collisionItems[i]->y() + 30){
                    yVel = 0;
                    isTouchingGround = true;
                    setPos(x(), collisionItems[i]->boundingRect().top() + collisionItems[i]->y() - 30);
                }
            }
        }
    }

    // need to check breakable block
    // before collision of normal block
    // if state >= 1, destroy breakable block when jumping
    if(this->state >= 1 && yVel < 0){
        QList<QGraphicsItem *> collisionItems = collidingItems();
        for(int i = 0, n = collisionItems.size(); i < n; ++i){
            if(typeid(*(collisionItems[i])) == typeid(BreakableBlock)){
                yVel = 0;
                setPos(x(), collisionItems[i]->boundingRect().bottom() + 1);
                scene()->removeItem(collisionItems[i]);
                delete collisionItems[i];
                return;
            }
        }
    }

    // if moving up (jumping)
    // and collides with a block's bottom
    // push player down
    if(yVel < 0){
        QList<QGraphicsItem *> collisionItems = collidingItems();
        for(int i = 0, n = collisionItems.size(); i < n; ++i){
            if(intersectWithBlock(typeid(*(collisionItems[i]))) == true){
                if(y() < collisionItems[i]->boundingRect().bottom()
                        && y() > collisionItems[i]->boundingRect().bottom() - 30){
                    yVel = 0;
                    setPos(x(), collisionItems[i]->boundingRect().bottom() + 1);
                }
            }
        }
    }

    // die out of bound
    if(y() >= 420){
        scene()->removeItem(this);
        emit gameOver();
        delete this;
        return;
    }

}

void Player::entityInteraction(){

    QList<QGraphicsItem *> collisionItems = collidingItems();

    // if intersect with enemy
    // AND if Player is falling, destroy
    // else take damage
    for(int i = 0, n = collisionItems.size(); i < n; ++i){
        if((intersectWithEnemy(typeid(*collisionItems[i]))) == true){
            if(yVel > 0){
                scene()->removeItem(collisionItems[i]); // remove enemy from scene
                delete collisionItems[i];               // delete enemy
                setPos(x(), y() - 10);      // bounce off enemy after
                yVel = -(jumpAccel * 0.7);  // destroying them
                emit increaseScore();
                return;
            }
            else{
                takeDamage();
            }
        }
    }

    // if intersect with spike or flame
    // game over
    for(int i = 0, n = collisionItems.size(); i < n; ++i){
        if(typeid(*(collisionItems[i])) == typeid(SpikeBlock)
                || typeid(*(collisionItems[i])) == typeid(Flame)){
            scene()->removeItem(this);
            emit gameOver();
            delete this;
            return;
            }
        }


    // if intersect with enemy bullet
    // take damage
    for(int i = 0, n = collisionItems.size(); i < n; ++i){
        if(typeid(*(collisionItems[i])) == typeid(EnemyBullet)){
            scene()->removeItem(collisionItems[i]);
            delete collisionItems[i];
            takeDamage();
            return;
        }
    }

    // if intersect with item
    // change state and increase score
    for(int i = 0, n = collisionItems.size(); i < n; ++i){
        if(typeid(*(collisionItems[i])) == typeid(Mushroom)){
            if(this->state == 0){
                this->state = 1;
            }
            scene()->removeItem(collisionItems[i]);
            delete collisionItems[i];
            emit increaseScore();
            updateState();
            return;
        }

        if(typeid(*(collisionItems[i])) == typeid(Flower)){
            this->state = 2;
            scene()->removeItem(collisionItems[i]);
            delete collisionItems[i];
            emit increaseScore();
            updateState();
            return;
        }
    }

    // if intersect with goal block
    // win
    for(int i = 0, n = collisionItems.size(); i < n; ++i){
        if(typeid(*(collisionItems[i]))== typeid(GoalBlock)){
            scene()->removeItem(this);
            emit winGame();
            delete this;
            return;
        }
    }

}
