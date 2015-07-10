#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wet.h"
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonOK_clicked()
{
    using namespace std;
    int argc = 0;
    char* argv[4];
    argv[argc++] = "firstArg ";
    if(ui->inLO->isChecked()) {
        argv[argc++] = "-l ";
    }
    if(ui->inGO->isChecked()) {
        argv[argc++] = "-g ";
    }

    QString theURL = ui->inURL->text();
    QString theDepth = ui->inDepth->text();
    string sURL = theURL.toStdString();
    string sDepth = theDepth.toStdString();

    argv[argc++] = &sURL[0];
    argv[argc] = &sDepth[0];

    WET::run(argc,argv);
}

void MainWindow::on_inURL_returnPressed()
{
    ui->buttonOK->click();
}

void MainWindow::on_inDepth_returnPressed()
{
    ui->buttonOK->click();
}
