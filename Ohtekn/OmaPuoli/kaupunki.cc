#include "kaupunki.hh"

Kaupunki::Kaupunki()
{
    // Luodaan tilasto olio.
    tilasto = new Tilasto;
}
Kaupunki::~Kaupunki()
{

}
//Asettaa halutut taustakuvat.
void Kaupunki::asetaTausta(QImage& perustaustakuva, QImage& isotaustakuva)
{
    window->aseta_kaupunki(perustaustakuva);
}
//Asettaa kellon.
void Kaupunki::asetaKello(QTime kello)
{
    window->paivita_aika(kello);
}
//Lisaa pysakin.
void Kaupunki::lisaaPysakki(std::shared_ptr<PysakkiRP> pysakki)
{
    // muutetaan y koordinaattia 495 pixselia, jotta saadaan kartta tasmaamaan
    int x_koord = pysakki->annaSijainti().annaX();
    int y_koord = 495- pysakki->annaSijainti().annaY();
    // Lisataan pysakkien kuvat, jos ne osuvat kartalle
    if ((0 <= x_koord and x_koord <= 500) and (0 <= y_koord and y_koord <= 500)){
        window->lisaa_pysakki(x_koord, y_koord);
    }
}
//Aloittaa pelin ja luo drone-toimijan.
void Kaupunki::peliAlkaa()
{
    // asetetaan drone kartalle ja avataan pelinakyma
    window->tilasto = tilasto;
    window->lisaa_drone();
    window->show();

}
//Lisaa uuden toimijan peliin.
void Kaupunki::lisaaToimija(std::shared_ptr<ToimijaRP> uusitoimija)
{
    std::shared_ptr<KulkuneuvoRP> nysse = std::dynamic_pointer_cast <KulkuneuvoRP> (uusitoimija);
    if(nysse != NULL){
        // muutetaan y koordinaattia 495 pixselia, jotta saadaan kartta tasmaamaan
        int x_koord = nysse->annaSijainti().annaX();
        int y_koord = 495 - nysse->annaSijainti().annaY();
        // Lisataan toimijat vektoriin, toimijoiden kuvat kartalle seka paivitetaan tilasto
        toimijat.push_back(nysse);
        window->lisaa_toimija(x_koord, y_koord);
        tilasto->uusiNysse();
        tilasto->lisaaMatkustajia(nysse->annaMatkustajat().size());
    }



}
//Poistaa toimijan kaupungista ja pelinäkymästä.
void Kaupunki::poistaToimija(std::shared_ptr<ToimijaRP> toimija)
{
    std::shared_ptr<KulkuneuvoRP> nysse = std::dynamic_pointer_cast <KulkuneuvoRP> (toimija);
    if(nysse != NULL){
        unsigned j = 0;
        while(j < toimijat.size()){
            if (toimijat[j] == nysse){
                // Paivitetaan tilasto, poistetaan toimijan kuva kartalta poistetaan
                // toimija vektorista ja tuhotaan toimija
                tilasto->nyssePoistui();

                window->poista_toimija(j);
                toimijat[j]->tuhoa();
                toimijat.erase(toimijat.begin()+j);
            }j++;
        }
    }
}
//Tuhoaa toimijan kaupungista.
void Kaupunki::toimijaTuhottu(std::shared_ptr<ToimijaRP> toimija)
{
    std::shared_ptr<KulkuneuvoRP> nysse = std::dynamic_pointer_cast <KulkuneuvoRP> (toimija);
    if(nysse != NULL){
        // Paivitetaan tilasto ja tuhotaan nysse
        tilasto->nysseTuhoutui();
        tilasto->matkustajiaKuoli(nysse->annaMatkustajat().size());
        window->paivita_pisteet(tilasto->annaPisteet());
        poistaToimija(toimija);
    }

}
//Etsii kyseisen toimijan ja palauttaa sen olemassaolon totuusarvon.
bool Kaupunki::loytyykoToimija(std::shared_ptr<ToimijaRP> toimija) const
{
    size_t k = 0;
    while(k < toimijat.size()){
        if (toimijat[k] == toimija){
            return true;
        }k++;
    }return false;
}
//Ilmoittaa toimijan liikkeet pelinäkymälle.
void Kaupunki::toimijaLiikkunut(std::shared_ptr<ToimijaRP> toimija)
{
    std::shared_ptr<KulkuneuvoRP> nysse = std::dynamic_pointer_cast <KulkuneuvoRP> (toimija);
    if((nysse != NULL) and (toimijat.size() != 0)){
        // muutetaan y koordinaattia 495 pixselia, jotta saadaan kartta tasmaamaan
        int x_koord = nysse->annaSijainti().annaX();
        int y_koord = 495 - nysse->annaSijainti().annaY();
        size_t k = 0;
        // Liikutetaan dronea aina, kun vektorin ensimmainen nysse liikkuu
        if (toimijat[0] == nysse){
            window->drone_liikkunut();
        }// Liikutetaan nyssea, jos sellainen on olemassa
        while(k < toimijat.size()){
            if (toimijat[k] == nysse){
                window->toimija_liikkunut(k, x_koord, y_koord);
            }k++;
        }
    }
}
//Antaa annetun sijainnin lähellä olevat toimijat.
std::vector<std::shared_ptr<ToimijaRP>> Kaupunki::annaToimijatLahella(Sijainti paikka) const
{
    size_t l = 0;
    std::vector<std::shared_ptr<ToimijaRP>> temp;
    while(l < toimijat.size()){
        Sijainti tempsij = toimijat[l]->annaSijainti();
        if(tempsij.onkoLahella(paikka)){
            // Lisataan lahella oleva nysse valiaikaisvektoriin ja palautetaan lopuksi vektori
            temp.push_back(toimijat[l]);
        }++l;
    }
    return temp;
}
//Lopettaa pelin.
bool Kaupunki::peliLoppunut() const
{
    return false;
}

