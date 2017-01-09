#include "luopeli.hh"
#include "kaupunki.hh"
#include "pelinakyma.hh"
#include "drone.hh"

using namespace Rajapinta;

// Funktio luo kaupungin, dronen ja pelinakyman
std::shared_ptr<KaupunkiRP> Rajapinta::luoPeli(){
    std::shared_ptr<Kaupunki> kaupunki (new Kaupunki);
    std::shared_ptr<Drone> drone (new Drone);
    Pelinakyma* window = new Pelinakyma;
    // Lisataan kaupunki droneen
    drone->kaupunki = kaupunki;
    // Lisataan drone pelinakymaan
    window->drone = drone;
    // Lisataan pelinakyma kaupunkiin
    kaupunki->window = window;

    return kaupunki;
}
