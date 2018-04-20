#include "merge.h"

void merge(string A, string B, string C)
{
    ifstream inputA, inputB;
    inputA.open(A.c_str());
    inputB.open(B.c_str());
    ofstream output;
    output.open(C.c_str());
    int a, b;
    inputA >> a;
    inputB >> b;
    while(!inputA.eof() && !inputB.eof())
    {
        if(a<b)
        {
            output << a << " ";
            inputA >> a;
        }
        else
        {
            output << b << " ";
            inputB >> b;
        }
    }
    while(!inputA.eof())
    {
            output << a << " ";
            inputA >> a;
    }
    while(!inputB.eof())
    {
            output << b << " ";
            inputB >> b;
    }
    inputA.close();
    inputB.close();
    output.close();
}
