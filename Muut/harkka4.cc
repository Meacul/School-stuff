//Kyosti Nyrhila 229111
// Tama ohjelma tutkii syotettyjen tulosten yhtenaisyyksia.
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>
#include <fstream>
#include <string>
#include <cstdio>
const int TUNNUSLUKUJA = 8;
const int MAX_OPISKELIJOITA = 100;
const char Erotin = ':';
const char kommentti = '%';
using namespace std;


struct Opiskelija
{
   int opiskelijanumero;
   int tunnusluvut[TUNNUSLUKUJA];
   string nimi;
};
bool lisaa_taulukkoon( Opiskelija lisattava, 
		       Opiskelija taulukko[], int& luettu);
  
     
static std::ostream &operator<<(std::ostream &outStream, 
				const Opiskelija &opiskelija ) {
   for (int tunnuslukuindeksi = 0;
	tunnuslukuindeksi < TUNNUSLUKUJA; tunnuslukuindeksi++) {
      outStream << setw(3) << right << 
	opiskelija.tunnusluvut[tunnuslukuindeksi];
   }
   outStream << setw(3) << right << ""  << 
     opiskelija.opiskelijanumero << " " << opiskelija.nimi;
   return outStream;
}

//lukee tiedoston ja tallentaa sen Opiskelija Structiin
bool lueTiedosto(Opiskelija taulukko[], string tiedostonimi, 
		 int& luettu)
{
   ifstream tiedosto(tiedostonimi.c_str());
   if (!tiedosto)
     {
	cout << "Virhe: tiedostoa " << tiedostonimi; 
	cout << " ei saada avattua luettavaksi.";
     }
   luettu = 0;
   string rivi;
     while ( getline(tiedosto, rivi))
	     {
		//seuraava rivi poistaa kommentti- ja tyhjät rivit
		if ( rivi.empty() or rivi.at(0) == kommentti )
		  {
		     continue;
		  }
		Opiskelija opisk;
		istringstream rivivirta(rivi);
		// lukee opiskelijanumeron valiaikaiseen structiin
		if ( ! (rivivirta >> opisk.opiskelijanumero))
		     {
			tiedosto.close();
			return false;
		     }
		     
		if ( rivivirta.get() != ':')
		     {
			tiedosto.close();
			return false;
		     }
		if ( ! getline(rivivirta, opisk.nimi, ':'))
		  {
		     tiedosto.close();
		     return false;
		  }
		int indeksi = 0;
		while ( indeksi < TUNNUSLUKUJA )
		  {
		     
		     if ( ! ( rivivirta >> opisk.tunnusluvut[indeksi]) )
		       {
			  tiedosto.close();
			  return false;
		       }
		     indeksi++;
		  }
		
		if ( ! lisaa_taulukkoon(opisk, taulukko, luettu))
		  {
		     tiedosto.close();
		     return false;
		  }
		// seuraava rivi ilmoittaa, jos opiskelijoiden maksimi on
		// ylitetty
		if ( luettu == 100)
		  {
		     cout << "Virhe: syotetiedostossa " << tiedostonimi 
		       << " on liian monta riviä." << endl;
		  }
		
		
	     }
   if ( ! tiedosto.eof())
     {
	tiedosto.close();
	return false;
     }
   
   tiedosto.close();
   return true;
}


bool lisaa_taulukkoon ( Opiskelija lisattava, Opiskelija taulukko[],
			int& luettu)
{
   taulukko[luettu] = lisattava;
   ++luettu;
   
   return true;
	
	
}

int abs(int a) {
   return (a >= 0) ? a : -a;
}
     
//etsii opiskelijanumeroa vastaavan structin rivin
int a ( Opiskelija opiskelijat[], int luettu, int haku )
{  
   
   int b;
   
   b = 0;
   while ( b < luettu - 1 )
     {
	if ( haku == opiskelijat[b].opiskelijanumero )
	  {
	     break; 
	  }
	else
	  {
	     b++;
	  }
     }
   
   
	
   return b;
   
   
}


//seuraava funktio tutkii tunnuslukujen erotusta
int vertaa(const Opiskelija &opiskelija1, const Opiskelija &opiskelija2)
{
   int samanlaistenLaskuri = 0;
   int tunnuslukuIndeksi = 0;
   
   while ( tunnuslukuIndeksi < TUNNUSLUKUJA ) {
      if ((abs(opiskelija1.tunnusluvut[tunnuslukuIndeksi] - 
	       opiskelija2.tunnusluvut[tunnuslukuIndeksi])) < 3
	  or (opiskelija1.tunnusluvut[tunnuslukuIndeksi] - 
	      opiskelija2.tunnusluvut[tunnuslukuIndeksi] ) == 0) {
	 samanlaistenLaskuri++;
     
      }
      tunnuslukuIndeksi++;}
     
   return samanlaistenLaskuri;
    }


int main (void)
{
   Opiskelija opiskelijat[MAX_OPISKELIJOITA];
   int opiskelijaIndeksi = 0;
   int haku;
   int luettu;
   int yhtalaisyys;
   string tiedostonimi;
   int virhe = 0;
   // yleisiä muuttujia
   cout << "Anna tunnuslukutiedoston nimi: ";
   getline(cin, tiedostonimi);
   lueTiedosto(opiskelijat, tiedostonimi, luettu);
   
   while (true)
     {
	virhe = 0;
	opiskelijaIndeksi = 0;
	cout << "Syota tutkittava opiskelijanumero: ";
	cin >> haku;
	
	int f = a(opiskelijat, luettu, haku);
	
	if ( haku == 0 )
	  {
	     break;
	  }
	// sulkee ohjelman, jos haku = 0
	
	if ( haku != opiskelijat[f].opiskelijanumero)
	  {
	     //tutkii onko annettu opiskelijanumero laillinen
	     if ( haku < 100000 or haku > 999999 )
	       {
		  cout << "Virhe: opiskelijanumero " << haku
		    << " ei ole numero" << endl;
	       }
	     else 
	       {
		  cout << "Virhe: opiskelijanumero " << haku << " on tuntematon." << endl;
	       }
	     
	     virhe = 1;
	  }
	yhtalaisyys = 0;
	int laskuri = 0;
	
	if ( virhe == 0 )
	  {
	     
	     while ( opiskelijaIndeksi != f and opiskelijaIndeksi < luettu ) 
	       {
	   
		  yhtalaisyys = vertaa(opiskelijat[f], opiskelijat[opiskelijaIndeksi]);
		  if ( 6 == yhtalaisyys or 7 == yhtalaisyys or 8 == yhtalaisyys) {
		     cout  << "** kopioepaily (" << yhtalaisyys  << "):" << setw(3) << 
		       right <<  opiskelijat[opiskelijaIndeksi] << endl;
		     laskuri++;
		  }
	   // jostakin syystä tässä ohjelma tulostaa myös aiemmin löytyneet
	   // kopioepäillyt.
		  opiskelijaIndeksi++;
	       }
	  }
	
	if ( laskuri == 0 and virhe == 0)
	  {
	     cout << "Ei loytynyt kopioepailyja opiskelijan " 
	       << haku << " tyohon verrattuna." << endl;
	  }
	
     }
}
