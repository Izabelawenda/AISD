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

// Funkcje haszuj¹ce

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

// Funkcja tworzy ³añcuch 4 znakowy z A i B
// na podstawie wartoœci bitów x
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

    // Zerujemy tablicê haszowan¹
    for (i = 0; i < 10; i++)
    {
        T[i].tytul = "";
        T[i].autor = "";
        T[i].wydawnictwo = "";
        T[i].rok_wydania = NULL;
        T[i].strony = NULL;
    }

    t1 = GetTickCount();
    // Tablicê wype³niamy ³añcuchami
    for (i = 0; i < 10; i++)
    {
        // Generujemy losowy ³añcuch z 4 znaków A, B
        s.tytul = s4(rand() % 16);
        s.autor = s4(rand() % 16);
        s.wydawnictwo = s4(rand() % 16);
        s.rok_wydania = (rand() % 30) + 1980;
        s.strony = (rand() % 150) + 250;

        // £añcuch umieszczamy w tablicy haszowanej
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
    
    // Wyœwietlamy zawartoœæ tablicy wraz z wartoœci¹ funkcji haszuj¹cej
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

    // Sprawdzamy obecnoœæ ³añcuchów w tablicy haszowanej
    for (i = 0; i < 16; i++)
    {
        s.tytul = s4(i);  // £añcuch
        h = hash1(s.tytul);  // Hasz ³añcucha
        c = 0;      // Licznik obiegów
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

        // Wyœwietlamy wyniki
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