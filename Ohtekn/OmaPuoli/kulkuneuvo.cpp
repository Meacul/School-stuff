#include "kulkuneuvo.hh"

Kulkuneuvo::Kulkuneuvo(int x_koord,int y_koord,shared_ptr<ToimijaRP> toimija)
{
    x_koord_ = x_koord,
    y_koord_ = y_koord,
    toimija_ = toimija;
}
Kulkuneuvo::~Kulkuneuvo()
{

}

string Kulkuneuvo::annaNimi() const{
    cout << "anna nimi" << endl;
}
vector<std::shared_ptr<MatkustajaRP> > Kulkuneuvo::annaMatkustajat() const{
    cout << "anna matkustajat" << endl;
}
void Kulkuneuvo::lisaaMatkustaja(std::shared_ptr<MatkustajaRP> matkustaja){
    cout << "lisaa matkustaja" << endl;
    nimi_ ="hei";
}

void Kulkuneuvo::poistaMatkustaja(std::shared_ptr<MatkustajaRP> matkustaja){
    cout << "poista matkustaja" << endl;
}
void Kulkuneuvo::tee_jotain_muuta(){

}
