#include <iostream>
using namespace std;

int main()
{	
	int data;
	int min;
	int max;
	int summa = 0;
	int antal = 0;
	for(;cin >> data;antal++,summa+=data)
	{	 
	
		if(antal == 0)
		{
			max = data;
			min = data;
		}
		else if(data>max)
		{
			max = data;	
		}	
		else if(data<min)
		{
			min = data;
		}
	}
	cout << "Minsta: " << min << endl;
	cout << "Stösta: " << max << endl;
	cout << "Medel: " << (float)summa/antal << endl;
	return 0;
}
