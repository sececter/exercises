#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "vez.h"
#include "hra.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_horizontalScrollBar_valueChanged(int value);

    void on_spinBox_valueChanged();

private:
    Ui::MainWindow *ui;
    QGraphicsScene * scene;
    void vykresli(int relx, stav_veze vez);
    void update();
    Hra *h;
    stav_hry *stavy;
    int disku;
    int kroku;
};

#endif // MAINWINDOW_H
