// Tama ohjelma tutkii syotettyjen tulosten yhtenaisyyksia.
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
	std::string nimi;
};

static std:ostream &operator<< (std::ostream &outstream, const Opiskelija &opiskelija )
{
   for (int tunnuslukuindeksi = 0; 
bool lueOpiskelija(Opiskelija *opiskelija) // palauttaa true jos halutaan lopettaa lukeminen
{
	cout << "opiskelijanumero [lopetus: 0]:";
	cin >> opiskelija->opiskelijanumero;
	
	if (opiskelija->opiskelijanumero == 0) {
		return true;
	}
	
	cout << "nimi:";
	getline(cin, opiskelija->nimi);
        
   
	cout << "tunnusluvut:";
	string tunnusluvutstring;
	getline(cin, tunnusluvutstring); // ensimmainen luku lukee kai edellisen entterin painalluksen,
	 // niin pitaa lukea kahdesti... varmaan on parempikin tapa
	
	stringstream ss(tunnusluvutstring);
	for (int tunnuslukuindeksi = 0; tunnuslukuindeksi < TUNNUSLUKUJA; tunnuslukuindeksi++) {
   		ss >> opiskelija->tunnusluvut[tunnuslukuindeksi];
   	}
   	
   	// tulostetaan data, etta ollaan varmoja etta sisaanluku toimii oikein
   	cout << "lisatty opiskelija" << i << endl;†
	for (int tunnuslukuindeksi = 0; tunnuslukuindeksi < TUNNUSLUKUJA; tunnuslukuindeksi++) {
		cout << " " << opiskelija->tunnusluvut[tunnuslukuindeksi];
	}
	cout << endl;
   	
        tulostaTiedot(*opiskelija);
   	return false;
}

void tulostaTiedot( const Opiskelija &opiskelija )
{     
       cout << "lisatty opiskelija" << opiskelija << endl;
}

int abs(int a) {
	return (a >= 0) ? a : -a;
}

//Parametrit ovat referensseja, se nopeuttaa koodia koska
//Opiskelija-struckteista ei tarvitse tehd√§ kopiota muistissa. Lisaksi
//ne ovat const koska taman funktion ei ole tarkoitus muuttaa niiden arvoja,
//vaan ainoastaan lukea niita

int vertaa(const Opiskelija &opiskelija1, const Opiskelija &opiskelija2)
{
	int samanlaistenLaskuri = 0;
	for (int tunnuslukuIndeksi = 0; tunnuslukuIndeksi < TUNNUSLUKUJA; tunnuslukuIndeksi++ ) {
		if (abs(opiskelija1.tunnusluvut[tunnuslukuIndeksi] - opiskelija2.tunnusluvut[tunnuslukuIndeksi]) < 2) {
			samanlaistenLaskuri++;
		}
	}
	
	return samanlaistenLaskuri; // palauttaa true jos laskuri on 7 tai enemman
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
		
		if (lueOpiskelija(opiskelijat + opiskelijaIndeksi)) {
			cout << "Lopetetaan ohjelma" << endl;
			break; // lopettaa silmukan while (true)
		}
		
	   tulostaTiedot(*opiskelija);
		for (int i = 0; i < opiskelijaIndeksi-1; i++) //Verrataan uusinta opiskelijaa aiempiin
		{
     		   int yhtalaisyys;
		   yhtalaisyys = vertaa(opiskelijat[i], opiskelijat[opiskelijaIndeksi]);
			if ( 5 < yhtalaisyys ) {
			   
			   cout << "**kopioep‰ilty[" << yhtalaisyys << "]" << opiskelijaIndeksi << endl;
			}
		}
		
		opiskelijaIndeksi++;
	}
	return 0;
}
