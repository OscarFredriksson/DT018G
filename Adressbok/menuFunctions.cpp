#include "menuFunctions.h"


/*
Lägger till en kontakt i filen med det namn som ges av inargumentet.
Användaren bes mata in samtlig information för kontakten som skrivs till filen om inmatningen är godkänd.
Programmet kör felhantering på telefonnumret och födelsedagen, om telefonnumret eller födelsedagen innehåller
något annat än siffror kommer programmet be om den inmatningen igen. Programmet kollar även så att födelsedagsinmatningen
innehåller endast siffror och att månaden är mellan 1 och 12, om någon av dessa inte stämmer kommer användaren
bes mata in ny data.
*/

void addContact(const char* filename)	
{
    std::ofstream savefile(filename, std::ios::app);	//Öppnar filen med filnamnet givet av inargumentet och skriver till slutet av den.
	if(!savefile)	//Om filen inte kunde öppnas, gå ur funktionen
    {
        std::cout << "Filen kunde inte öppnas. Prova att starta om programmet." << std::endl;	//Informera användaren
        return;	
    }

    std::string firstname, lastname, email, number, birthday, adress, other;	//Skapar temporära variabler

    std::cout << "Förnamn: ";   
    std::cin >> firstname;              
    savefile << firstname << std::endl; 
    
    std::cout << "Efternamn: "; 
    std::cin >> lastname;               
    savefile << lastname << std::endl;  
    
    std::cout << "Mailadress: ";
    std::cin >> email;                  
    savefile << email << std::endl;     
    
    bool loop = true;   //Skapar en variabel för inmatningsloopar
    do 
    {
        std::cout << "Telefonnummer: ";
        std::cin >> number;  
        if(isNum(number))   //Om numret består av endast siffror är inmatningen korrekt, avsluta loopen
            loop = false;   
        else    //Om numret inte består av endast siffror är inmatningen felaktig, fortsätt loopen
        {   
            std::cout << "Felaktig inmmatning, endast siffror, prova igen." << std::endl;	
            loop = true;
        }
    }while(loop);	//Körs så länge användaren matar in ett icke godkänt telefonnummer
    savefile << number << std::endl;    //Skriver telefonnumret till filen när inmatningen är godkänd  	        

    loop = true;    //Sätter default värde på loop variabeln
    do
    {
        std::cout << "Födelsedag (ÅÅÅÅMMDD): ";
        std::cin >> birthday;   
        
        if(!isNum(birthday))    //Kollar om strängen innehåller något annat än siffror
            std::cout << "Felaktig inmatning, endast siffror, prova igen." << std::endl;  
        
        else if(birthday.length() != 8)  //Kollar om inmatningen inte innehåller 8 tecken
            std::cout << "Felaktigt format, prova igen." << std::endl; 
        
        else if(stoi(birthday.substr(4,2)) < 1 || stoi(birthday.substr(4,2)) > 12)   //Kollar om månadsinmatningen inte är mellan 1 och 12           
            std::cout << "Felaktig månadsinmatning, prova igen." << std::endl;
        else    //Annars stämmer samtliga kriterier för att inmatningen ska vara korrekt
            loop = false;   //Avsluta loopen

    }while(loop);	//Körs så länge användaren matar in en icke godkänd födelsedag
    savefile << birthday << std::endl;	//Skriver födelsedagen till filen när inmatningen är godkänd  
    
    std::cin.ignore();  //Ignorerar inledande whitespace i input buffern från tidigare std::cin
    std::cout << "Adress: ";	
    std::getline(std::cin, adress);	//Läser in en hela raden då adressinmatningen kan innehålla mellanslag
    savefile << adress << std::endl;	
	
    std::cout << "Övrig information (föra att lämna tom tryck ENTER): ";
    std::getline(std::cin, other);   //Läser in en hela raden då den övriga informationen kan innehålla mellanslag
    savefile << other << std::endl; 
    std::cout << "Kontakten är tillagd!" << std::endl;
}	

/*
Tar bort en kontakt i filen med det namn som ges av inargumentet.
Användaren bes mata in listnumret till den kontakt den vill ta bort, men får även alternativet att
gå tillbaka till menyn, visa samtliga kontakter eller söka efter en kontakt för att enkelt kunna ta reda på dess listnummer.
När en kontakt som ska tas bort har valts får användaren frågan om den är säker på att kontakten ska tas bort.
Om användaren svarar ja skrivs samtliga kontakter utom den som ska tas bort över i en ny sparfil som sedan
döps om för att göra den till den primära filen, den gamla sparfilen tas bort.
*/
void removeContact(const char* filename)
{
    std::ifstream savefile(filename);   
    if(!savefile)	//Om filen inte kunde öppnas, gå ur funktionen
    {
        std::cout << "Filen kunde inte öppnas, den kanske inte existerar." << std::endl;	
	    std::cout << "Prova att lägga till en kontakt, då kommer sparfilen skapas om den inte finns." << std::endl;
        return;	
    }
    if (countContacts(filename) == 0)	//Om antal kontakter är 0, gå ur funktionen
    {
	    std::cout << "Kontaktboken är tom." << std::endl;
	    return;	
    }
    
    std::string input; //Skapar en temporär variabel för att ta in en inmatning
    int selcontact; //Skapar en temporär variabel för att lagra den valda kontakten i
    bool loop = true;   //Skapar en variabel för inmatningsloopen

    std::cout << "För att visa alla kontakter skriv 'l', för att söka efter en kontakt, skriv 's'." << std::endl; 
    std::cout << "För att gå tillbaka till menyn, skriv 'M'" << std::endl << std::endl;
    
    do
    {
	    std::cout << "Skriv kommando eller listnumret till den kontakt du vill ta bort: " << std::endl;	//Be användaren om en inmatning
        std::cin >> input;  //Ta in en inmatning av kommando

	    if (input == "l" || input == "L")
		    for (int i = 1; showContact(filename, i); i++);  //Visa samtliga kontakter
	    else if (input == "s" || input == "S")   
		    searchContact(filename);	//Kör sökfunktionen
        else if(input == "m" || input == "M")   
            	return; //Gå ur funkionen
        else if(isNum(input)) //Om inmatningen är en siffra är det ett kontaktval
        {
            selcontact = std::stoi(input, nullptr);    //Gör om kontaktvalessträngen till en integer

            
            if(selcontact < 1 || selcontact > countContacts(filename))	//Om den valda kontakten inte finns 
                std::cout << "Felaktig inmatning, försök igen." << std::endl;	
            else    //Annars är inmatningen godkänd, avsluta loopen
                loop = false;   
        }
        else    //Om inmatningen inte är ett kontaktval eller någon av de övriga valen, fortsätt loopen
            std::cout << "Felaktig inmatning, försök igen." << std::endl;
    } while(loop);	//Kör så länge inmatningen inte är godkänd
    
    char selection; //Skapar en varibel för val om kontakten ska tas bort eller inte
    std::cout << "Är du säker på att du vill ta bort kontakten (J/N):" << std::endl;
    showContact(filename, selcontact); //Visa den valda kontakten
    std::cin >> selection;  //Ta in en inmatning av val om kontakten ska tas bort eller ej
    
    if(selection == 'J' || selection == 'j')
    {
        std::ofstream tempfile("temp", std::ios::out);	//Skapar en temporär fil att föra över allt om den kontakt som ska tas bort i
		if (!tempfile)	//Om den temporära filen inte kunde öppnas, gå ur funktionen
		{
			std::cout << "En temporär fil för borttagning av kontakten kunde inte skapas, starta om programmet och prova igen." << std::endl;
			return;
		}
        gotoLine(savefile, 1);  //Går till första raden i sparfilen
        std::string temp;   //Skapar en temporär sträng att använda vid överföring av rader till den temporära filen
    
		/*	Kör så länge i är mindre än antalet rader i filen efter att en kontakt har tagits bort.
			Varje kontakt tar upp 7 rader och en extrarad kommer alltid att finnas efter den sista kontakten.
			Detta innebär att antalet rader i sparfilen är 7 * antal kontakter + 1.
		*/
        for(int i = 1; i < 7*(countContacts(filename)-1)+1; i++)	
        {
            if(i == 7*selcontact-6) //Om den första raden av den valda kontakten är nådd
                gotoLine(savefile, 7*selcontact+1); //Gå till raden efter den valda kontakten
            std::getline(savefile, temp);   //Ta en rad ur sparfilen och spara i den temporära strängen
            tempfile << temp << std::endl;  //Skriv över strängen i den temporära filen
        }
        savefile.close();
        tempfile.close();
        remove(filename);   //Ta bort den primära filen och döp om den temorära filen för att göra den den primära filen
        rename("temp", filename);   
		std::cout << "Kontakten har tagits bort." << std::endl;
	}
}

/*	Visar en kontakt i den fil som ges av det första inargumentet på positionen av det andra inargumentet. 
	Returnerar om den lyckas hitta och skriva ut en kontakt på den positionen eller inte.
*/
bool showContact(const char* filename, int pos)
{
    std::ifstream savefile(filename);   
	if (!savefile)	//Om filen inte kunde öppnas, returnera att den valda kontakten inte kunde visas
	{
		std::cout << "Filen kunde inte öppnas, den kanske inte existerar." << std::endl;	
		std::cout << "Prova att lägga till en kontakt, då kommer sparfilen skapas om den inte finns." << std::endl;
		return false;
	}
	if (countContacts(filename) == 0)	//Om antal kontakter är 0, returnera att den valda kontakten inte kunde visas
	{
		std::cout << "Kontaktboken är tom." << std::endl;
		return false;
	}
    
    //Skapar en array av strings för att förenkla utskrivningen av månaden i födelsedagen
    std::string months[12] = { "Januari","Februari","Mars","April","Maj","Juni","Juli","Augusti","September","Oktober","November","December" };
    std::string firstname, lastname, email, number, birthday, adress, other; //Skapar temporära variabler

    for(int i = -6; i<1; i++)   //Går igenom kontaktens 7 variabler.
	{
        gotoLine(savefile, (7*pos+i));  /*	Går till kontaktens första rad i filen.
											Varje kontakt tar upp 7 rader, vilket innebär att den första raden av 
											en given kontakt är rad nummer: 7 * kontaktens listnummer - 6	*/
	
        if(i == -6)	//Om i är -6 ska kontaktens förnamn läsas in
	        savefile >> firstname;	
        if(i == -5)   //Om i är -5 ska kontaktens efternamn läsas in
            savefile >> lastname;	
        if(i == -4)   //Om i är -4 ska kontaktens emailadress läsas in
            savefile >> email;	
        if( i== -3)   //Om i är -3 ska kontaktens telefonnummer läsas in
            savefile >> number;	
        if(i == -2)   //Om i är -2 ska kontaktens födelsedag läsas in
            savefile >> birthday;	
	if(i == -1)	//Om i är -1 ska kontaktens födelsedag läsas in
		std::getline(savefile, adress);	//Läser in hela raden då adressen kan innehålla mellanslag
	if(i == 0)    //Om i är 0 ska kontaktens övriga information läsas in
            std::getline(savefile, other);	//Läser in hela raden då den övriga informationen kan innehålla mellanslag
    }

    if(firstname == "")	//Om förnamnet är tomt finns inte kontakten eller kunde inte kontakten läsas in korrekt
        return false;    //returnerar att kontakten inte kunde visas
	else	//Annars finns kontakten
	{
        std::cout << pos << ". " << firstname << " " << lastname << std::endl;  //Skriver ut kontaktens listnummer, följ av för och efternamn
        std::cout << "   Email: " << email << std::endl;
        std::cout << "   Telefonnummer: " << number << std::endl;
            
        std::cout << "   Födelsedag: " << birthday.substr(6,2) << " " //Skriver ut de sista två tecknen i strängen, alltså dagen
                                        << months[stoi(birthday.substr(4,2))-1] << " " //Gör om månadssträngen till en integer och använder months[] för att skriva ut månaden
                                        << birthday.substr(0,4) << std::endl;   //Skriver ut de första fyra tecknen, alltså året
        
	    std::cout << "   Adress: " << adress << std::endl;  
        std::cout << "   Övrig information: " << other << std::endl << std::endl;
        return true;	//returnera att kontakten hittades och kunde skrivas ut
    }
}

/*	Tar in en sökterm och söker efter denna i samtliga kontakter.
	Kontakter som innehåller söktermen visas för användaren. 
	Returnerar om en eller flera kontakter hittades eller ej.*/
bool searchContact(const char* filename)
{
    std::string searchterm;	//Skapa en variabel för söktermen
    std::cout << "Skriv in sökterm: ";	
    std::cin.ignore();
    std::getline(std::cin, searchterm); //Ta in sökterm
    
	bool foundnone = true;	//Skapa en variabel för om funktionen hittar en kontakt som innehåller söktermen eller inte
    for(int i = 1; i != 0;)	//Funktionen foundContact() returnerar 0 när ingen kontakt kunde hittas med söktermen, kör tills dess
    {
        i = findContact(filename, searchterm);	//Söker efter en kontakt i filen med filnamnet givet av inargumentet som innehåller söktermen
        if(i != 0)	//Om en kontakt hittades
        {
            foundnone = false;	//Säg att funktionen har hittat en kontakt med söktermen
            std::cout << "Hittad kontakt: " << std::endl;	
            showContact(filename, i);	//Skriv ut kontakten på skärmen
        } 
    }
	if (foundnone)	//Om ingen kontakt hittades, returnera false
	{
		std::cout << "Hittade ingen kontakt med söktermen \"" << searchterm << "\"." << std::endl;
		return false;
	}
	else    //Annars har en eller flera kontakter hittats, returnera true
		return true;    
}

//Returnerar positionen av den första hittade kontakt med söktermen givet av det andra inargumentet i filen given av det första inargumentet.
int findContact(const char* filename, std::string searchterm)
{
    for(int i = 0; i<searchterm.length(); i++)	//gör samtliga tecken i söktermen till gemener
        searchterm[i] = tolower(searchterm[i]);
    
    std::ifstream savefile(filename);   
	if (!savefile)	//Om filen inte kunde öppnas, returnera att ingen kontakt kunde hittas
	{
		std::cout << "Filen kunde inte öppnas, den kanske inte existerar." << std::endl;	
		std::cout << "Prova att lägga till en kontakt, då kommer sparfilen skapas om den inte finns." << std::endl;
		return 0;	
	}
	if (countContacts(filename) == 0) //Om antal kontakter är 0, returnera att ingen kontakt kunde hittas
	{
		std::cout << "Kontaktboken är tom." << std::endl;
		return 0;	
	}
	static int foundcontact = 0;	//Skapar en statisk variabel för att hålla koll på senaste hittade kontakt.

	/*	Går till raden efter den senast hittade kontakten.
		Varje kontakt tar upp 7 rader, vilket innebär att den första raden av 
		en given kontakt är rad nummer: 7 * kontaktens listnummer - 6	*/
    gotoLine(savefile, 7*(foundcontact+1)-6);  
    
    for(int i = 0;!savefile.eof();i++)  //Kör så länge filens slut inte har nåtts
    {
        if(i%7 == 0)    // loopen når en ny kontakt var 7e varv, öka då variabeln för kontaktens listnummer    
            foundcontact++; 

        std::string temp;   //Skapa en temporär sträng
        getline(savefile,temp); //Hämta en rad ur filen
        
        //gör samtliga tecken i den temporära strängen till gemener
        for(int k = 0;k<temp.length(); k++) 
            temp[k] = tolower(temp[k]);

        if(temp.find(searchterm) != std::string::npos)  //Om den temporära strängen innehåller söktermen
            return foundcontact; //Returnera den hittade kontaktens listnummer 
        
    }
    foundcontact = 0;   //Återställ den statiska variablen
    return 0;   //Returnera att ingen kontakt kunde hittas med söktermen
}


