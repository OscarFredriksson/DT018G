#include <iostream> 
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string name, number, adress;
    ifstream input;
    input.open("names.txt"); 
    while(getline(input, name) && getline(input, number) && getline(input, adress))
    {   
        name = name.substr(name.find(" ")+1) + ", " + name.substr(0,name.find(" "));
        if((number.at(8)-'0') % 2 != 0)
            name.append(" [M]");
        else
            name.append(" [K]");       
        cout << name << endl << adress << endl;
    }
    input.close();
    return 0;
}^