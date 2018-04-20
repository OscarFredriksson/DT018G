#include <iostream>
#include <fstream>
#include <string>
#include "miscFunctions.h"

/*
Lägger till en kontakt i filen med det namn som ges av inargumentet.
Användaren bes mata in samtlig information för kontakten som skrivs till filen om inmatningen är godkänd.
Programmet kör felhantering på telefonnumret och födelsedagen, om telefonnumret eller födelsedagen innehåller
något annat än siffror kommer programmet be om den inmatningen igen. Programmet kollar även så att födelsedagsinmatningen
innehåller endast siffror och att månaden är mellan 1 och 12, om någon av dessa inte stämmer kommer användaren
bes mata in på nytt.
*/
void addContact(const char* filename);	

/*
Tar bort en kontakt i filen med det namn som ges av inargumentet.
Användaren bes mata in listnumret till den kontakt den vill ta bort, men får även alternativet att
gå tillbaka till menyn, visa samtliga kontakter eller söka efter en kontakt för att enkelt kunna ta reda på dess listnummer.
När en kontakt som ska tas bort har valts får användaren frågan om den är säker på att kontakten ska tas bort.
Om användaren svarar ja skrivs samtliga kontakter utom den som ska tas bort över i en ny sparfil som sedan
döps om för att göra den till den primära filen, den gamla sparfilen tas bort.
*/
void removeContact(const char* filename);	

/*	Visar en kontakt i filen som ges av det f�rsta inargumentet p� positionen av det andra inargumentet.
Returnerar om den lyckas hitta och skriva ut en kontakt p� den positionen eller inte.	*/
bool showContact(const char* filename, const int pos);

/*	Tar in en s�kterm och s�ker efter denna i samtliga kontakter.
Kontakter som inneh�ller s�ktermen visas f�r anv�ndaren. */
bool searchContact(const char* filename);

//Returnerar positionen av den f�rsta hittade kontakt med s�ktermen givet av det andra inargumentet i filen given av det f�rsta inargumentet
int findContact(const char* filename, std::string searchterm);

