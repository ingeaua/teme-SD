#include <iostream>
#include <fstream>
#include <list>
using namespace std;

ifstream fin("mergeheap.in");
ofstream fout("mergeheap.out");


/// ----- structura de nod + functia de creare a unui nod nou -----

struct nod 
{

    int cheie, ordin;
    nod *copilStanga, *frateDreapta, *tata;  
    /// tata e intuitiv, 
    /// frateDreapta = fratele din dreapta al unui nod (frati sunt daca au acelasi tata)
    /// copilStanga = fiul cel mai din stanga al nodului
    /// pt a "traversa" fii unui nod mergi pe copil si apoi pe frati pana nu mai sunt
 
};

nod* nodNou (int cheie)
{
    nod* aux = new nod;
    aux->cheie = cheie;
    aux->ordin = 0;
    aux->copilStanga = NULL;
    aux->frateDreapta = NULL;
    aux->tata = NULL;

    return aux;
}

/// ----- functii afisare pt Heap/Arbore -----

/// ----- "afisareArbore2" este prelutata de pe GeeksForGeeks -----

void afisareArbore(list <nod*> Heap, nod* curent)
{
    cout << curent->cheie << " ";
    if (curent->frateDreapta != NULL)
    {
        afisareArbore(Heap, curent->frateDreapta);
    }
    if (curent->copilStanga != NULL)
    {
        afisareArbore(Heap, curent->copilStanga);
    }
}

void afisareArbore2(list <nod*> Heap, nod* curent)
{
    while (curent)
    {
        cout << curent->cheie << " ";
        afisareArbore2(Heap, curent->copilStanga);
        curent = curent->frateDreapta;
    }
}

void afisareHeap(list <nod*> Heap)
{
    auto itAfisare = Heap.begin();
    for (unsigned int i = 1; i <= Heap.size(); i++)
    {
        cout << "Arborele " << i << ": ";
        afisareArbore(Heap, *itAfisare);
        itAfisare++;
        cout << endl;
    }
}

/// ----- structura de HeapBinomial si toate operatiile folosite -----

struct HeapBinomial 
{

    list <nod*> Heap;

    nod* reunesteArbori(nod* arbore1, nod* arbore2) /// reuneste 2 arbori, radacina celui nod fiind in "arbore1"
    {
        if (arbore1->cheie < arbore2->cheie)
        {
            swap(*arbore1, *arbore2);
        }
        arbore2->tata = arbore1;
        arbore2->frateDreapta = arbore1->copilStanga;
        arbore1->copilStanga = arbore2;
        arbore1->ordin++;

        return arbore1;
    }

    void ajustare()   /// functie care verifica ce arbori trebuie reuniti intr-un heap
    {
        if (Heap.size() <= 1)
        {
            return;
        }
        else if (Heap.size() == 2)
        {
            if (Heap.front()->ordin == Heap.back()->ordin)
            {
                Heap.front() = reunesteArbori(Heap.front(), Heap.back());
                Heap.pop_back();
            }
            return ;
        }
        list <nod*>::iterator precedent, actual, urmator;
        precedent = Heap.begin();
        actual = precedent;
        actual++;
        urmator = actual;
        urmator++;
        while (precedent != Heap.end())
        {
            if (actual == Heap.end())
            {
                precedent++;
            }
            else if ((*precedent)->ordin < (*actual)->ordin)
            {
                precedent++;
                actual++;
                if (urmator != Heap.end())
                {
                    urmator++;
                }
            }
            else if (urmator != Heap.end() && (*precedent)->ordin == (*actual)->ordin && (*actual)->ordin == (*urmator)->ordin)
            {
                precedent++;
                actual++;
                urmator++;
            }
            else if ((*precedent)->ordin == (*actual)->ordin)
            {
                *precedent = reunesteArbori(*precedent, *actual);
                actual = Heap.erase(actual);
                if (urmator != Heap.end())
                {
                    urmator++;
                }
            }
        }

    }

    void inserare (int cheie) /// inserarea unui nod nou in heap
    {
        nod* nou = nodNou(cheie);
        Heap.push_front(nou);
        ajustare();
    }

    void extragereMaxim()
    {
        /// afiszei radacina
        /// pt a extrage minimul trebuie sa faci un heap binomial format din toti copiii radacinii
        /// stergi radacina
        /// faci reuniune intre heap ul vechi si heap ul nou

        int maxim = -1;
        auto itHeap = Heap.begin();
        auto itPozitieMaxim = Heap.begin();
        for (unsigned int i = 0; i < Heap.size(); i++)
        {
            if ((*itHeap)->cheie > maxim)
            {
                maxim = (*itHeap)->cheie;
                itPozitieMaxim = itHeap;
            }
            itHeap++;
        }
        nod* radacinaArboreMaxim = *(itPozitieMaxim);
        fout << maxim << endl;
        list <nod*> HeapNou;
        nod* nodAux = radacinaArboreMaxim->copilStanga;
        nod* nodFrate;
        while (nodAux != NULL)
        {
            nodAux->tata = NULL;
            nodFrate = nodAux->frateDreapta;
            nodAux->frateDreapta = NULL;
            HeapNou.push_front(nodAux);
            nodAux = nodFrate;
        }
        Heap.erase(itPozitieMaxim);
        HeapBinomial auxiliar;
        auxiliar.Heap = Heap;
        auxiliar.reunesteHeapuri(HeapNou); /// aici practic la Heap reunim HeapNou, adica fix operatia 3 de pe infoarena, heap nou ar trebui sa ramana gol
        Heap = auxiliar.Heap;

    }

    void reunesteHeapuri(list <nod*> &HeapAux)
    {
        /// interclasare a arborilor dupa ordin si apoi un adjust => log n
        HeapBinomial HeapNou;
        auto itHeap1 = Heap.begin();
        auto itHeap2 = HeapAux.begin();

        while (itHeap1 != Heap.end() && itHeap2 != HeapAux.end())
        {
            if ((*itHeap1)->ordin <= (*itHeap2)->ordin)
            {
                HeapNou.Heap.push_back(*itHeap1);
                itHeap1++;
            }
            else
            {
                HeapNou.Heap.push_back(*itHeap2);
                itHeap2++;
            }
        }
        while(itHeap1 != Heap.end())
        {
            HeapNou.Heap.push_back(*itHeap1);
            itHeap1++;
        }
        while(itHeap2 != HeapAux.end())
        {
            HeapNou.Heap.push_back(*itHeap2);
            itHeap2++;
        }

        HeapAux.clear();
        HeapNou.ajustare();
        Heap = HeapNou.Heap;

    }
};

/// ----- main-ul cu input ul pentru infoarena - mergeheap -----

int main()
{
    int nrMultimi, nrOperatii;
    HeapBinomial VectorHeap[101];
    fin >> nrMultimi >> nrOperatii;
    int tipOperatie, indexHeap, elementInserare, indexHeap1, indexHeap2;
    for (int i = 1; i <= nrOperatii; i++)
    {
        fin >> tipOperatie;
        if (tipOperatie == 1)
        {
            fin >> indexHeap >> elementInserare;
            VectorHeap[indexHeap].inserare(elementInserare);
        }
        else if (tipOperatie == 2)
        {
            fin >> indexHeap;
            VectorHeap[indexHeap].extragereMaxim();
        }
        else if (tipOperatie == 3)
        {
            fin >> indexHeap1 >> indexHeap2;
            VectorHeap[indexHeap1].reunesteHeapuri(VectorHeap[indexHeap2].Heap);
        }

///       afisare  a starii heap ului dupa fiecare operatie
///
///       cout << "dupa operatia " << i << ":" << endl;
///       for (int i = 1 ; i <= nrMultimi; i++)
///        {
///            cout << "Heap " << i << ": " << endl;
///            afisareHeap(VectorHeap[i].Heap);
///        }
///       cout << endl << "----------------------" << endl;
    }
    return 0;
}


