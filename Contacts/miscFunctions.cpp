#include "miscFunctions.h"

/*	Ber användaren om en enter tryckning. 
	Används när whitespace (från till exempel std::cin) eller liknande inte finns kvar i input buffern
	som std::cin.get() kommer registera istället för användarens ENTER tryckning
*/
void getEnter1()
{
	std::cout << "Tryck ENTER för att återgå till menyn" << std::endl;
	std::cin.get();	//Väntar på en Enter tryckning
}

/*	Ignorerar överblivna tecken i input buffern, väntar sedan på en ENTER tryckning. 
	Används när whitespace (från till exempel std::cin) eller liknande finns kvar i input buffern
	som std::cin.get() kommer registera istället för användarens ENTER tryckning
*/
void getEnter2()
{
	std::cout << "Tryck ENTER för att återgå till menyn" << std::endl;
	std::cin.ignore().get();	//Ignorerar inledande tecken i input buffern och väntar sedan på en Enter tryckning
}

//Returnerar om samtliga tecken inargumentsträngen är siffror eller inte
bool isNum(std::string a)   
{
    for(int i = 0; i<a.length(); i++) //Går igenom samtliga tecken i strängen
    {
            if(!isdigit(a[i]))  //Om tecknet på positionen i inte är en siffra, returnera falskt
                return false;     
    }
    //Om loopen tar sig igenom hela strängen är samtliga tecken sifrror, returnera då sant
    return true;    
}

/*
Returnerar antal sparade kontakter filen med det namn givet av inargumentet.
Funktionen räknar antal rader i filen för att ta reda antal sparade kontakter. 
*/
int countContacts(const char* filename) 
{
    std::ifstream savefile(filename);  
    if(!savefile)   //Om filen inte kunde öppnas, returnera felkod
    {
        std::cout << "Kunde inte öppna filen." << std::endl;	
        return -1;
    }
    int count = 0;	//Skapa en variabel som håller koll på antal kontakter
    for(int i = 1; !savefile.eof(); i++)	//Kör så länge slutet av filen inte har nåtts
    {
        gotoLine(savefile, i);	//Gå till raden i i filen
        if(i%7 == 0)	//Om i är jämnt delbart med 7 har en ny kontakt nåtts, öka variabeln
            count++;	
    }
    return count;	//Returnera antal kontakter i filen
}

//Går till en specifik rad, givet av inargument två, i en fil som är given av inargument ett.
void gotoLine(std::ifstream& file, const int num)
{
    std::string temp;	
    file.seekg(std::ios::beg);  //Går till början av filen
    for(int i=1; i < num; i++) //Kör tills den rad given av inargument två har nåtts
        getline(file, temp);	//Läser in en rad ur filen för att kunna gå till nästa rad
}

