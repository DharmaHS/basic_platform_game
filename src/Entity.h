#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsRectItem>
#include <QTimer>

// Entity will be reponsible for gravity related things
class Entity : public QObject, public QGraphicsRectItem{
    Q_OBJECT

protected:
    const float gravityAccel = 1;
    float yVel = 0;
    bool isTouchingGround = true;

public:
    Entity();
    void setObj(int xOrigin, int yOrigin);
    bool intersectWithBlock(const type_info& collideObject);

public slots:
    void updateGround();
    void gravityPull();

};

// normal enemy move horizontally in static speed
class NormalEnemy : public Entity{
    Q_OBJECT

protected:
    int direction = -1;
    QTimer * timer;

public:
    NormalEnemy();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void stopTimer();

public slots:
    void move();

};

// jump enemy jumps periodically
class JumpEnemy : public Entity{
    Q_OBJECT

protected:
    QTimer * timer;

public:
    JumpEnemy();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void stopTimer();
public slots:
    void jump();

};

// shoot enemy moves left and right
class ShootEnemy : public Entity{
    Q_OBJECT

protected:
    int direction = -1;
    QTimer * moveTimer;
    QTimer * changeTimer;
    QTimer * shootTimer;

public:
    ShootEnemy();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void stopTimer();

public slots:
    void move();
    void changeDirection();
    void shoot();
};

class Mushroom : public Entity{
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

};

class Flower : public Entity{
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // ENTITY_H
