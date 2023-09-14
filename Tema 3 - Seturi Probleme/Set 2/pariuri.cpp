#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;
ifstream fin("pariuri.in");
ofstream fout("pariuri.out");

unordered_map<int, int> bilant;

int main()
{
    int n;  // nr persoane
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        int nrPariuri;  
        fin >> nrPariuri;
        for (int j = 0; j < nrPariuri; j++)
        {
            int timp, bani;         
            fin >> timp >> bani;
            bilant[timp] += bani;
        }
    }

    fout << bilant.size() << endl;

    for (auto i = bilant.begin(); i != bilant.end(); i++)   
    {
        fout << (*i).first << " " << (*i).second << " ";
    }


    return 0;
}