#include "MenuWindow.h"
#include "ui_MenuWindow.h"
#include "LevelWindow.h"
#include "Game.h"
#include <fstream>
#include <QFile>
#include <QTextStream>

MenuWindow::MenuWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    // Play Game button
    connect(ui->buttonPlay, SIGNAL(released()), this, SLOT(startGame()));

    // Edit level button
    connect(ui->buttonEditLevel, SIGNAL(released()), this, SLOT(openEditMenu()));

    // Quit the game
    connect(ui->buttonQuit, SIGNAL(released()), this, SLOT(close()));
}

MenuWindow::~MenuWindow(){
    delete ui;
}


void MenuWindow::startGame(){
    // read array from file
    // pass array into myMap
    QString fileName = ":/level/LevelFile/defaultLevel.txt";
    MapData * myMap = new MapData();
    myMap->readMap(fileName);

    // create a new game and
    // pass map into game
    Game * myGame = new Game();
    myGame->drawMap(myMap->getMap());
    myGame->startGame();

    myGame->show();
    close();

}

// Open level edit window
void MenuWindow::openEditMenu(){

    LevelWindow lvWindow;
    lvWindow.setModal(true);
    lvWindow.exec();
    close();

}


// namespace
