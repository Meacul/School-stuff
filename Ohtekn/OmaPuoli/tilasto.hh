#ifndef TILASTO_HH
#define TILASTO_HH
#include "tilastorp.hh"

#include <QtDebug>

/// Tilastoluokka pitaa kirjaa pelissa keratyista pisteista
/// Tuhotusta nyssesta saa 100 pistetta tuhotusta matkustajasta 1 pisteen
/// ja lataaminen maksaa 10 pistetta. pisteiden mennessä negatiivisiksi, peli loppuu.
/// Myös tuhotuista nysseista pidetaan kirjaa

using namespace Rajapinta;
class Tilasto:public TilastoRP

{
public:
    Tilasto();
    ~Tilasto();
    int annaPisteet() const;
    unsigned int anna_matkustajien_maara() const;
    void matkustajiaKuoli(int lkm);
    void lisaaMatkustajia(int lkm);
    void nysseTuhoutui();
    void uusiNysse();
    void nyssePoistui();
    int annaTuhotutNysset() const;
    bool lataa();

private:
    double pisteet_; // Pelaajan pisteet
    int nyssien_maara_; // Nyssien maara pelissa
    unsigned int matkustajien_maara_; // Matkustajien maara pelissa
    int tuhotut_nysset_; // Tuhottujen nyssien maara
};

#endif // TILASTO_HH
