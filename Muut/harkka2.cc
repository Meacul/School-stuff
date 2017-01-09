
// Tama ohjelma laskee paketin kokonaishinnan
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

// Ensin m‰‰ritell‰‰n funktiot

int kysy_lkm();
double kysy_leveys();
double kysy_korkeus();
double kysy_syvyys();
double kysy_massa();	
double laske( double m, double k, double s, double l, int lkm  );

bool pienilkm ( int lkm );
bool pienileveys ( double l );
bool isoleveys ( double l );
bool pienikorkeus ( double k );
bool isokorkeus ( double k );
bool pienisyvyys ( double s );
bool isosyvyys ( double s );
bool pienimassa ( double m );
bool isomassa ( double m );
bool summa ( double l, double k, double s );
// Paaohjelma alkaa

int main () 
{
   int lkm = 0;
   double l = 0, s = 0, k = 0, m = 0;
   lkm = kysy_lkm();
   
// N‰m‰ if-silmukat selvitt‰v‰t onko annettu arvo hyv‰ksytt‰v‰   
   if ( pienilkm( lkm ) == false )
 
     { cout << "Virhe: pakettien lukumaaran on oltava suurempi kuin 0."; 
       return 0; }
   
   else {
      l = kysy_leveys();
   
   
      if ( pienileveys( l ) == false)
	{ cout << "Virhe: leveyden oltava suurempi kuin 0 cm." << endl; 
	  return 0; }
   
      else if ( isoleveys( l ) == false)
	{ cout << "Virhe: leveys ei saa olla yli 150 cm." << endl;
	  return 0; }
   
      else {     
   
   
	 k = kysy_korkeus();
   
	 if ( pienikorkeus( k ) == false )
	   { cout << "Virhe: korkeuden oltava suurempi kuin 0 cm." << endl; 
	     return 0; }
   
	 else if ( isokorkeus( k ) == false )
	   { cout << "Virhe: korkeus ei saa olla yli 150 cm." << endl;
	      return 0; }
   
	 else {  
   
	    s = kysy_syvyys();
   
	    if ( pienisyvyys( s ) == false )
	       { cout << "Virhe: syvyyden oltava suurempi kuin 0 cm." << endl;
		 return 0; }
   
	    else if ( isosyvyys( s ) == false ) 
	       { cout << "Virhe: syvyys ei saa olla yli 150 cm.." << endl;
		 return 0; }
   
	    else if ( summa( l, k, s  ) == false )
	      { cout << "Virhe: dimensioiden summa ei saa olla yli 250 cm" << 
		endl;
		return 0; }
   
	    else {
	       m = kysy_massa();
   
	       if ( pienimassa ( m )  == false ) 
		 { cout << "Virhe massan oltava suurempi kuin 0 kg." << endl;
		   return 0; }
   
	       else if ( isomassa( m ) == false )
		 { cout << "Virhe massa ei saa olla suurempi kuin 100 kg" << 
		   endl; 
		   return 0; }
      
// T‰m‰n j‰lkeen lasketaan lopputulos ja tulostetaan se
	       else 
		 {  

		    cout << "kokonaisrahtimaksu:" << endl;
		    
		    // /\T‰m‰ rivi m‰‰r‰‰ tulostustarkkuuden
		    cout << laske( m, k, s, l, lkm) << endl;
		    return 0;} 
	   
     
   }
   }
   }
   }
   }
// T‰ss‰ ovat ohjelman k‰ytt‰m‰t funktiot. 
// Funktiot kysy_ ottavat vastaan k‰ytt‰j‰n syˆtt‰m‰t arvot.
// Bool funktiot m‰‰r‰‰v‰t, onko arvo laillinen.
int kysy_lkm ()
{
      int g;
      cout << "Syota pakettien lkm:";
      cin >> g; 
      return g;
}

double kysy_leveys () 
{	
      double h;
      cout << "Syota paketin leveys:";
      cin >> h; 
      return h;
}

double kysy_korkeus () 
{
   double o;
   cout << "Syota paketin korkeus:";
   cin >> o; 
   return o;
}

double kysy_syvyys ()
{
   double m;
   cout << "Syota paketin syvyys:";
   cin >> m; 
   return m;
}

double kysy_massa () 
{   
   double p;
   cout << "Syota paketin massa:";
   cin >> p; 
   return p;	
}

bool pienilkm ( int lkm )
{
   if ( lkm  < 1 ) { return false; }
   else { return true; } }
   
bool pienileveys ( double l )
{   
   if ( l < 1 ) { return false; }
   else { return true; } }
   
bool isoleveys ( double l )
{
   if ( l > 150 ) { return false; }
   else { return true; } }

bool pienikorkeus ( double k )
{   
   if ( k < 1 ) { return false; }
   else { return true; } }
   
bool isokorkeus ( double k )
{
   if ( k > 150 ) { return false; }
   else { return true; } }
bool pienisyvyys ( double s )
{   
   if ( s < 1 ) { return false; }
   else { return true; } }
   
bool isosyvyys ( double s )
{
   if ( s > 150 ) { return false; }
   else { return true; } }

bool pienimassa ( double m )
{
   if ( m < 1 ) { return false; }
   else { return true; }
}

bool isomassa ( double m )
{
   if ( m > 100.00 ) { return false; }
   else { return true; }
}

	

bool summa ( double l, double k, double s )
{
   if ( l + k + s > 250.00 ) { return false; }
   else { return true; } }
	
double laske ( double m, double k, double s, double l, int lkm ) 
{   
   
   double lopputulos = 0;
   double dim_lisa = 0;
   double m_lisa = 0;
   double alennus = 0;
     
   if ( ( k > 60.00 ) or ( l > 60.00 ) or ( s > 60.00 ) 
	or ( k + s + l > 100 ))
     { dim_lisa = ( 18.50 * lkm ); }
   else 
     { dim_lisa = 0; }
	
   if ( m >= 20.00 )
     {  m_lisa = ( 13.41 * lkm ); }
   else 
     {  m_lisa = 0; }
	
   
   if ( lkm >= 20 ) { alennus = ( 0.8175 ); }
   else { alennus = 1; }
	
   lopputulos = (alennus * ( 3.65 * m * lkm + dim_lisa + m_lisa ));
   return lopputulos;
}
// Laske funktion pit‰isi laskea rahtimaksun m‰‰r‰, 
// jostakin syyst‰ se ei anna oikeaa tulosta
