#include "pelinakyma.hh"
#include "ui_pelinakyma.h"


Pelinakyma::Pelinakyma(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pelinakyma),
    syote_(4),
    peliLoppu_(false),
    alkuaika_(clock())

{

    ui->setupUi(this);

    scene = new QGraphicsScene(this);

    ui->peligrafiikka->setScene(scene);

}


Pelinakyma::~Pelinakyma()
{
    delete ui;
}

// Asetetaan kartta
void Pelinakyma::aseta_kaupunki(QImage pkartta)
{
    QApplication::focusWidget();
    image = new QGraphicsPixmapItem(QPixmap::fromImage(pkartta));
    scene->addItem(image);
    image->setPos(0,0);
}
// Lisataan drone
void Pelinakyma::lisaa_drone(){

    QBrush redbrush(Qt::black);
    QPen blackpen(Qt::yellow);
    dronekuva = scene->addEllipse(drone->annaSijainti().annaX(),495 - drone->annaSijainti().annaY(),10,10,blackpen,redbrush);
    ui->lcdAmmustenMaara->display(drone->AnnaAmmustenMaara());
}
// Lisataan pysakit
void Pelinakyma::lisaa_pysakki(int x_koord, int y_koord){
    QBrush redbrush(Qt::red);
    QPen blackpen(Qt::black);
    scene->addRect(x_koord,y_koord, 4, 4, blackpen, redbrush);
}
// Lisataan toimija, jos peli on kaynnissa
void Pelinakyma::lisaa_toimija(int x_koord, int y_koord){
    // Tarkistetaan onko peli loppunut
    if(peliLoppu_ == false){
        QBrush redbrush(Qt::yellow);
        QPen blackpen(Qt::black);
        // Lisataan toimijaa vastaavat toimijakuvat ja asetetaan ne tarvittaessa kartalle
        if ((0 <= x_koord and x_koord <= 500) and (0 <= y_koord and y_koord <= 500)){
            toimijakuva = scene->addRect(x_koord,y_koord, 5, 5, blackpen, redbrush);
        }// Muuten lisataan toimijatkuvat pisteeseen 500, 500, joka on kartan ulkopuolella.
        else{
            toimijakuva = scene->addRect(500,500, 5, 5, blackpen, redbrush);
        }
        toimijakuvat.push_back(toimijakuva);
    }
}

// Liikutetaan toimijaa, jos peli on kaynnissa ja toimija  kartalla
void Pelinakyma::toimija_liikkunut(int indeksi, int x_koord, int y_koord){
    // Tarkistetaan pelin tila, aina kun nysse liikkuu
    tarkista_tila();
    // Tarkastetaan onko peli kaynnissa ja onko toimija kartalla ja siirretään sen sijaintia tarvittaessa.
    if((indeksi < toimijakuvat.size()) and (peliLoppu_ == false)){
        if ((-5 <= x_koord and x_koord <= 500) and (1 <= y_koord and y_koord <= 500)){
            QBrush redbrush(Qt::yellow);
            QPen blackpen(Qt::black);
            scene->removeItem(toimijakuvat.at(indeksi));
            toimijakuvat.at(indeksi) = scene->addRect(x_koord,y_koord, 5, 5, blackpen, redbrush);
        }

    }
}

// Liikutetaan dronea
void Pelinakyma::drone_liikkunut(){
    // Syotteella nelja drone ei liiku, muilla syotteilla liikutetaan dronea.
    // Syotteet sailyvat, kunnes niita muutetaan, joten drone jatkaa liikettaan annettuun suuntaan
    if (((syote_ != 4) and (drone->otaSyote(syote_) == true)) and (peliLoppu_ == false)){

        if(syote_ == 1){
            dronekuva->moveBy(-3.333333,0);
        }if(syote_ == 2){
            dronekuva->moveBy(0,3.333333);
        }if(syote_ == 0){
            dronekuva->moveBy(0,-3.333333);
        }if(syote_ == 3){
            dronekuva->moveBy(3.333333,0);
        }
    }
}
// Poistetaan nysse
void Pelinakyma::poista_toimija(unsigned indeksi){
    //Poistetaan toimijan kuva kartalta
    if(indeksi < toimijakuvat.size()){
        scene->removeItem(toimijakuvat.at(indeksi));
        toimijakuvat.erase(toimijakuvat.begin()+indeksi);
    }
}
// Tarkistetaan, onko peli kaynnissa ja onko 5 min kulunut jo
void Pelinakyma::tarkista_tila(){
    // 5 min vastaa noin 330000
    if ((clock() - alkuaika_ > 333000) and (peliLoppu_ == false)){
        on_exitButton_clicked();
    }
}

// Paivitetaan peli-ikkunan kello
void Pelinakyma::paivita_aika(QTime kello){
    if (peliLoppu_ == false){
        ui->kello->setTime(kello);
    }
    // Avataan lopetusikkuna 5 minuutin kohdalla ja pidetään huoli ettei ikkunaa avata useampaa kertaa
}

// Paivitetaan peli-ikkunaan pisteet
void Pelinakyma::paivita_pisteet(double pisteet){
    // Paivitetaan pisteet
    ui->lcdTilasto->display(pisteet);

}

// Suljetaan oman puolen peli ja avataan lopetusikkuna, jos Exit painiketta painetaan tai 5 min on kulunut
void Pelinakyma::on_exitButton_clicked()
{
    if(peliLoppu_ == false){
        peliLoppu_ = true;
        // Luodaan lopetusikkuna ja avataan se
        Lopetusikkuna* lopetusikkuna = new Lopetusikkuna;
        lopetusikkuna->show();
        // Pyyhitään scene ja toimijakuvat, jolloin kurssipuolen pyoriminen taustalla ei haittaa
        scene->clear();
        toimijakuvat.clear();
        // Esitetaan pelaajan pisteet
        lopetusikkuna->nayta_pisteet(tilasto->annaPisteet(), tilasto->annaTuhotutNysset(), drone->AnnaOsumatarkkuus());
    }
}

// Drone pudottaa pommin
void Pelinakyma::ammu()
{
    if(peliLoppu_ == false){
        drone->tuhoa();
        ui->lcdAmmustenMaara->display(drone->AnnaAmmustenMaara());
    }
}
// Drone lataa, jos pelaajalla on pisteita, ja drone ammukset eivat ole taynna
void Pelinakyma::lataa()
{
    // Ladataan ammukset, jos ammuksia on kulunut
    if((drone->lataa() == true) and (peliLoppu_ == false)){
        // Paivitetaan ammukset, jos pelaajalla on riittavasti pisteita
        if (tilasto->lataa() == true){
            // Esitetaan ammusten ja pisteiden maarat.
            ui->lcdAmmustenMaara->display(drone->AnnaAmmustenMaara());
            ui->lcdTilasto->display(tilasto->annaPisteet());
        }
        else{
            // Lopetetaan peli, jos pisteet loppuvat
            on_exitButton_clicked();
        }
    }

}

// Funktio lukee kayttajan nappainkomennot
void Pelinakyma::keyPressEvent(QKeyEvent *e){
    // Maaritetaan nappainpainalluskomennot niin, etta
    // jokainen suunta saa omanlaisensa syote arvon.
    switch (e->key()) {
        // A nappaimella drone liikkuu vasemmalle/lanteen
        case Qt::Key_A:syote_= 1;break;

        // S nappaimella drone liikkuu alas/etelaan
        case Qt::Key_S:syote_= 2;break;

        // W nappaimella drone liikkuu ylos
        case Qt::Key_W:syote_= 0;break;

        // D nappaimella drone liikkuu oikealle
        case Qt::Key_D:syote_= 3;break;

        // P nappaimella drone pysahtyy
        case Qt::Key_P:syote_= 4;break;

        // L nappaimella drone lataa
        case Qt::Key_L:lataa();break;

        // K nappaimella drone pudottaa pommin
        case Qt::Key_K:ammu(); break;
    }
}




