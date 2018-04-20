#include "menuFunctions.h"
#include "miscFunctions.h"

//Används för att clear screen kommandot ska fungera på både windows, linux och OSX
#ifdef WIN32	//Om systemet är windows
	const char* clear_str = "CLS";	//Sätt variabeln till windows clear screen kommando
#else	//Annars är systemet Linux eller OSX
    	const char* clear_str = "clear";	//Sätt variabeln till linux och OSX clear screen kommando
#endif

int main()
{
    char selection;	//Variabel för inmatning av menyval
    const char* filename = "contacts";	//Variabel för filnamnet till filen som kontakterna sparas i

    while(true)	//Kör fram tills programmet avslutas
    {
        system(clear_str);	//Töm skärmen
		
	    //Skriv ut menytext
        std::cout << "---------Välkommen till adressboken!----------" << std::endl;
        std::cout << "Vad vill du göra? Skriv en siffra för att välja." << std::endl;
        std::cout << "1.\tLägga till en kontakt." << std::endl;
        std::cout << "2.\tTa bort en kontakt." << std::endl;
        std::cout << "3.\tVisa alla kontakter." << std::endl;
        std::cout << "4.\tSöka efter en kontakt." << std::endl;
        std::cout << "5.\tStäng av programmet." << std::endl;
        
        std::cin >> selection;	//Ta in en inmatning av menyval
        
	    switch(selection)
        {
            case '1':	
                addContact(filename);	//Kör funtionen för att lägga till en kontakt och skickar med filnamnet till den fil kontakterna är sparade i
		getEnter1();	//Ber användaren om en Enter tryckning
                break;	
            
	    case '2':	
                removeContact(filename);	//Kör funktionen för att lägga till en kontakt och skickar med filnamnet till den fil kontakterna är sparade i
                getEnter2();	//Ber användaren om en Enter tryckning
                break;	
            
	    case '3':	
                for(int i = 1; showContact(filename,i) ;i++);	//Körs så länge funktionen showContact() lyckas att visa kontakten med listnummer i. Alltså visas samtliga kontakter i kontaktboken.
                getEnter2();	//Ber användaren om en Enter tryckning
                break;	
            
	    case '4':	
                searchContact(filename);	//Kör funktionen för att söka efter en kontakt och skickar med filnamnet till den fil konakterna är sparade i
                getEnter1();	//Ber användaren om en Enter tryckning
                break;	
            
	    case '5':	
		        return 0;	//Avsluta programmet
            
	    default:	//Om valet inte är något av ovan är inmatningen felaktig
                std::cout << "Felaktig inmatning." << std::endl;
                getEnter2();	//Ber användaren om en Enter tryckning
        }
    }
    return 0;	//Om programmet tar sig ur while(true)-loopen, avsluta programmet då något har gått fel.
}


