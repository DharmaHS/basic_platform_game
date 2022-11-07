#ifndef BLOCKOBJ_H
#define BLOCKOBJ_H

#include "TrapSensor.h"
#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>

class BlockObj : public QObject, public QGraphicsRectItem{

public:
    BlockObj();
    void setObj(int xOrigin, int yOrigin);
};

class NormalBlock : public BlockObj{
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

class BreakableBlock : public BlockObj{
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

class SpringBlock : public BlockObj{
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

// only goes up and down
class MoveBlock : public BlockObj{
    Q_OBJECT

protected:
    int direction = -1;
    // 1 = down
    // -1 = up
    QTimer * moveTimer;
    QTimer * directionTimer;

public:
    MoveBlock();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void stopTimer();

public slots:
    void move();
    void changeDirection();

};

// does nothing
class SpikeBlock : public BlockObj{
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

// shoot flame object periodically
class FlameBlock : public BlockObj{
    Q_OBJECT

protected:
    bool haveSensor = false;
    bool switchOn = false;
    TrapSensor * mySensor;

public:
    FlameBlock();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

public slots:
    void checkSensor();
    void turnOnFlame();
    void turnOffFlame();
    void shootFlame();

};

// apears and despawns
class Flame : public BlockObj{
    Q_OBJECT

public:
    Flame();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

public slots:
    void despawnFlame();
};

// does nothing.
class GoalBlock : public BlockObj{
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // BLOCKOBJ_H
