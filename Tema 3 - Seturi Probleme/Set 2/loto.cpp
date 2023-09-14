#include <iostream>
#include <fstream>
#include <unordered_map>
#include <tuple>
using namespace std;
ifstream fin("loto.in");
ofstream fout("loto.out");

int main()
{
    int n, vNumere[101], sumaLoto;
    unordered_map <int, tuple <int, int, int>> sumeDe3; /// avem nevoie de 6 numere deci facem suma de cate 3 numere cu toate

    fin >> n >> sumaLoto;

    for (int i = 0; i < n; i++)
    {
        fin >> vNumere[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            for (int k = j; k < n; k++) /// map [suma] = tuplu[nr1, nr2, nr3] si asa avem suma de 3 numere pt toate
            {       
                int suma = vNumere[i] + vNumere[j] + vNumere[k];
                sumeDe3[suma] = make_tuple(vNumere[i], vNumere[j], vNumere[k]);
            }
        }
    }

    bool ok = 0;

    for (int i = 0; i < n && !ok; i++)
    {
        for (int j = i; j < n && !ok; j++)
        {
            for (int k = j; k < n && !ok; k++)
            {
                int suma = vNumere[i] + vNumere[j] + vNumere[k];    /// verificam daca suma ramasa scazand din total suma a a 3 numere se
                suma = sumaLoto - suma;                             /// gaseste in map, daca da inseamna ca am gasit 6 nr ok
                if (sumeDe3.find(suma) != sumeDe3.end())            /// bam bam afisare break
                {
                    ok = 1;
                    tuple <int, int, int> tuplu;
                    tuplu = sumeDe3[suma];
                    fout << vNumere[i] << " " << vNumere[j] << " "  << vNumere[k] << " " 
                        << get<0>(tuplu) << " " << get<1>(tuplu) << " " << get<2>(tuplu) << endl;
                }
            }
        }
    }

    if (!ok)    /// conditie de mai sus nicaieri => skill issue, nu avem 6 numere cu sumaloto :(
    {
        fout << "-1";
    }

    return 0;
}