#include "sorted.h"
#include "merge.h"

int main()
{
    string file;
    while(true)
    {
        cout << "Vilken fil vill du kolla om den är sorterad?"<< endl;
        cin >> file;
        ifstream input(file.c_str());
        if(input)
        {
            if(sorted(file))
                cout << "Filen " << file << " är sorterad." << endl;
            else
                cout << "Filen " << file << " är inte sorterad" << endl;
            break;
        }
        else
            cout << "Felaktig filinmatning" << endl;
    }
    merge("A", "B", "C");
    cout << "Filerna A och B är ihopslagna till den sorterade filen C" << endl;
    return 0;
}