#include <iostream>
#include <unordered_set>
#include <fstream>
using namespace std;
ifstream fin("muzica.in");
ofstream fout("muzica.out");

int main()
{
    long long nVasile, nDJ, a, b, c, d, e, cnt = 0, melodie; 
    unordered_set <long long> playlistVasile;
    fin >> nVasile >> nDJ;
    fin >> a >> b >> c >> d >> e;

    for (int i = 0; i < nVasile; i++)   /// citim playlist ul lui vasile
    {
        fin >> melodie;
        playlistVasile.insert(melodie);
    }

    long long mel1 = a, mel2 = b;

    if (playlistVasile.find(mel1) != playlistVasile.end()) /// verificam daca prima melodie a dj ului e in playlist vasile
    {
        playlistVasile.erase(mel1);                         /// cand gasim vreuna in playlist o scoatem ca sa nu mai dam de ea
        cnt++;                                               /// (se precizeaza ca vasile are playlist cu piese unice)
    }

    if (playlistVasile.find(mel2) != playlistVasile.end()) /// same si pt a doua
    {
        playlistVasile.erase(mel2);
        cnt++;
    }

    for (int i = 2; i < nDJ; i++)
    {  
        long long mel = (c * mel2 + d * mel1) % e;          /// folosind formula verificam pentru fiecare in parte acelasi lucru
        if (playlistVasile.find(mel) != playlistVasile.end())
        {
            playlistVasile.erase(mel);
            cnt++;
        }
        mel1 = mel2;
        mel2 = mel;
    }
    
    fout << cnt;

    return 0;
}