#include <iostream>
using namespace std;

int hotel[10], n;

/// e efectiv bruteforce, luam fiecare comanda si o executam
/// L - punem un 1 cat mai in stanga in vector
/// R - punem un 1 cat mai in dreapta in vector
/// nr - hotel[nr] = 0

int main()
{
    
    cin >> n;
    char amugae;
    for (int i = 0; i < n; i++)
    {
        cin >> amugae;
        if (amugae == 'L')
        {
            for (int j = 0; j < 10; j++)
            {
                if (hotel[j] == 0)
                {
                    hotel[j] = 1;
                    break;
                }
            }
        }
        if (amugae == 'R')
        {
            for (int j = 9; j >= 0; j--)
            {
                if (hotel[j] == 0)
                {
                    hotel[j] = 1;
                    break;
                }
            }
        }
        if (amugae >= '0' && amugae <= '9')
        {
            hotel[amugae - 48] = 0;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        cout << hotel[i];
    }

    return 0;
}