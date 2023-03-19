#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;
using namespace std::chrono;

double medie_counting, medie_radix10, medie_radix64, medie_radix2la16, medie_bubble, medie_shell, medie_merge, medie_stl;

/// ----- RadixSort -----

void count(long long* vector, int length, int pozitie, int baza)    /// pozitie = la a cata pozitie ne uitam (abordarea LSD)
{
    int *vCount = new int[baza];
    for (int i = 0; i < baza; i++)
    {
        vCount[i] = 0;
    }
    for (int i = 0; i < length; i++)
    {
        vCount[(vector[i] / pozitie) % baza]++;       /// calculam cate elemente avem cu fiecare pozitie
    }
    for (int i = 1; i < baza; i++)
    {
        vCount[i] += vCount[i-1];                   /// actualizam array ul
    }
    long long *vAux = new long long[length];
    for (long long i = length - 1; i >= 0; i--)
    {
        vAux[--vCount[(vector[i] / pozitie) % baza]] = vector[i];
    }
    for (long long i = 0; i < length; i++)
    {
        vector[i] = vAux[i];
    }

    delete[] vCount;
    delete[] vAux;
}

void radix_sort(long long* vector, int length, int baza = 10)
{
    /// aflam maximul pentru a putea stii numarul de cifre
    long long maxim = vector[0];
    for (long long i = 0; i < length; i++)
    {
        if (vector[i] > maxim)
        {
            maxim = vector[i];
        }
    }

    for (long long pozitie = 1; maxim / pozitie > 0; pozitie *= baza)
    {
        if (baza > 10)
        {
        }
        count(vector, length, pozitie, baza);
    }
}

/// ----- MergeSort -----

void merge(long long *vector, int stanga, int mijloc, int dreapta)
{
     int i = stanga, j = mijloc+1;
     int k = 0;
    long long *vAux = new long long[dreapta-stanga+1];

     while (i <= mijloc && j <= dreapta)
     {
         if (vector[i] <= vector[j])
         {
            vAux[k++] = vector[i++];
         }
         else
         {
             vAux[k++] = vector[j++];
         }
     }
     if (i > mijloc)
     {
         while (j <= dreapta)
         {
             vAux[k++] = vector[j++];
         }
     }
     else
     {
         while (i <= mijloc)
         {
             vAux[k++] = vector[i++];
         }
     }
     k = 0;
     for (int i = stanga; i <= dreapta; i++)
    {
         vector[i] = vAux[k++];
    }
     delete[] vAux;
}

void merge_sort(long long *vector, int stanga, int dreapta)
{
    if (stanga < dreapta)
    {
        int mijloc = (stanga + dreapta) / 2;
        merge_sort(vector, stanga, mijloc);
        merge_sort(vector, mijloc+1, dreapta);
        merge(vector, stanga, mijloc, dreapta);
    }
}

/// ----- ShellSort -----

void shell_sort(long long *vector, int length)
{
    for (int gap = length / 2; gap >= 1; gap /= 2)
    {
        for (int j = gap; j < length; j++)
        {
            for (int i = j - gap; i >= 0; i -= gap)
            {
                if (vector[i + gap] > vector[i])
                {
                    break;
                }
                else
                {
                    swap(vector[i+gap],vector[i]);
                }
            }
        }
    }
}


/// ----- CountingSort -----

void counting_sort(long long *vector, int length)
{
    int maxim = vector[0];
    for (int i = 0; i < length; i++)
    {
        if (vector[i] > maxim)
        {
            maxim = vector[i];
        }
    }
    long long *count = new long long[maxim+1];
    for (int i = 0; i <= maxim; i++)
    {
        count[i] = 0;
    }
    for (int i = 0; i < length; i++)
    {
        count[vector[i]]++;
    }
    int poz = 0;
    for (int i = 0; i <= maxim; i++)
    {
        for (int j = 1; j <= count[i]; j++)
        {
            vector[poz++] = i;
        }
    }
    delete[] count;
}

/// ----- BubbleSort -----

void bubble_sort(long long *vector, int length)
{
    for (int i = 0; i < length; i++)
    {
        bool sorted = true;
        for (int j = 0; j < length - i - 1; j++)
        {
            if (vector[j] > vector[j+1])
            {
                swap(vector[j],vector[j+1]);
                sorted = false;
            }
        }
        if (sorted)
        {
            break;
        }
    }
}

/// functie de generare a vectorilor random de dimensiune "length" cu valoarea elementelor pana la "maxim"

void genereaza_vector_random(long long *vector, int length, long long maxim)
{
    std::random_device numere_rand;
    std::uniform_int_distribution<int> dist(1, maxim);
    for (long long i = 0; i < length; i++)
    {
        vector[i] = dist(numere_rand);
    }
}

/// functie de generare a vecotrului aproape sortat cu "length" elemente

void genereaza_vector_aproape_sortat(long long *vector, int length)
{
    for (int i = 0; i < length; i++)
    {
        vector[i] = i + 1;
    }

    std::random_device numere_rand;
    std::uniform_int_distribution<int> dist(length/1000, length/500);
    int nr_transpozitii = dist(numere_rand);

    std::random_device transpozitie;
    std::uniform_int_distribution<int> transpoz(0, length-1);

    for (int i = 0; i < nr_transpozitii; i++)
    {
        int i1 = transpoz(transpozitie);
        int i2 = transpoz(transpozitie);
        swap(vector[i1], vector[i2]);
    }
}

/// functie de generare a vectorului reversed de lungime "length"

void genereaza_vector_reversed(long long *vector, int length)
{
    for (int i = 0; i < length; i++)
    {
        vector[i] = length - i;
    }
}

/// functie de generare a vectorului sortat de lungime "length"

void genereaza_vector_sortat(long long *vector, int length)
{
    for (int i = 0; i < length; i++)
    {
        vector[i] = i + 1;
    }
}


/// functie de copiere pt vectori

void copiere(long long *v1, long long *v2, int length)    /// v1 = v2
{
    for (long long i = 0; i < length; i++)
    {
        v1[i] = v2[i];
    }
}

/// functie verificare sortare

bool verificare_sortare(long long *vector, int length)
{
    if (length == 1)
    {
        return 1;
    }
    for (int i = 0; i < length-1; i++)
    {
        if (vector[i] > vector[i+1])
        {
            return 0;
        }
    }
    return 1;
}

/// functie de afisare vector

void afisare(long long *vector, int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << vector[i] << " ";
    }
    cout << endl;
}


/// functia pentru teste

void sortari(long long *vector, int length)
{
    long long* vAux = new long long[length];


    cout << endl <<"-----RADIX SORT(baza 10)-----" << endl;
    copiere(vAux, vector, length);
    auto start1 = system_clock::now();
    radix_sort(vAux, length);
    auto stop1 = system_clock::now();
    auto durata1 = duration_cast<microseconds>(stop1 - start1);
    medie_radix10 += (double)durata1.count() / 1000;
    cout << "Durata sortare: " << (double)durata1.count()/1000 << " de milisecunde" << endl;
    if (verificare_sortare(vAux, length))
    {
        cout << "Vectorul a fost sortat corect" << endl;
    }
    else
    {
        cout << "Exista probleme la sortare" << endl;
    }



    cout << endl << "-----RADIX SORT(baza 2^6)-----" << endl;
    copiere(vAux, vector, length);
    auto start2 = system_clock::now();
    radix_sort(vAux, length, 64);
    auto stop2 = system_clock::now();
    auto durata2 = duration_cast<microseconds>(stop2 - start2);
    medie_radix64 += (double)durata2.count() / 1000;
    cout << "Durata sortare: " << (double)durata2.count()/1000 << " de milisecunde" << endl;
    if (verificare_sortare(vAux, length))
    {
        cout << "Vectorul a fost sortat corect" << endl;
    }
    else
    {
        cout << "Exista probleme la sortare" << endl;
    }



    cout << endl <<"-----RADIX SORT(baza 2^16)-----" << endl;
    copiere(vAux, vector, length);
    auto start3 = system_clock::now();
    radix_sort(vAux, length, 65536);
    auto stop3 = system_clock::now();
    auto durata3 = duration_cast<microseconds>(stop3 - start3);
    medie_radix2la16 += (double)durata3.count() / 1000;
    cout << "Durata sortare: " << (double)durata3.count()/1000 << " de milisecunde" << endl;
    if (verificare_sortare(vAux, length))
    {
        cout << "Vectorul a fost sortat corect" << endl;
    }
    else
    {
        cout << "Exista probleme la sortare" << endl;
    }



    cout << endl <<"-----MERGE SORT-----" << endl;
    copiere(vAux, vector, length);
    auto start4 = system_clock::now();
    merge_sort(vAux, 0, length-1);
    auto stop4 = system_clock::now();
    auto durata4 = duration_cast<microseconds>(stop4 - start4);
    medie_merge += (double)durata4.count() / 1000;
    cout << "Durata sortare: " << (double)durata4.count()/1000 << " de milisecunde" << endl;
    if (verificare_sortare(vAux, length))
    {
        cout << "Vectorul a fost sortat corect" << endl;
    }
    else
    {
        cout << "Exista probleme la sortare" << endl;
    }



    cout << endl <<"-----SHELL SORT-----" << endl;
    copiere(vAux, vector, length);
    auto start5 = system_clock::now();
    shell_sort(vAux, length);
    auto stop5 = system_clock::now();
    auto durata5 = duration_cast<microseconds>(stop5 - start5);
    medie_shell += (double)durata5.count() / 1000;
    cout << "Durata sortare: " << (double)durata5.count()/1000 << " de milisecunde" << endl;
    if (verificare_sortare(vAux, length))
    {
        cout << "Vectorul a fost sortat corect" << endl;
    }
    else
    {
        cout << "Exista probleme la sortare" << endl;
    }



    cout << endl <<"-----COUNTING SORT-----" << endl;
    copiere(vAux, vector, length);
    auto start6 = system_clock::now();
    counting_sort(vAux, length);
    auto stop6 = system_clock::now();
    auto durata6 = duration_cast<microseconds>(stop6 - start6);
    medie_counting += (double)durata6.count() / 1000;
    cout << "Durata sortare: " << (double)durata6.count()/1000 << " de milisecunde" << endl;
    if (verificare_sortare(vAux, length))
    {
        cout << "Vectorul a fost sortat corect" << endl;
    }
    else
    {
        cout << "Exista probleme la sortare" << endl;
    }



    cout << endl <<"-----STL SORT-----" << endl;
    copiere(vAux, vector, length);
    auto start7 = system_clock::now();
    std::sort(vAux, vAux + length);
    auto stop7 = system_clock::now();
    auto durata7 = duration_cast<microseconds>(stop7 - start7);
    medie_stl += (double)durata7.count() / 1000;
    cout << "Durata sortare: " << (double)durata7.count()/1000 << " de milisecunde" << endl;
    if (verificare_sortare(vAux, length))
    {
        cout << "Vectorul a fost sortat corect" << endl;
    }
    else
    {
        cout << "Exista probleme la sortare" << endl;
    }



    cout << endl <<"-----BUBBLE SORT-----" << endl;
    copiere(vAux, vector, length);
    auto start8 = system_clock::now();
    bubble_sort(vAux, length);
    auto stop8 = system_clock::now();
    auto durata8 = duration_cast<microseconds>(stop8 - start8);
    medie_bubble += (double)durata8.count() / 1000;
    cout << "Durata sortare: " << (double)durata8.count()/1000 << " de milisecunde" << endl;
    if (verificare_sortare(vAux, length))
    {
        cout << "Vectorul a fost sortat corect" << endl;
    }
    else
    {
        cout << "Exista probleme la sortare" << endl;
    }

    delete[] vAux;
}

int main()
{
    int tip_test;
    cout << "-------------------------------" << endl;
    cout << "Introduceti un numar care sa reprezinte tipul testului" << endl;
    cout << "1 - Testare pe vector random (cu MAX introdus de la tastatura)" << endl;
    cout << "2 - Testare pe vector aproape sortat" << endl;
    cout << "3 - Testare pe vector descrescator" << endl;
    cout << "4 - Testare pe vector crescator" << endl;
    cin >> tip_test;
    while(tip_test != 1 && tip_test != 2 && tip_test != 3 && tip_test != 4)
    {
        cout << "!! INTRODUCETI UN NUMAR VALID !!" << endl;
        cin >> tip_test;
    }

    int nr_teste;
    if (tip_test != 3 && tip_test != 4)
    {
        cout << "-------------------------------" << endl;
        cout << "Introduceti numarul de teste: ";
        cin >> nr_teste;
    }
    else
    {
        nr_teste = 1;
    }


    cout << "-------------------------------" << endl;
    long long nr_elemente, maxim;
    cout << "Introduceti numarul de elemente dintr-un vector: ";
    cin >> nr_elemente;
    if (tip_test == 1)
    {
        cout << "Introduceti maximul: ";
        cin >> maxim;
    }
    else
    {
        maxim = nr_elemente;
    }

    for(int i = 1; i <= nr_teste; i++)
    {
        long long* vector = new long long[nr_elemente];
        if (tip_test == 1)
        {
            genereaza_vector_random(vector, nr_elemente, maxim);
        }
        else if(tip_test == 2)
        {
            genereaza_vector_aproape_sortat(vector, nr_elemente);
        }
        else if(tip_test == 3)
        {
            genereaza_vector_reversed(vector, nr_elemente);
        }
        else
        {
            genereaza_vector_sortat(vector, nr_elemente);
        }

        /// afisare(vector, nr_elemente);
        cout << endl << "----- TEST " << i << " ----- " << endl;
        sortari(vector, nr_elemente);
        delete[] vector;
        cout << endl << endl;
    }

    if (nr_teste > 1)
    {
        cout << "-------------------------------" << endl;
        cout << "Medie Radix(10): " << medie_radix10/(double)nr_teste << " milisecunde" << endl;
        cout << "Medie Radix(64): " << medie_radix64/(double)nr_teste << " milisecunde" << endl;
        cout << "Medie Radix(2^16): " << medie_radix2la16/(double)nr_teste << " milisecunde" << endl;
        cout << "Medie Merge: " << medie_merge/(double)nr_teste << " milisecunde" << endl;
        cout << "Medie Shell: " << medie_shell/(double)nr_teste << " milisecunde" << endl;
        cout << "Medie Counting: " << medie_counting/(double)nr_teste << " milisecunde" << endl;
        cout << "Medie STL: " << medie_stl/(double)nr_teste << " milisecunde" << endl;
        cout << "Medie Bubble: " << medie_bubble/(double)nr_teste << " milisecunde" << endl;
    }

    return 0;
}
