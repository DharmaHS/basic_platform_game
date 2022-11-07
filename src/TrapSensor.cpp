#include "TrapSensor.h"
#include "Player.h"
#include <QTimer>


TrapSensor::TrapSensor(){
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(emitSignal()));

    timer->start(30);
}

void TrapSensor::setObj(int xOrigin, int yOrigin){
    setRect(xOrigin, yOrigin, 330, 330);

}

void TrapSensor::emitSignal(){
    // if player intersects with sensor box, emit near
    // else emit not near
    QList<QGraphicsItem *> collisionItems = collidingItems();
    for(int i = 0, n = collisionItems.size(); i < n; ++i){
        if((typeid(*(collisionItems[i])) == typeid(Player))){
            emit playerIsNear();
            return;
        }
    }
    emit playerIsNotNear();
}
