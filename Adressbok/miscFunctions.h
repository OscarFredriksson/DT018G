#include <iostream>
#include <fstream>
#include <string>

/*	Ber användaren om en enter tryckning. 
	Används när whitespace (från till exempel std::cin) eller liknande inte finns kvar i input buffern
	som std::cin.get() kommer registera istället för användarens ENTER tryckning
*/
void getEnter1();

/*	Ignorerar överblivna tecken i input buffern, väntar sedan på en ENTER tryckning. 
	Används när whitespace (från till exempel std::cin) eller liknande finns kvar i input buffern
	som std::cin.get() kommer registera istället för användarens ENTER tryckning
*/
void getEnter2();

//Kollar om samtliga tecken i en str�ng �r siffror
bool isNum(std::string a);

/*
Returnerar antal sparade kontakter filen med det namn givet av inargumentet.
Funktionen räknar antal rader i filen för att ta reda antal sparade kontakter. 
*/
int countContacts(const char* filename);

//G�r till en specifik rad, givet av inargument tv�, i en fil som �r given av inargument ett.
void gotoLine(std::ifstream& file, const int num);
