#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
ifstream fin("proc2.in");
ofstream fout("proc2.out");


int main()
{
    int n, m;
    fin >> n >> m;
    priority_queue <int> procesoareLibere;              
    priority_queue <pair <int, int>> eliberareProcesoare; // pair {cand se elibereaza, pe ce procesor ruleaza}, compararea e dupa eliberare

    for (int i = 1; i <= n; i++)                         
    {                                                   
        procesoareLibere.push(-i); // la inceput toate procesoarele libere, le punem cu - ca sa mearga pq ul cum trebuie
    }                              // ca au prioritate alea mai mari si nu am reusit sa fac cu greater

    for (int i = 1; i <= m; i++)
    {
        int start, durata;
        fin >> start >> durata;
        // eliminam task urile care sunt gata pana incepe cel citit 
        while (!eliberareProcesoare.empty() &&  -eliberareProcesoare.top().first <= start) /// <= pt ca e interval deschis la dreapta la durata
        {
            procesoareLibere.push(eliberareProcesoare.top().second);
            eliberareProcesoare.pop();
        }
        // ocupam procesoru pentru task ul curent, afisam, scoatem procesor din disponibile
        eliberareProcesoare.push({-start - durata, procesoareLibere.top()});
        fout << -procesoareLibere.top() << endl;
        procesoareLibere.pop();
    }

    return 0;
}