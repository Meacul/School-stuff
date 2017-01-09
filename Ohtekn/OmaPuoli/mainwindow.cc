#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "pelinakyma.hh"
#include <QApplication>
#include <unistd.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->exitButton, SIGNAL(clicked()),
                    this, SLOT(sulje_ohjelma()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sulje_ohjelma(){
    destroy();
}


void MainWindow::on_playButton_clicked()
{
    Pelinakyma pelinakyma;
    pelinakyma.setModal(true);
    pelinakyma.exec();

}
