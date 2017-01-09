// Tämä ohjelma laskee tentin pistetuloksen.
// jos käyttäjä syöttää numeromuuttujien tilalle 
// jotain muuta, joutuu ohjelma ikuiseen kierteeseen
// (c)Kyösti Nyrhilä 2012 (kyosti.nyrhila@tut.fi)
#include <iostream>
#include <cmath>
using namespace std;

  
int main()
{
   char a = '?';
   while( true )
// Tämä while mahdollistaa alkuun palaamisen continue komennolla
     {
      cout << "Haluatko laskea lisaa kokonaispisteita(k/e): ";
      cin >> a;
      if ( a == 'e' )
       {
         return 0;	
       }
//tässä kohdassa return 0 -komennolla suljetaan ohjelma   
      else if ( a != 'k')
       {
			 
         cout << "Virheellinen syote, aloita alusta!" << endl;
         continue;    	      }
      else{
         int ht1 = 0;//ensimmäisen harjoituksen pisteet
         int ht2 = 0;//2. -.-
         int ht3 = 0;//3. -.-
         int ht4 = 0;//4. -.-
         int bonusp = 0;// harjoituksista tulleet lisäpisteet
         int lasnaolo = 0;//viikkoharjoitusten läsnäolojen määrä
         int lbonus = 0;//läsnäolosta tulleet lisäpisteet
         int tentti = 0;//tentin pisteet
         int fin = 0;// lopullinen pistetulos
         int kok = 0;// väliaikainen muuttuja, jota tarvittiin virheenpoistossa
         cout << "Syota arvostelijan antamat harjoitustyon 01 pisteet:";
         cin >> ht1; 
         cout << "Syota arvostelijan antamat harjoitustyon 02 pisteet:";
         cin >> ht2;
         cout << "Syota arvostelijan antamat harjoitustyon 03 pisteet:";
         cin >> ht3;
         cout << "Syota arvostelijan antamat harjoitustyon 04 pisteet:";
         cin >> ht4;
         int harj = ((15 * ht1) + (20 * ht2) + (30 * ht3) + (40 * ht4)) / 20;
         if ( harj < 61 )//tämä if-komponentti selvittää bonusp:n arvon
	{
	  bonusp = -99 ; }
         else if ( harj == 61 )
	{
	   bonusp = -38 ;
	}
         else if ( harj == 62 )
	{
	  bonusp = -32 ;
	}
         else if ( harj == 63 )
	{
	  bonusp = -27 ;
	}
         else if ( harj == 64 )
	{
	  bonusp = -23 ;
	}
         else if ( harj == 65 )
	{
	  bonusp = -20 ;
	}
         else if ( harj == 66 )
	{
	  bonusp = -17 ;
	}
         else if ( harj == 67 )
	{
	  bonusp = -14 ;
	}
         else if ( harj == 68 )
	{
	  bonusp = -11 ;
	}
         else if ( harj == 69 )
	{
	  bonusp = -8 ;
	}
         else if ( harj == 70 )
	{
	  bonusp = -5 ;
	}
         else if ( harj == 71 )
	{
	  bonusp = -4 ;
	}
         else if ( harj == 72 )
	{
	  bonusp = -3 ;
	}
         else if ( harj == 73 )
	{
	  bonusp = -2 ;
	}
         else if ( harj == 74 )
	{
	  bonusp = -1 ;
	}
         else if ( harj == 75 )
	{
	  bonusp = 0 ;
	}
         else if ( harj >= 76 and harj <= 80 )
	{
	  bonusp = 1 ;
	}
         else if ( harj >= 81 and harj <= 85 )
	{
	  bonusp = 2 ;
	}
         else if ( harj >= 86 and harj <= 90 )
	{
	  bonusp = 3 ;
	}
         else if ( harj >= 91 and harj <= 95 )
	{
	  bonusp = 4 ;
	}
         else if ( harj >= 96 and harj <= 100)
	{
	  bonusp = 5 ;
	}
         else 
	{
	  bonusp = 5 ;
	}
         cout << "Syota viikkoharjoituslasnaolojen lukumaara:";
         cin >> lasnaolo;
         if ( lasnaolo <= 6 )//tämä if komponentti selvittää lbonus:n arvon
 	{
	   lbonus = 0 ;
	}
         else if ( lasnaolo == 7 )
	{
	   lbonus = 1 ;
	}
         else if ( lasnaolo == 8 ) 
	{
	   lbonus = 2 ;
	}
         else if ( lasnaolo == 9 )
	{     
	   lbonus = 3 ;
	}
         else if ( lasnaolo == 10 )
	{
	   lbonus = 4 ;
	}
         else if ( lasnaolo == 11 )
	{
	   lbonus = 6 ;
	}
         else if ( lasnaolo == 12 )
	{
	   lbonus = 8 ;
	}
         else if ( lasnaolo == 13 )
	{
	   lbonus = 10 ;
	}
         else if ( lasnaolo == 14 )
	{
	   lbonus = 12 ;
	}
         else
	{
	   lbonus = 12;
	}
         cout << "Syota tenttipisteet:";
         cin >> tentti;
         kok = tentti + bonusp + lbonus;
         if ( kok <= 0 )//tämä if-komponentti poistaa epäloogiset tulokset
	{
           fin = 0;  
	}
         else if ( kok >= 100 )
	{
	   fin = 100;
	}
         else
	{
	   fin = kok;
	}
         cout << "Lopulliset kokonaispisteet: ";
         cout << fin;
         cout << endl;  
     continue;}
     }
return 0;   
}
