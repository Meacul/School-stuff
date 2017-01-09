#ifndef KULKUNEUVO_HH
#define KULKUNEUVO_HH
#include "kulkuneuvorp.hh"
#include "toimijarp.hh"
#include <iostream>

using namespace Rajapinta;
using namespace std;

class Kulkuneuvo
{
public:
    Kulkuneuvo(int x_koord, int y_koord, shared_ptr<ToimijaRP> toimija);
    ~Kulkuneuvo();
    string annaNimi() const;
    int annaXkood() const;
    int annaYkoord() const;
private:
    string nimi_;
    shared_ptr<ToimijaRP> toimija_;
    int x_koord_;
    int y_koord_;
    shared_ptr<MatkustajaRP> matkustaja;
    vector<std::shared_ptr<MatkustajaRP> > matkustajat_;
};


#endif // KULKUNEUVO_HH
