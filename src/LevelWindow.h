#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#include <QDialog>

namespace Ui {
class LevelWindow;
}

class LevelWindow : public QDialog{
    Q_OBJECT

public:
    explicit LevelWindow(QWidget *parent = nullptr);
    ~LevelWindow();

public slots:
    void editLevel1();
    void playLevel1();
    void editLevel2();
    void playLevel2();

private:
    Ui::LevelWindow *ui;
};

#endif // LEVELWINDOW_H
