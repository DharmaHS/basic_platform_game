#include "MapData.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>

MapData::MapData(){
    // initialize the array
    mapArr = new int*[HEIGHT];
    for(int h = 0; h < HEIGHT; h++){
        mapArr[h] = new int[WIDTH];
    }
}

void MapData::readMap(QString fileName){

    QFile file(fileName);
    if(! file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox msgBox;
        msgBox.setText("File not oped!");
        msgBox.exec();
    }

    // read in file, int split by ","
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readAll();
        list = line.split(",");
        for(int h = 0; h < HEIGHT; ++h){
            for(int w = 0; w < WIDTH; ++w){
                mapArr[h][w] = list.at(h * 120 + w).toInt();
            }
        }
    }


    file.flush();
    file.close();

}

void MapData::saveMap(QString fileName){
    QFile file(fileName);
    if(! file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox msgBox;
        msgBox.setText("File not oped!");
        msgBox.exec();
    }

    // write in the stringlist
    QTextStream out(&file);
    QString line;
    line = list.join(",");
    out << line;

    file.flush();
    file.close();
}

int **MapData::getMap(){
    return mapArr;
}

