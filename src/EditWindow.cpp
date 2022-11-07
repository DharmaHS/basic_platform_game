#include "EditWindow.h"
#include "ui_EditWindow.h"
#include "MapData.h"
#include "Game.h"
#include "Entity.h"
#include "BlockObj.h"
#include <QGraphicsScene>
#include <QScrollBar>
#include <QMessageBox>
#include <QDebug>

EditWindow::EditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditWindow)
{
    ui->setupUi(this);

    connect(ui->buttonUp, SIGNAL(released()), this, SLOT(pointerUp()));
    connect(ui->buttonDown, SIGNAL(released()), this, SLOT(pointerDown()));
    connect(ui->buttonLeft, SIGNAL(released()), this, SLOT(pointerLeft()));
    connect(ui->buttonRight, SIGNAL(released()), this, SLOT(pointerRight()));
    connect(ui->buttonEdit, SIGNAL(released()), this, SLOT(editBlock()));
    connect(ui->buttonSave, SIGNAL(released()), this, SLOT(saveMap()));
}

EditWindow::~EditWindow(){
    delete ui;
}

void EditWindow::setFileName(QString inputName){
    fileName = inputName;
}

void EditWindow::startEditor(){
    // read in map from file name
    myMap = new MapData();
    myMap->readMap(fileName);

    // initialize game in edit mode (stop visual timer)
    myGame = new Game();
    myGame->startEditMode();
    myGame->drawMap(myMap->getMap());

    // place pointer rect
    w = 0;
    h = 0;
    pointerRect = new QGraphicsRectItem;
    pointerRect->setRect(5, 5, 20, 20);
    myGame->scene->addItem(pointerRect);

    ui->graphicsView->setScene(myGame->scene);
    ui->graphicsView->show();
}

void EditWindow::pointerUp(){
    if(h >= 0 && h < HEIGHT - 1){
        h -= 1;
    }
    pointerRect->setPos(w * 30, h * 30);
}

void EditWindow::pointerDown(){
    if(h >= 0 && h < HEIGHT - 1){
        h += 1;
    }
    pointerRect->setPos(w * 30, h * 30);
}

void EditWindow::pointerLeft(){
    if(w >= 0 && w < WIDTH - 1){
        w -= 1;
    }
    pointerRect->setPos(w * 30, h * 30);
}

void EditWindow::pointerRight(){
    if(w >= 0 && w < WIDTH - 1){
        w += 1;
    }
    pointerRect->setPos(w * 30, h * 30);
}

void EditWindow::editBlock(){
    // check if input is valid
    // delete original block
    // add in new block
    // change value of map data in StringList of MapData

    QList<QGraphicsItem *> collisionItems = pointerRect->collidingItems();
    for(int i = 0, n = collisionItems.size(); i < n; ++i){
        myGame->scene->removeItem(collisionItems[i]);
        delete collisionItems[i];
    }

    int blockVal;
    QString temp;
    QRegExp re("\\d*");

    // check if inputs is a number
    // return error msg if not
    temp = ui->textEdit->toPlainText();
    if (re.exactMatch(temp) == false){
        QMessageBox::critical(this, "Invalid input!", "Please input a valid number!");
        return;
    }

    blockVal = temp.toInt();
    if(blockVal < 0 || blockVal > 12){
        QMessageBox::critical(this, "Invalid input!", "Please input a valid number!");
        return;
    }

    switch(blockVal){
    case 0:{
        break;
    }
    case 1:{
        NormalEnemy * block = new NormalEnemy();
        block->setObj(w, h);
        myGame->scene->addItem(block);
        block->stopTimer();
        break;
    }
    case 2:{
        JumpEnemy * block = new JumpEnemy();
        block->setObj(w, h);
        myGame->scene->addItem(block);
            block->stopTimer();
        break;
    }
    case 3:{
        ShootEnemy * block = new ShootEnemy();
        block->setObj(w, h);
        myGame->scene->addItem(block);
            block->stopTimer();
        break;
    }
    case 4:{
        Mushroom * block = new Mushroom();
        block->setObj(w, h);
        myGame->scene->addItem(block);
        break;
    }
    case 5:{
        Flower * block = new Flower();
        block->setObj(w, h);
        myGame->scene->addItem(block);
        break;
    }
    case 6:{
        NormalBlock * Block = new NormalBlock();
        Block->setObj(w, h);
        myGame->scene->addItem(Block);
        break;
    }
    case 7:{
        BreakableBlock * block = new BreakableBlock();
        block->setObj(w, h);
        myGame->scene->addItem(block);
        break;
    }
    case 8:{
        SpringBlock * block = new SpringBlock();
        block->setObj(w, h);
        myGame->scene->addItem(block);
        break;
    }
    case 9:{
        MoveBlock * block = new MoveBlock();
        block->setObj(w, h);
        myGame->scene->addItem(block);
            block->stopTimer();
        break;
    }
    case 10:{
        SpikeBlock * block = new SpikeBlock();
        block->setObj(w, h);
        myGame->scene->addItem(block);
        break;
    }
    case 11:{
        FlameBlock * block = new FlameBlock();
        block->setObj(w, h);
        myGame->scene->addItem(block);
        break;
    }
    case 12:{
        GoalBlock * block = new GoalBlock();
        block->setObj(w, h);
        myGame->scene->addItem(block);
        break;
    }
    }

    myMap->list.replace(h * 120 + w, QString::number(blockVal));
}

void EditWindow::saveMap(){
    myMap->saveMap(fileName);
}
