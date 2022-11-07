#ifndef TRAPSENSOR_H
#define TRAPSENSOR_H

#include <QGraphicsRectItem>
#include <QObject>

class TrapSensor : public QObject, public QGraphicsRectItem{
    Q_OBJECT

public:
    TrapSensor();
    void setObj(int xOrigin, int yOrigin);

public slots:
    void emitSignal();

signals:
    void playerIsNear();
    void playerIsNotNear();
};

#endif // TRAPSENSOR_H
