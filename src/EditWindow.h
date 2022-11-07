#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include "Game.h"
#include "MapData.h"
#include <QDialog>
#include <QGraphicsRectItem>

namespace Ui {
class EditWindow;
}

class EditWindow : public QDialog
{
    Q_OBJECT

protected:
    const static int WIDTH = 120;
    const static int HEIGHT = 12;
    int w;
    int h;

    Game * myGame;
    MapData * myMap;
    QGraphicsRectItem * pointerRect;
    QString fileName;

public:
    explicit EditWindow(QWidget *parent = nullptr);
    ~EditWindow();
    void setFileName(QString inputName);
    void startEditor();

public slots:
    void pointerUp();
    void pointerDown();
    void pointerLeft();
    void pointerRight();
    void editBlock();
    void saveMap();

private:
    Ui::EditWindow *ui;

};

#endif // EDITWINDOW_H
