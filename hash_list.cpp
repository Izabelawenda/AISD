#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

struct slistEl
{
    slistEl* next;
    string tytul;
    string autor;
    string wydawnictwo;
    int rok_wydania;
    int strony;
};

// Funkcje haszuj¹ce

unsigned int hash1(string title)
{
    unsigned int h, i;

    h = 0;
    for (i = 0; i < title.length(); i++)
        h = 2 * h + 1 - (title[i] & 1);
    return h % 10;
}

unsigned int hash2(string title)
{
    unsigned int h, i;

    h = 0;
    for (i = 0; i < title.length(); i++)
        h = 31 * h + title[i] - 65;
    return h % 10;
}

unsigned int hash3(string title)
{
    unsigned int h, i;

    h = 0;
    for (i = 0; i < title.length(); i++)
        h = 8 * h - ((title[i] * 2) & 2);
    return h % 10;
}

int main()
{
    slistEl* T[10], * p, * r;
    unsigned int i, j, k, h, c;
    string s;
    bool t;

    srand(time(NULL));
    DWORD t1, t2;
    
    // Zerujemy tablicê haszowan¹
    for (i = 0; i < 10; i++)
    {
        T[i] = NULL;
    }

    t1 = GetTickCount();
    // Tablicê wype³niamy ³añcuchami
    for (i = 0; i < 35; i++)
    {
        // Generujemy losowy ³añcuch z 4 znaków A-Z
        s = "";
        for (j = 0; j < 4; j++) s += 65 + (rand() % 26);

        // £añcuch umieszczamy na odpowiedniej liœcie
        h = hash3(s);
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
            for (k = 0; k < 10; k++)
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
    t2 = GetTickCount();
    cout << "Czas trwania: " << t2 - t1 << " ms" << endl;

    // Wypisujemy tablicê
    for (i = 0; i < 10; i++)
    {
        cout << "T [ " << i << " ] = " << endl;
        p = T[i];
        while (p)
        {
            cout << "Tytul: " << p->tytul << endl;
            cout << "Autor: " << p->autor << endl;
            cout << "Wydawnictwo: " << p->wydawnictwo << endl;
            cout << "Rok wydania: " << p->rok_wydania << endl;
            cout << "Strony: " << p->strony << endl;
            p = p->next;
        }
        cout << endl;
    }

    cout << endl;

    // Generujemy wszystkie ³añcuchy 4-ro znakowe i szukamy ich w tablicy

    s = "AAAA";

    do
    {
        h = hash3(s);
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
    t2 = GetTickCount();
    cout << "Czas trwania: " << t2 - t1 << " ms" << endl;
   

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