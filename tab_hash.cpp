#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

struct ksiazka
{
    string tytul;
    string autor;
    string wydawnictwo;
    int rok_wydania;
    int strony;
};

// Funkcje haszuj�ce

int hash1(string title)
{
    unsigned int h, i;

    h = 0;
    for (i = 0; i < title.length(); i++)
        h = 2 * h + 1 - (title[i] & 1);
    return h % 10;
}

int hash2(string title)
{
    unsigned int h, i;

    h = 0;
    for (i = 0; i < title.length(); i++)
        h = 31 * h + title[i] - 65;
    return h % 10;
}

int hash3(string title)
{
    unsigned int h, i;

    h = 0;
    for (i = 0; i < title.length(); i++)
        h = 8 * h - ((title[i] * 2) & 2);
    return h % 10;
}

// Funkcja tworzy �a�cuch 4 znakowy z A i B
// na podstawie warto�ci bit�w x
string s4(int x)
{
    string s = "";
    int m = 8;
    while (m)
    {
        s += (x & m) ? 'A' : 'B';
        m >>= 1;
    }
    return s;
}

int main()
{
    ksiazka T[10], s;
    int i, j, h, c, p;

    srand(time(NULL));
    DWORD t1, t2;

    // Zerujemy tablic� haszowan�
    for (i = 0; i < 10; i++)
    {
        T[i].tytul = "";
        T[i].autor = "";
        T[i].wydawnictwo = "";
        T[i].rok_wydania = NULL;
        T[i].strony = NULL;
    }

    t1 = GetTickCount();
    // Tablic� wype�niamy �a�cuchami
    for (i = 0; i < 10; i++)
    {
        // Generujemy losowy �a�cuch z 4 znak�w A, B
        s.tytul = s4(rand() % 16);
        s.autor = s4(rand() % 16);
        s.wydawnictwo = s4(rand() % 16);
        s.rok_wydania = (rand() % 30) + 1980;
        s.strony = (rand() % 150) + 250;

        // �a�cuch umieszczamy w tablicy haszowanej
        h = hash1(s.tytul);
        j = h;
        while (true)
        {
            if (T[j].tytul == "")
            {
                T[j] = s;
                break;
            }
            if (T[j].tytul == s.tytul) break;
            j = (j + 1) % 10;
            if (j == h) break;
        }
    }
    
    // Wy�wietlamy zawarto�� tablicy wraz z warto�ci� funkcji haszuj�cej
    for (i = 0; i < 10; i++)
    {
        cout << "T [ " << i << " ] = " << endl << endl;
        if (T[i].tytul != "")
        {
            cout << "Tytul: " << T[i].tytul << endl;
            cout << "Autor: " << T[i].autor << endl;
            cout << "Wydawnictwo: " << T[i].wydawnictwo << endl;
            cout << "Rok wydania: " << T[i].rok_wydania << endl;
            cout << "Ilosc stron: " << T[i].strony << endl;
            cout << " hf( ) = " << hash1(T[i].tytul) << endl;
        }
        else           cout << "-";
        cout << endl;
    }

    cout << endl;

    // Sprawdzamy obecno�� �a�cuch�w w tablicy haszowanej
    for (i = 0; i < 16; i++)
    {
        s.tytul = s4(i);  // �a�cuch
        h = hash1(s.tytul);  // Hasz �a�cucha
        c = 0;      // Licznik obieg�w
        j = h;
        p = -1;
        while (true)
        {
            if (T[j].tytul == "") break;
            if (T[j].tytul == s.tytul)
            {
                p = j; break;
            };
            j = (j + 1) % 10;
            if (j == h) break;
            c++;
        }

        // Wy�wietlamy wyniki
        cout << s.tytul << " hf( ) = " << h << " c = " << c << " ";
        if (p > -1) cout << "is in T [ " << p << " ] ";
        else       cout << "-";
        cout << endl;
    }
    cout << endl;
    t2 = GetTickCount();
    cout << "Czas trwania: " << t2 - t1 << " ms" << endl;

    return 0;
}