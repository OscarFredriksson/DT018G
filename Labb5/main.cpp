#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream input;
    input.open("hitchhikersguide.txt");
    std::map<std::string, int> count;
    std::string word;
    while(input >> word)
    {
        std::string temp;
        for(int i = 0; i < word.length(); i++)
        {
            word[i] = tolower(word[i]);
            if(isalpha(word[i]))
                temp+=word[i];
        }
        if(!temp.empty())
            count[temp]++;
    }
    std::vector<std::pair<int, std::string>> sort;

    for(auto &a : count)
        sort.push_back(make_pair(a.second, a.first));
        
    std::sort(sort.rbegin(), sort.rend());
    int n;
    std::cout << "Detta program skriver ut de n mest förekommande orden i filen." << std::endl;
    std::cout << "n: ";
    std::cin >> n;

    for(int i = 0; i < n; i++)
        std::cout << i+1 << ". Ordet \""<< std::get<1>(sort[i]) << "\" förekommer " << std::get<0>(sort[i]) << " gånger." << std::endl;
    
    return 0;
}