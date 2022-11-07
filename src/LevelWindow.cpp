#include "LevelWindow.h"
#include "ui_LevelWindow.h"
#include "MapData.h"
#include "Game.h"
#include "EditWindow.h"

LevelWindow::LevelWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LevelWindow)
{
    ui->setupUi(this);

    connect(ui->buttonEdit1, SIGNAL(released()), this, SLOT(editLevel1()));
    connect(ui->buttonPlay1, SIGNAL(released()), this, SLOT(playLevel1()));
    connect(ui->buttonEdit2, SIGNAL(released()), this, SLOT(editLevel2()));
    connect(ui->buttonPlay2, SIGNAL(released()), this, SLOT(playLevel2()));
    connect(ui->buttonBack, SIGNAL(released()), this, SLOT(close()));
}

LevelWindow::~LevelWindow(){
    delete ui;
}
//E:/School/2019-2020(2)/SummerClass/GameProject/PlatformGame/LevelFile

void LevelWindow::editLevel1(){
    EditWindow edWindow;
    edWindow.setFileName("C:/LevelFile/customLevel1.txt");
    edWindow.startEditor();
    edWindow.setModal(true);
    edWindow.exec();
}

void LevelWindow::playLevel1(){
    QString fileName = "C:/LevelFile/customLevel1.txt";
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

void LevelWindow::editLevel2(){
    EditWindow edWindow;
    edWindow.setFileName("C:/LevelFile/customLevel2.txt");
    edWindow.startEditor();
    edWindow.setModal(true);
    edWindow.exec();
}

void LevelWindow::playLevel2(){
    QString fileName = "C:/LevelFile/customLevel2.txt";
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
