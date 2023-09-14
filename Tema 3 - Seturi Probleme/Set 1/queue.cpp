#include <iostream>
#include <fstream>
#include <stack>
using namespace std;
ifstream fin("queue.in");
ofstream fout("queue.out");

/// o coada e implementata prin 2 stive astfel:
/// push_front inseamna push in stiva1
/// pop_front inseamna ca : daca stiva2 e goala mutam n-1 elemente din stiva1 in stiva2 si dam pop din prima
///                         daca stiva2 nu e goala pur si simplu dam pop din ea ajunge goala

int main()
{
    int n, WR;
    fin >> n;
    stack <int> stiva1, stiva2;   
    char comanda[100];
    for (int i = 1 ; i <= n; i++)
    {
        fin >> comanda;
        if (comanda[1] == 'u')
        {
            WR = 0;
            for (int j = 10; comanda[j] != ')'; j++)
            {
                WR = WR * 10 + (int(comanda[j]) - 48);
            }
            stiva1.push(WR);
            fout << i << ": read(" << WR << ") push(1," << WR <<")" << endl;  
        }
        else
        {
            if (!stiva2.empty())
            {
                WR = stiva2.top();
                stiva2.pop();
                fout << i << ": pop(2) write(" << WR << ")" << endl;
            }
            else
            {
                fout << i << ": ";
                while (stiva1.size() != 1)
                {
                    WR = stiva1.top();
                    stiva1.pop();
                    stiva2.push(WR);
                    fout << "pop(1) push(2," << WR << ") ";
                }
                WR = stiva1.top();
                stiva1.pop();
                fout << " pop(1) write(" << WR << ")" << endl;
            }
        }
    }

    return 0;
}