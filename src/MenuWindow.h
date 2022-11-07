#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include "Game.h"
#include "MapData.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MenuWindow; }
QT_END_NAMESPACE

class MenuWindow : public QMainWindow{
    Q_OBJECT

public:
    MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
    void startGame();
    void openEditMenu();

private:
    Ui::MenuWindow *ui;
};
#endif // MENUWINDOW_H
