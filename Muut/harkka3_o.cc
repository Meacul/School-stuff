    // Tama ohjelma tutkii syotettyjen tulosten yhtenaisyyksia.
    #include <iomanip>
    #include <iostream>
    #include <sstream>
    #include <cmath>
    #include <string>
     
    #define TUNNUSLUKUJA      8
    #define MAX_OPISKELIJOITA 100
    using namespace std;
     
    struct Opiskelija
    {
            int opiskelijanumero;
            int tunnusluvut[TUNNUSLUKUJA];
            string nimi;
    };
     
    static std::ostream &operator<<(std::ostream &outStream, const Opiskelija &opiskelija ) {
            for (int tunnuslukuindeksi = 0; tunnuslukuindeksi < TUNNUSLUKUJA; tunnuslukuindeksi++) {
                    outStream << setw(3) << right << opiskelija.tunnusluvut[tunnuslukuindeksi];
            }
            outStream << setw(3) << right << ""  << opiskelija.opiskelijanumero << " " << opiskelija.nimi;
            return outStream;
    }
    bool lueOpiskelija(Opiskelija *opiskelija)
    {
            cout << "opiskelijanumero [lopetus: 0]: ";
            cin >> opiskelija->opiskelijanumero;
     
            if (opiskelija->opiskelijanumero == 0) {
                    return true;
            }
     
            cout << "nimi: ";
     
            getline(cin, opiskelija->nimi);
            getline(cin, opiskelija->nimi);
     
            cout << "tunnusluvut: ";
     
            int tunnuslukuindeksi = 0;
            while ( tunnuslukuindeksi < TUNNUSLUKUJA) {
     
               cin >> opiskelija->tunnusluvut[tunnuslukuindeksi];
               tunnuslukuindeksi++;
            }
     
            cout << setw(3) << right << "lisatty opiskelija:" << *opiskelija << endl;
     
            return false;
    }
    int abs(int a) {
            return (a >= 0) ? a : -a;
    }
     
     
    //seuraava funktio tutkii tunnuslukujen erotusta
    int vertaa(const Opiskelija &opiskelija1, const Opiskelija &opiskelija2)
    {
            int samanlaistenLaskuri = 0;
            int tunnuslukuIndeksi = 0;
            while ( tunnuslukuIndeksi < TUNNUSLUKUJA ) {
            if ((abs(opiskelija1.tunnusluvut[tunnuslukuIndeksi] - opiskelija2.tunnusluvut[tunnuslukuIndeksi])) <= 2) {
                   samanlaistenLaskuri++;
     
                    }
            tunnuslukuIndeksi++;}
     
            return samanlaistenLaskuri;
    }
    int main (void)
    {
            Opiskelija opiskelijat[MAX_OPISKELIJOITA];
            int opiskelijaIndeksi = 0;
     
            while (true)
            {
                    if ( opiskelijaIndeksi+1 == MAX_OPISKELIJOITA)
                    {
                            cout << "Liian monta opiskelijaa!" << endl;
                            return 0;
                    }
                    //lopettaa ohjelman ja ilmoittaa, että taulukon maksimi on saav$
                    if (lueOpiskelija(opiskelijat + opiskelijaIndeksi)) {
     
                            break; // lopettaa silmukan while (true), lähinnä suoja$
                    }
                    int i = 0;
                    while (i < opiskelijaIndeksi ) {
                            int yhtalaisyys;
                            yhtalaisyys = vertaa(opiskelijat[i], opiskelijat[opiskelijaIndeksi]);
                            if ( 5 < yhtalaisyys ) {
                                    cout  << "** kopioepaily (" << yhtalaisyys  << "):" << setw(3) << right <<                           opiskelijat[i] << endl;     }
     
                    i++;}
                    opiskelijaIndeksi++;
            }
            return 0;
    }

