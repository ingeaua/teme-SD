#include <iostream>
#include <stack>
#include <fstream>
using namespace std;
ifstream fin("paranteze.in");
ofstream fout("paranteze.out");

int main()
{
    int n, maxim = 0;
    fin >> n;
    stack <pair <int, char>> stiva; /// stiva de tipu {indice, paranteza}
    string paranteze;
    fin >> paranteze;
    for (int i = 0; i < n; i++)  
    {
        if (paranteze[i] == '(' || paranteze[i] == '[' || paranteze[i] == '{') /// deschisa -> push in stiva
        {
            stiva.push({i, paranteze[i]});
        }
        else if (!stiva.empty())    /// daca stiva nu e goala (evident)
        {
            if ((stiva.top().second == '(' && paranteze[i] == ')') ||
                (stiva.top().second == '[' &&  paranteze[i] == ']') ||  /// gasim pereche cu ultimele 2 citite (adica e un sir
                (stiva.top().second == '{' && paranteze[i] == '}'))     /// parantezat corect recursiv cumva??)
            {
                stiva.pop();
                if (!stiva.empty())                                     /// daca stiva nu e goala inseamna ca doar o subsecventa din sir
                {                                                       /// e parantezata corect
                    maxim = max(maxim, i - stiva.top().first);          
                }
                else
                {
                    maxim = max(maxim, i+1);                            /// daca toata stiva e goala inseamna ca tot sirul curent
                }                                                       /// e parantezat corect
            }
            else
            {
                stiva.push({i, paranteze[i]});                          /// daca nu se potrivesc parantezele dam push
            }
        }
    }
    fout << maxim;

    return 0;
}