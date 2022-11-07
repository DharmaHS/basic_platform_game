QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BlockObj.cpp \
    Bullet.cpp \
    EditWindow.cpp \
    Entity.cpp \
    Game.cpp \
    LevelWindow.cpp \
    MapData.cpp \
    Player.cpp \
    Score.cpp \
    TrapSensor.cpp \
    main.cpp \
    MenuWindow.cpp

HEADERS += \
    BlockObj.h \
    Bullet.h \
    EditWindow.h \
    Entity.h \
    Game.h \
    LevelWindow.h \
    MapData.h \
    MenuWindow.h \
    Player.h \
    Score.h \
    TrapSensor.h

FORMS += \
    EditWindow.ui \
    LevelWindow.ui \
    MenuWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
