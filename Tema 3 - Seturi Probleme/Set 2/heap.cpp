#include <fstream>
#include <set>
#include <vector>
using namespace std;
ifstream fin("heapuri.in");
ofstream fout("heapuri.out");

/// setu foloseste un Binary Search Tree ca spre deosebire de unordered set iti si sorteaza elementele
/// asa ca folosind un set si un vector putem sa facem toate operatiile de care avem nevoie :P

int main()
{
    set <int> heappy; // word play
    vector <int> v;

    int n;
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        int op;
        fin >> op;
        {
            if (op == 1)
            {
                int element;
                fin >> element;
                heappy.insert(element);
                v.push_back(element);
            }
            else if (op == 2)
            {
                int indexElement;
                fin >> indexElement;
                heappy.erase(v[indexElement-1]);
            }
            else if (op == 3)
            {
                fout << *heappy.begin() << endl;
            }
        }
    }

    return 0;
}