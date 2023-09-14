#include <fstream>
#include <vector>
using namespace std;
ifstream fin("hashuri.in");
ofstream fout("hashuri.out");

int main()
{
    vector<vector<int>> hash(666103); // nr prim bun de la curs
    int n, x, y;
    fin >> n;
    for (int i = 1; i <= n; i++)
    {
        fin >> x >> y;
        int hashValue = y % 666103;
        if (x == 1) // inserare
        {
            hash[hashValue].push_back(y);
        }
        else if (x == 2)  // stergere
        {
            for (int j = 0; j < hash[hashValue].size(); j++)
            {
                if (hash[hashValue][j] == y)
                {
                    hash[hashValue].erase(hash[hashValue].begin() + j);
                    break;
                }
            }
        }
        else if (x == 3)    // cautare
        {
            bool ok = 0;
            for (int j = 0; j < hash[hashValue].size(); j++)
            {
                if (hash[hashValue][j] == y)
                {
                    ok = 1;
                    break;
                }
            }
            fout << ok << endl;
        }
    }

    return 0;
}