#ifndef KAUPUNKI_HH
#define KAUPUNKI_HH
#include "kaupunkirp.hh"
#include "tilasto.hh"
#include "pelinakyma.hh"
#include "nysse.hh"
#include "kulkuneuvo.hh"

#include <QTime>
#include <vector>
#include <memory>

/// Kaupunkiluokka kommunikoi kurssipuolen ja pelinakyman valilla, ja se luo ohjaa ja tuhoaa nysseja.

using namespace Rajapinta;
using namespace std;

class Kaupunki:public KaupunkiRP
{
public:
    Kaupunki();
    ~Kaupunki();
    void asetaTausta(QImage& perustaustakuva, QImage& isotaustakuva);
    void asetaKello(QTime kello);
    void lisaaPysakki(std::shared_ptr<PysakkiRP> pysakki);
    void peliAlkaa(); // Siirry alustustilasta pelitilaan
    void lisaaToimija(std::shared_ptr<ToimijaRP> uusitoimija);
    void poistaToimija(std::shared_ptr<ToimijaRP> toimija);
    void toimijaTuhottu(std::shared_ptr<ToimijaRP> toimija);
    bool loytyykoToimija(std::shared_ptr<ToimijaRP> toimija) const;
    void toimijaLiikkunut(std::shared_ptr<ToimijaRP> toimija);
    std::vector<std::shared_ptr<ToimijaRP>> annaToimijatLahella(Sijainti paikka) const;
    bool peliLoppunut() const;
    Pelinakyma* window;

private:
    Tilasto* tilasto; // Tilastopointteri
    shared_ptr<ToimijaRP> toimija; // Yksittainen nysse
    vector<shared_ptr<KulkuneuvoRP>> toimijat; // Vektori nysseilla

};
#endif // KAUPUNKI_HH
