#include <iostream>

using namespace std;

// Definicja obiektu kolejki priorytetowej
//----------------------------------------
struct Edge
{
    int v1, v2, weight;            // Wierzcho�ki kraw�dzi, waga kraw�dzi
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

// Definicja obiektu minimalnego drzewa rozpinaj�cego
//---------------------------------------------------
struct TNode
{
    TNode* next;
    int v, weight;
};

class MSTree
{
private:
    TNode** A;                  // Tablica list s�siedztwa
    int Alen;                    // Liczba kom�rek w tablicy
    int weight;                  // Waga ca�ego drzewa
public:
    MSTree(int n);
    ~MSTree();
    void addEdge(Edge e);
    TNode* getAList(int n);
    void print();
};

// Definicje metod obiektu Queue
//------------------------------

// Konstruktor - tworzy n elementow� tablic� heap na kopiec
//---------------------------------------------------------
Queue::Queue(int n)
{
    Heap = new Edge[n];         // Tworzymy tablic�
    hpos = 0;                      // Pozycja w kopcu
}

// Destruktor - usuwa kopiec z pami�ci
//------------------------------------
Queue::~Queue()
{
    delete[] Heap;
}

// Zwraca kraw�d� z pocz�tku kopca
//--------------------------------
Edge Queue::front()
{
    return Heap[0];
}

// Umieszcza w kopcu now� kraw�d� i odtwarza struktur� kopca
//----------------------------------------------------------
void Queue::push(Edge e)
{
    int i, j;

    i = hpos++;                    // i ustawiamy na koniec kopca
    j = (i - 1) >> 1;            // Obliczamy pozycj� rodzica

    // Szukamy miejsca w kopcu dla e

    while (i && (Heap[j].weight > e.weight))
    {
        Heap[i] = Heap[j];
        i = j;
        j = (i - 1) >> 1;
    }

    Heap[i] = e;                // Kraw�d� e wstawiamy do kopca
}

// Usuwa korze� z kopca i odtwarza jego struktur�
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

// Definicje metod obiektu MSTree
//-------------------------------

// Konstruktor - tworzy tablic� pustych list s�siedztwa
//-----------------------------------------------------
MSTree::MSTree(int n)
{
    int i;

    A = new TNode * [n];         // Tworzymy tablic� dynamiczn�
    for (i = 0; i < n; i++) A[i] = NULL; // i wype�niamy j� pustymi listami
    Alen = n - 1;                  // Zapami�tujemy d�ugo�� tablicy
    weight = 0;                    // Zerujemy wag� drzewa
}

// Destruktor - usuwa listy oraz tablic� s�siedztwa
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
            r = p;                     // Zapami�tujemy wskazanie
            p = p->next;               // Przesuwamy si� do nast�pnego elementu listy
            delete r;                  // Usuwamy element
        }
    }

    delete[] A;                  // Usuwamy tablic� list s�siedztwa
}

// Dodaje kraw�d� do drzewa
//-------------------------
void MSTree::addEdge(Edge e)
{
    TNode* p;

    weight += e.weight;            // Do wagi drzewa dodajemy wag� kraw�dzi
    p = new TNode;                 // Tworzymy nowy w�ze�
    p->v = e.v2;                   // Wierzcho�ek ko�cowy
    p->weight = e.weight;          // Waga kraw�dzi
    p->next = A[e.v1];          // Dodajemy p do listy wierzcho�ka v1
    A[e.v1] = p;

    p = new TNode;                 // To samo dla kraw�dzi odwrotnej
    p->v = e.v1;                   // Wierzcho�ek ko�cowy
    p->weight = e.weight;          // Waga kraw�dzi
    p->next = A[e.v2];          // Dodajemy p do listy wierzcho�ka v2
    A[e.v2] = p;
}

// Zwraca wska�nik pocz�tku listy s�siad�w wierzcho�ka
//----------------------------------------------------
TNode* MSTree::getAList(int n)
{
    return A[n];
}

// Wy�wietla zawarto�� drzewa oraz jego wag�
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
// *** PROGRAM G��WNY ***
// **********************

int main()
{
    int n = 9, m = 12;                                                   // Liczba wierzcho�k�w i kraw�dzi
    Edge e;
    TNode* p;
    int i, v;

    Queue Q(m);                                                // Kolejka priorytetowa oparta na kopcu
    MSTree T(n);                                             // Minimalne drzewo rozpinaj�ce
    MSTree G(n);                                               // Graf
    bool* visited = new bool[n];

    for (i = 0; i < n; i++)
        visited[i] = false;                                          // Inicjujemy tablic� odwiedzin

    for (i = 0; i < m; i++)
    {
        cin >> e.v1 >> e.v2 >> e.weight;                                           // Odczytujemy kolejne kraw�dzie grafu
        G.addEdge(e);                                                             // i umieszczamy je w G
    }

    v = 0;                        
    visited[v] = true;         

    for (i = 1; i < n; i++)      
    {
        for (p = G.getAList(v); p; p = p->next) 
            if (!visited[p->v])    
            {
                e.v1 = v;                
                e.v2 = p->v;
                e.weight = p->weight;
                Q.push(e);            
            }

        do
        {
            e = Q.front();            
            Q.pop();
        } while (visited[e.v2]); 

        T.addEdge(e);             
        visited[e.v2] = true;     
        v = e.v2;
    }

    T.print();

    delete[] visited;

    return 0;
}