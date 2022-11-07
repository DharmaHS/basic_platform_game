#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsRectItem>
#include <QObject>

class Bullet : public QObject, public QGraphicsRectItem{
    Q_OBJECT

protected:
    int direction;
    int range = 0;

public:
    Bullet();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void shootBullet(int& direction);
    bool checkCollision(const type_info& collideObject);

public slots:
    void moveBullet();
};

class PlayerBullet : public Bullet{
    Q_OBJECT

public:
    PlayerBullet();
    bool intersectWithEnemy(const type_info& collideObject);

public slots:
    void killEnemy();
};

class EnemyBullet : public Bullet{

};

#endif // BULLET_H
