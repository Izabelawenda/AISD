#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Definicja elementu listy
//-------------------------
struct slistEl
{
    slistEl* next;
    string tytul;
    string autor;
    string wydawnictwo;
    int rok_wydania;
    int strony;
};

// Funkcja haszuj¹ca
//------------------
unsigned int hf(string s)
{
    unsigned int h, i;

    h = 0;
    for (i = 0; i < s.length(); i++)
        h = 31 * h + s[i] - 65;
    return h % 10;
}


int main2()
{
    slistEl* T[10], * p, * r;
    unsigned int i, j, h, c;
    string s, s1, s2;
    int a, b;
    bool t;

    srand(time(NULL));
    double roznica;
    cout.setf(ios::fixed);
    cout.precision(5);
    clock_t start, koniec;
    start = clock();
    // Zerujemy tablicê haszowan¹
    for (i = 0; i < 10; i++) T[i] = NULL;

    // Tablicê wype³niamy ³añcuchami
    for (i = 0; i < 35; i++)
    {
        // Generujemy losowy ³añcuch z 4 znaków A-Z
        s = "";
        for (j = 0; j < 4; j++) s += 65 + (rand() % 26);

        // £añcuch umieszczamy na odpowiedniej liœcie
        h = hf(s);
        p = T[h];
        t = true;

        if (p)
            while (true)
            {
                if (p->tytul == s)
                {
                    t = false;
                    break;
                }
                if (!p->next) break;
                p = p->next;
            }

        if (t)
        {
            r = new slistEl;
            r->tytul = s;
            for (i = 0; i < 10; i++)
            {
                r->autor += 65 + (rand() % 26);
                r->wydawnictwo += 65 + (rand() % 26);
            }
            r->rok_wydania = (rand() % 30) + 1980;
            r->strony = (rand() % 150) + 250;
            r->next = NULL;
            if (!p) T[h] = r;
            else p->next = r;
        }
    }

    // Wypisujemy tablicê
    for (i = 0; i < 10; i++)
    {
        cout << "T [ " << i << " ] = ";
        p = T[i];
        while (p)
        {
            cout << "Tytul: " << p->tytul << " ";
            cout << "Autor: " << p->autor << " ";
            cout << "Wydawnictwo: " << p->wydawnictwo << " ";
            cout << "Rok wydania: " << p->rok_wydania << " ";
            cout << "Strony: " << p->strony << " ";
            p = p->next;
        }
        cout << endl;
    }

    cout << endl;

    // Generujemy wszystkie ³añcuchy 4-ro znakowe i szukamy ich w tablicy

    s = "AAAA";

    do
    {
        h = hf(s);
        c = 0;
        p = T[h];
        while (p && (p->tytul != s))
        {
            c++;
            p = p->next;
        }

        if (p) cout << s << " hf = " << h << " c = " << c << endl;

        for (i = 4; i > 0; i--)
        {
            s[i - 1] = s[i - 1] + 1;
            if (s[i - 1] <= 'Z') break;
            s[i - 1] = 'A';
        }
    } while (s != "AAAA");

    koniec = clock();
    roznica = (koniec - start) / (double)CLOCKS_PER_SEC;
    cout << "Czas wykonania: " << roznica << endl;

    // Usuwamy listy z pamiêci

    for (i = 0; i < 10; i++)
        while ((p = T[i]))
        {
            T[i] = p->next;
            p->tytul = "";
            delete p;
        }

    cout << endl;

    return 0;
}