#include "drone.hh"

//Luo dronen karttakuvan pikselikoordinaattiin 0,0.
Drone::Drone()
{
    //6824642,3327034
    sijainti_.asetaPohjIta(6824642,3327034);
    ammuksia_ = 3;
    osumia_ = 0;
    ammuttuja_ = 0;

}
Drone::~Drone()
{
}
//Palauttaa dronen sijainnin.
Sijainti Drone::annaSijainti() const
{
    return sijainti_;
}

//Liikuttaa dronen annettuun sijaintiin.
void Drone::liiku(Rajapinta::Sijainti sij)
{
    sijainti_ = sij;
}

//Tämä on toimijaRP:n jäänne, jota ei dronen tapauksessa tarvita.
bool Drone::onkoTuhottu() const
{
}
//Tuhoaa dronen lähistöllä olevat bussi-toimijat.
void Drone::tuhoa()
{
    if (ammuksia_ != 0){
        ++ammuttuja_;
        // Tutkitaan ampumaetaisyyden paassa olevat nysset
        std::vector<std::shared_ptr<ToimijaRP>> lahellaolijat = kaupunki->annaToimijatLahella(sijainti_);
        unsigned int k = 0;
        while(k < lahellaolijat.size()){
            // Tuhotaan kaikki ampumaetaisyydella olleet nysset
            kaupunki->toimijaTuhottu(lahellaolijat[k]);
            k++;
            ++osumia_;
        }
        --ammuksia_;
    }

}
//Ottaa vastaan käyttäjän syötteen ja liikuttaa dronea haluttuun suuntaan.
bool Drone::otaSyote(int suunta)
{

    Sijainti alkusij;
    alkusij = annaSijainti();
    double ita = alkusij.annaItaKoord();
    double pohj = alkusij.annaPohjoisKoord();
    // Dronen liikkumisnopeus on 1 koordinaattipiste haluttuun suuntaan
    double liikkumisnopeus = 10;

    // Tutkitaan mihin suuntaan dronea halutaan liikuttaa
    if(suunta == 0)
    {
        pohj = pohj + liikkumisnopeus;
    }

    if(suunta == 1)
    {
        ita = ita - liikkumisnopeus;
    }

    if(suunta == 2)
    {
        pohj = pohj - liikkumisnopeus;
    }

    if(suunta == 3)
    {
        ita = ita + liikkumisnopeus;

    }
    // Tutkitaan onko drone pelialueella ja liikutetaan dronea vain sen ollessa pelialueella.
    alkusij.asetaPohjIta(pohj, ita);
    if((0 <= alkusij.annaX()) and (alkusij.annaX() <= 495) and (0 <= alkusij.annaY()) and( alkusij.annaY() <= 500)){
        liiku(alkusij);
        return true;
    }
    // Jos drone ei ole pelialueella, ei sitä liikuteta.
    else{
        return false;
    }

}
//Lataa aseen ammukset.
bool Drone::lataa(){
    if(ammuksia_ == 3){
        return false;
    }
    ammuksia_ = 3;
    return true;
}
//Palauttaa ammusten tämänhetkisen määrän.
double Drone::AnnaAmmustenMaara() const{
    return ammuksia_;
}
//Laskee pelaajan osumatarkkuuden.
double Drone::AnnaOsumatarkkuus() const{
    if ((ammuttuja_ == 0) or (osumia_ == 0)){
        return 0;
    }else{
        return osumia_/ammuttuja_;
    }
}


