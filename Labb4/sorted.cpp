#include "sorted.h"

bool sorted(string a)
{
    int data;
    int prev;
    ifstream input;
    input.open(a.c_str());
    input >> prev;
    while(!input.eof())
    {
        input >> data;
        if(data<prev)
        {
            input.close();
            return false;
        }
        prev = data;
    }
    input.close();
    return true;

}