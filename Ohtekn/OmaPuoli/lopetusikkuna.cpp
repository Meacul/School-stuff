#include "lopetusikkuna.hh"
#include "ui_lopetusikkuna.h"


Lopetusikkuna::Lopetusikkuna(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lopetusikkuna)
{
    ui->setupUi(this);
}

Lopetusikkuna::~Lopetusikkuna()
{
    delete ui;
}

// Funktio paivittaa pelaajan pisteet, tuhotut nysset ja osumatarkkuuden
void Lopetusikkuna::nayta_pisteet(double pisteet, double bussit, double tarkkuus){

    ui->lcdScore->display(pisteet);
    ui->lcdBusses->display(bussit);
    ui->lcdHitRatio->display(tarkkuus);

}

// Paatetaan ohjelman suoritus
void Lopetusikkuna::on_exitButton_clicked()
{
    QCoreApplication::quit();
}
