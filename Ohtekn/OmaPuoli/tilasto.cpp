#include "tilasto.hh"



Tilasto::Tilasto():
    pisteet_(0.0),
    nyssien_maara_(0),
  matkustajien_maara_(0),
  tuhotut_nysset_(0)
{
}
Tilasto::~Tilasto()
{

}

// Palauttaa pelaajan pisteet
int Tilasto::annaPisteet() const
{
    return pisteet_;
}

// Palauttaa matkustajien maaran
unsigned int Tilasto::anna_matkustajien_maara() const{
    return matkustajien_maara_;
}

// Vahentaa matkustajien maaraa ja antaa jokaisesta matkustajasta 1 pisteen
void Tilasto::matkustajiaKuoli(int lkm)
{

    pisteet_ = pisteet_ + lkm;
    matkustajien_maara_ = matkustajien_maara_ - lkm;
}

// Lisaa matkustajien maaraa
void Tilasto::lisaaMatkustajia(int lkm)
{
    matkustajien_maara_ = matkustajien_maara_ + lkm;
}

// Vahentaa nyssien maaraa ja antaa 100 pistetta
void Tilasto::nysseTuhoutui()
{
    ++tuhotut_nysset_;
    pisteet_ = pisteet_ + 100;
    --nyssien_maara_;
}

// Lisaa nyssien maaraa
void Tilasto::uusiNysse()
{
    ++nyssien_maara_;
}

// Vahentaa nyssien maaraa
void Tilasto::nyssePoistui()
{
    --nyssien_maara_;
}

// Palauttaa tuhottunen nyssien maaran
int Tilasto::annaTuhotutNysset() const{
    return tuhotut_nysset_;
}

// Vahentaa 10 pistetta jos lataaminen onnistuu
bool Tilasto::lataa(){
    double pisteet = pisteet_ - 10;
    if(pisteet < 0){
        return false;
    }
    else{
        pisteet_ = pisteet_ - 10;
        return true;
    }
}
