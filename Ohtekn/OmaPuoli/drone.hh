#ifndef DRONE_HH
#define DRONE_HH
#include "toimijarp.hh"
#include "kaupunkirp.hh"
#include "sijainti.hh"

#include <set>
#include <map>
#include <vector>
#include <string>
#include <memory>

/// Drone on itsenainen toimija, joka liikkuu, pudottaa pommeja, lataa
/// ja tarkkailee osumatarkkuuttaan

using namespace std;
using namespace Rajapinta;

class Drone:public ToimijaRP
{
public:
    Drone();
    ~Drone();
    Sijainti annaSijainti() const;
    void liiku(Rajapinta::Sijainti sij);
    bool onkoTuhottu() const;
    void tuhoa();
    bool otaSyote(int suunta);
    shared_ptr<KaupunkiRP> kaupunki;
    bool lataa();
    double AnnaAmmustenMaara() const;
    double AnnaOsumatarkkuus() const;

private:
    Rajapinta::Sijainti sijainti_; // Dronen sijainta
    bool tuhottu_; // Dronen tila
    int ammuksia_; // Ammusten maara
    double osumia_; // Osumien maara
    double ammuttuja_; // Laukausten maara
};

#endif // DRONE_HH
