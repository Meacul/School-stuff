#ifndef PELINAKYMA_HH
#define PELINAKYMA_HH

#include "drone.hh"
#include "lopetusikkuna.hh"

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTime>
#include <QTimer>
#include <list>
#include <QLCDNumber>
#include <ctime>

/// Pelinakymassa naytetaan pelin kartta, drone, pysakit ja nysset.
/// Pelinakyman kautta toimijoita ohjataan
/// Dronea liikutetaan WSAD näppäimillä niin että drone jatkaa haluttuun suuntaan itsenäisesti
/// Drone pysähtyy P näppäimestä ampuu K näppäimestä ja lataa L näppäimestä
using namespace std;
namespace Ui {
class Pelinakyma;
}

class Pelinakyma : public QDialog
{
    Q_OBJECT

public:
    shared_ptr<Drone> drone;
    void aseta_kaupunki(QImage pkartta);
    void lisaa_pysakki(int x_koord, int y_koord);
    void lisaa_toimija(int x_koord, int y_koord);
    void toimija_liikkunut(int indeksi, int x_koord, int y_koord);
    void drone_liikkunut();
    void poista_toimija(unsigned indeksi);
    void lisaa_drone();
    void tarkista_tila();
    void paivita_aika(QTime kello);
    void paivita_nysset();
    void paivita_pisteet(double pisteet);
    void ammu();
    void lataa();
    explicit Pelinakyma(QWidget *parent = 0);
    Tilasto* tilasto;
    ~Pelinakyma();

private slots:

    void on_exitButton_clicked();



protected:
   void keyPressEvent(QKeyEvent *e);

private:
    Ui::Pelinakyma *ui;
    QGraphicsScene *scene; // Pelinakyma
    QGraphicsPixmapItem *image; // Kartta
    QGraphicsEllipseItem *dronekuva; // Drone
    QGraphicsRectItem *toimijakuva; // Nysse
    vector<QGraphicsRectItem*> toimijakuvat; // Vektori nysseilla
    int syote_; // Liikesuunta
    clock_t alkuaika_; // Alkuaika, josta lasketaan pelin kesto
    bool peliLoppu_; // Totuusarvo pelin tilasta

};

#endif // PELINAKYMA_HH
