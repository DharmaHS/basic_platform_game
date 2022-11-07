#ifndef MAPDATA_H
#define MAPDATA_H

#include <QString>
#include <QStringList>

class MapData{

private:
    const static int HEIGHT = 12;
    const static int WIDTH = 120;

    int ** mapArr;

public:
    QStringList list;

public:
    MapData();
    void readMap(QString fileName);
    void saveMap(QString fileName);
    int ** getMap();

};

#endif // MAPDATA_H
