#include <iostream>

using namespace std;

// Definicja obiektu kolejki priorytetowej
//----------------------------------------
struct Edge
{
    int v1, v2, weight;      // Wierzcho?ki kraw?dzi, waga kraw?dzi
};

class Queue
{
private:
    Edge* Heap;
    int hpos;
public:
    Queue(int n);
    ~Queue();
    Edge front();
    void push(Edge e);
    void pop();
};

// Definicja obiektu struktury zbior?w roz??cznych
//------------------------------------------------
struct DSNode
{
    int up, rank;
};

class DSStruct
{
private:
    DSNode* Z;
public:
    DSStruct(int n);
    ~DSStruct();
    void MakeSet(int v);
    int FindSet(int v);
    void UnionSets(Edge e);
};

// Definicja obiektu minimalnego drzewa rozpinaj?cego
//---------------------------------------------------
struct TNode
{
    TNode* next;
    int v, weight;
};

class MSTree
{
private:
    TNode** A;               // Tablica list s?siedztwa
    int Alen;                // Liczba kom?rek w tablicy
    int weight;              // Waga ca?ego drzewa
public:
    MSTree(int n);
    ~MSTree();
    void addEdge(Edge e);
    void print();
};

// Definicje metod obiektu Queue
//------------------------------

// Konstruktor - tworzy n elementow? tablic? heap na kopiec
//---------------------------------------------------------
Queue::Queue(int n)
{
    Heap = new Edge[n];   // Tworzymy tablic?
    hpos = 0;                // Pozycja w kopcu
}

// Destruktor - usuwa kopiec z pami?ci
//------------------------------------
Queue::~Queue()
{
    delete[] Heap;
}

// Zwraca kraw?d? z pocz?tku kopca
//--------------------------------
Edge Queue::front()
{
    return Heap[0];
}

// Umieszcza w kopcu now? kraw?d? i odtwarza struktur? kopca
//----------------------------------------------------------
void Queue::push(Edge e)
{
    int i, j;
    i = hpos++;              
    j = (i - 1) >> 1;      

    while (i && (Heap[j].weight > e.weight))
    {
        Heap[i] = Heap[j];
        i = j;
        j = (i - 1) >> 1;
    }

    Heap[i] = e;        
}

// Usuwa korze? z kopca i odtwarza jego struktur?
//-----------------------------------------------
void Queue::pop()
{
    int i, j;
    Edge e;

    if (hpos)
    {
        e = Heap[--hpos];

        i = 0;
        j = 1;

        while (j < hpos)
        {
            if ((j + 1 < hpos) && (Heap[j + 1].weight < Heap[j].weight)) j++;
            if (e.weight <= Heap[j].weight) break;
            Heap[i] = Heap[j];
            i = j;
            j = (j << 1) + 1;
        }

        Heap[i] = e;
    }
}

// Definicje metod obiektu DSStruct
//---------------------------------

// Konstruktor
DSStruct::DSStruct(int n)
{
    Z = new DSNode[n];    // Tworzymy tablic? dla element?w zbior?w
}

DSStruct::~DSStruct()
{
    delete[] Z;            // Usuwamy tablic? ze zbiorami
}

// Tworzy wpis w tablicy Z
//------------------------
void DSStruct::MakeSet(int v)
{
    Z[v].up = v;
    Z[v].rank = 0;
}

// Zwraca indeks reprezentanta zbioru, w kt?rym jest wierzcho?ek v
//----------------------------------------------------------------
int DSStruct::FindSet(int v)
{
    if (Z[v].up != v) Z[v].up = FindSet(Z[v].up);
    return Z[v].up;
}

// ??czy ze sob? zbiory z v i u
//-----------------------------
void DSStruct::UnionSets(Edge e)
{
    int ru, rv;

    ru = FindSet(e.v1);  
    rv = FindSet(e.v2);  
    if (ru != rv)           
    {
        if (Z[ru].rank > Z[rv].rank) 
            Z[rv].up = ru;    
        else
        {
            Z[ru].up = rv;   
            if (Z[ru].rank == Z[rv].rank) Z[rv].rank++;
        }
    }
}

// Definicje metod obiektu MSTree
//-------------------------------

// Konstruktor - tworzy tablic? pustych list s?siedztwa
//-----------------------------------------------------
MSTree::MSTree(int n)
{
    int i;

    A = new TNode * [n];  
    for (i = 0; i < n; i++) A[i] = NULL; 
    Alen = n - 1;           
    weight = 0;              
}

// Destruktor - usuwa listy oraz tablic? s?siedztwa
//-------------------------------------------------
MSTree::~MSTree()
{
    int i;
    TNode* p, * r;

    for (i = 0; i <= Alen; i++)
    {
        p = A[i];
        while (p)
        {
            r = p;                                 // Zapami?tujemy wskazanie
            p = p->next;                               // Przesuwamy si? do nast?pnego elementu listy
            delete r;                                // Usuwamy element
        }
    }

    delete[] A;                                  // Usuwamy tablic? list s?siedztwa
}

// Dodaje kraw?d? do drzewa
//-------------------------
void MSTree::addEdge(Edge e)
{
    TNode* p;

    weight += e.weight;             // Do wagi drzewa dodajemy wag? kraw?dzi
    p = new TNode;                  // Tworzymy nowy w?ze?
    p->v = e.v2;                      // Wierzcho?ek ko?cowy
    p->weight = e.weight;               // Waga kraw?dzi
    p->next = A[e.v1];                  // Dodajemy p do listy wierzcho?ka v1
    A[e.v1] = p;

    p = new TNode;                     // To samo dla kraw?dzi odwrotnej
    p->v = e.v1;                       // Wierzcho?ek ko?cowy
    p->weight = e.weight;                 // Waga kraw?dzi
    p->next = A[e.v2];                       // Dodajemy p do listy wierzcho?ka v2
    A[e.v2] = p;
}

// Wy?wietla zawarto?? drzewa oraz jego wag?
//------------------------------------------
void MSTree::print()
{
    int i;
    TNode* p;

    cout << endl;
    for (i = 0; i <= Alen; i++)
    {
        cout << "Vertex " << i << " - ";
        for (p = A[i]; p; p = p->next) cout << p->v << ":" << p->weight << " ";
        cout << endl;
    }
    cout << endl << endl << "Minimal Spanning Tree Weight = " << weight << endl << endl;
}

// **********************
// *** PROGRAM G??WNY ***
// **********************

int main()
{
    int n = 9, m = 12;                                             // Liczba wierzcho?k?w i kraw?dzi
    Edge e;
    int i;

    DSStruct Z(n);                                                   // Struktura zbior?w roz??cznych
    Queue Q(m);                                                    // Kolejka priorytetowa oparta na kopcu
    MSTree T(n);                                                       // Minimalne drzewo rozpinaj?ce

    for (i = 0; i < n; i++)
        Z.MakeSet(i);                                               // Dla ka?dego wierzcho?ka tworzymy osobny zbi?r

    for (i = 0; i < m; i++)
    {
        cin >> e.v1 >> e.v2 >> e.weight;                            // Odczytujemy kolejne kraw?dzie grafu
        Q.push(e);                                                 // i umieszczamy je w kolejce priorytetowej
    }

    for (i = 1; i < n; i++)                                         // P?tla wykonuje si? n - 1 razy !!!
    {
        do
        {
            e = Q.front();                                                // Pobieramy z kolejki kraw?d?
            Q.pop();                                                      // Kraw?d? usuwamy z kolejki
        } while (Z.FindSet(e.v1) == Z.FindSet(e.v2));
        T.addEdge(e);                                                   // Dodajemy kraw?d? do drzewa
        Z.UnionSets(e);                                                    // Zbiory z wierzcho?kami ??czymy ze sob?
    }

    T.print();

    return 0;
}