#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>

// RectItem as placeholder
#include <QGraphicsRectItem>

class Player : public QObject, public QGraphicsRectItem{
    Q_OBJECT

protected:
    const float gravityAccel = 1;
    const float jumpAccel = 15;
    const float momentum = 0.5;

    float xVel = 0;
    float yVel = 0;
    bool isTouchingGround = false;
    int facingDirection = 1;
    // 1 = facing right
    // -1 = facing left
    int state = 0;
    /*
    0 = start
    1 = extra health
    2 = shooting
    */

public:
    Player();
    void setObj (int xOrigin, int yOrigin);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void keyPressEvent(QKeyEvent * event);

protected:
    void movePlayer(int direction);
    void jump();
    bool intersectWithBlock(const type_info& collideObject);
    bool intersectWithEnemy(const type_info& collideObject);
    bool intersectWithBullet(const type_info& collideObject);
    void takeDamage();
    void updateState();

signals:
    void increaseScore();
    void gameOver();
    void winGame();

public slots:

    // constantly updating touching ground info
    void updateGround();

    // constantly apply gravity
    void gravityPull();

    // constantly reset and update movement related values
    // (e.g terminal velocity, momentum, etc.)
    void updateVelocity();

    // collision, update position
    void checkCollision();

    // take damage, get mushroom, die etc.
    void entityInteraction();

};

#endif // PLAYER_H
