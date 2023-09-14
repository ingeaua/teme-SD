#include <iostream>
#include <fstream>
#include <stack>
using namespace std;
ifstream fin("alibaba.in");
ofstream fout("alibaba.out");

int main()
{
    int nrCif, k;
    string nr;
    fin >> nrCif >> k >> nr;
    if (k == 0)
    {
        fout << nr;
    }
    else
    {
        stack <char> stiva;
        for (int i = 0; i < nr.length(); i++)
        {
            while (!stiva.empty() && stiva.top() < nr[i] && k > 0) /// scoatem ce e in stiva mai mic decat nr curent
            {
                stiva.pop();
                k--;
            }
            stiva.push(nr[i]);
        }
        while(k) /// in caz ca numerele sunt date descrescator intra pe while ul asta si le scoate pe primele k cele mai mici
        {
            stiva.pop();
            k--;
        }
        string nrFin = "";
        while(stiva.size())   /// afisam numerele
        {   
            nrFin = stiva.top() + nrFin;
            stiva.pop();
        }
        fout << nrFin; 
    }

    return 0;
}