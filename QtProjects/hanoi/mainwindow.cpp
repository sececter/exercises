#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setMaximum(MAX_DISKU);

    //Vytvori grafickou scenu pro graficke objekty.
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    scene->clear();
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete h;
    delete[] stavy;
}

//Vykresli vez o zadane rel. pozici podle zadaneho stavu.
void MainWindow::vykresli(int relx, stav_veze vez) {
    //Sirka a vyska platna.
    int sirka = ui->graphicsView->width();
    int vyska = ui->graphicsView->height();

    //X slozka leveho dolniho rohu obdelnika.
    int x = sirka / 4 * (2+relx);

    //Relativni vzdalenost y slozek jednotl. obdelniku.
    int kroky = vyska / (disku + 5);
    //Vyska jednoho obdelnika.
    int vely = kroky * 9 / 10;

    //Relativni vzdalenost x slozek jednotl. obdelniku
    int krokx = sirka / (8*disku);

    //Vykresli jednotlive obdelniky.
    for(int i = 0; i < vez.vyska; i++) {
        int disk = vez.disky[i];
        int velx = disk * krokx;
        int y = (disku - i -1) * kroky;

        //Vytvori, nastavi velikost, pozici a barvu obdelnika predstavujiciho disk.
        QGraphicsRectItem * obd = new QGraphicsRectItem;
        obd->setRect(x-velx, y, 2*velx, vely);
        obd->setPen(QColor("red"));
        QColor okraj = QColor::fromHsv((360/disku*disk)%360, 240, 240);
        QColor vnitrek = QColor::fromHsv((360/disku*disk)%360, 120, 240);
        obd->setPen(okraj);
        obd->setBrush(vnitrek);
        scene->addItem(obd);
    }
}

void MainWindow::update() {
    try {
        //Precte poctu disku a spocita pocet kroku.
        disku = ui->spinBox->value();
        kroku = (1<<disku)-1;
        //Aktualizuje vlastnosti scroll baru.
        ui->horizontalScrollBar->setMinimum(0);
        ui->horizontalScrollBar->setMaximum(kroku);
        ui->horizontalScrollBar->setValue(0);
        //Vytvori novou hru, vyresi a zkopiruje pole stavu a vykresli
        //vychozi pozici
        h = new Hra(disku);
        stavy = new stav_hry[kroku+1];
        for(int i = 0; i <= kroku; i++) {
            stavy[i] = h->stav_v_kroku(i);
        }
        vykresli(-1, stavy[0].l);
    } catch (chyba_hra e) {
        QMessageBox messageBox;
        messageBox.critical(0,"Chyba",e.what());
        messageBox.setFixedSize(500,200);
    } catch (chyba_vez e) {
        QMessageBox messageBox;
        messageBox.critical(0,"Chyba",e.what());
        messageBox.setFixedSize(500,200);
    } catch(...) {
        QMessageBox messageBox;
        messageBox.critical(0,"Chyba","Chyba pri inicializaci hry!");
        messageBox.setFixedSize(500,200);
    }
}

//Vykresluje jednotlive kroky.
void MainWindow::on_horizontalScrollBar_valueChanged(int value) {
    if(value >= 0 && value <= kroku) {
        scene->clear();
        vykresli(-1, stavy[value].l);
        //Pri sudem poctu kroku vymenime stredni a pravou vez.
        if(disku%2 == 1) {
            vykresli(0, stavy[value].s);
            vykresli(1, stavy[value].p);
        } else {
            vykresli(0, stavy[value].p);
            vykresli(1, stavy[value].s);
        }
    }
}

//Pri zmene poctu disku aktualizuje zobrazeni.
void MainWindow::on_spinBox_valueChanged() {
    scene->clear();
    update();
}
