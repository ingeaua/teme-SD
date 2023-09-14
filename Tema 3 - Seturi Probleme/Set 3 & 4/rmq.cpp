#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;
ifstream fin("rmq.in");
ofstream fout("rmq.out");

int RMQ [17][100001];

void buildRMQ(vector <int> v, int nrElemente)
{
    for (int i = 0; i < nrElemente; i++)
    {
        RMQ[0][i] = v[i];               /// initializam prima linie a rmq ului cu valorile vectorului
    }

    for (int i = 1; (1 << i) <= nrElemente; i++)
    {
        for (int j = 0; j + (1 << i) - 1 <= nrElemente; j++)
        {
            RMQ[i][j] = min(RMQ[i-1][j], RMQ[i-1][j + (1 << (i - 1))]);   /// aplicam formula generala pentru restul termenilor
        }
    }
}

void printRMQ(int n)    /// functie afisare rmq
{
    for (int i = 0; (1 << i) <= n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << RMQ[i][j] << " ";
        }
        cout << endl;
    }
}


int main()
{
    int nrElemente, nrIntrebari;
    cin >> nrElemente >> nrIntrebari;
    vector <int> v;
    for (int i = 0; i < nrElemente; i++)
    {
        int element;
        cin >> element;
        v.push_back(element);
    }

    buildRMQ(v, nrElemente); // construirm rmq ul (evident)

    printRMQ(nrElemente);

    for (int i = 1; i <= nrIntrebari; i++)
    {
        int capatSt, capatDr;
        cin >> capatSt >> capatDr;
        capatSt--;                  /// le scadem ca aparent in problema vectoru e numerotat de la 1.......
        capatDr--;
        int p = 31 - __builtin_clz(capatDr - capatSt + 1);
        // int p = log2(capatDr - capatSt + 1);
        // cout << "min(RMQ[" << p << "][" << capatSt << "], RMQ[" << p << "][" << capatDr - (1 << p) + 1 << "]) = ";
        fout << min(RMQ[p][capatSt], RMQ[p][capatDr - (1 << p) + 1]) << endl; /// formula pt a lua minimul de pe intervalul [st...dr]
    }                                                                               

    return 0;
}