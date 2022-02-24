#include <iostream>

using namespace std;

// Definicja obiektu kolejki priorytetowej
//----------------------------------------
struct Edge
{
    int v1, v2, weight;            // Wierzcho³ki krawêdzi, waga krawêdzi
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

// Definicja obiektu minimalnego drzewa rozpinaj¹cego
//---------------------------------------------------
struct TNode
{
    TNode* next;
    int v, weight;
};

class MSTree
{
private:
    TNode** A;                  // Tablica list s¹siedztwa
    int Alen;                    // Liczba komórek w tablicy
    int weight;                  // Waga ca³ego drzewa
public:
    MSTree(int n);
    ~MSTree();
    void addEdge(Edge e);
    TNode* getAList(int n);
    void print();
};

// Definicje metod obiektu Queue
//------------------------------

// Konstruktor - tworzy n elementow¹ tablicê heap na kopiec
//---------------------------------------------------------
Queue::Queue(int n)
{
    Heap = new Edge[n];         // Tworzymy tablicê
    hpos = 0;                      // Pozycja w kopcu
}

// Destruktor - usuwa kopiec z pamiêci
//------------------------------------
Queue::~Queue()
{
    delete[] Heap;
}

// Zwraca krawêdŸ z pocz¹tku kopca
//--------------------------------
Edge Queue::front()
{
    return Heap[0];
}

// Umieszcza w kopcu now¹ krawêdŸ i odtwarza strukturê kopca
//----------------------------------------------------------
void Queue::push(Edge e)
{
    int i, j;

    i = hpos++;                    // i ustawiamy na koniec kopca
    j = (i - 1) >> 1;            // Obliczamy pozycjê rodzica

    // Szukamy miejsca w kopcu dla e

    while (i && (Heap[j].weight > e.weight))
    {
        Heap[i] = Heap[j];
        i = j;
        j = (i - 1) >> 1;
    }

    Heap[i] = e;                // KrawêdŸ e wstawiamy do kopca
}

// Usuwa korzeñ z kopca i odtwarza jego strukturê
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

// Konstruktor - tworzy tablicê pustych list s¹siedztwa
//-----------------------------------------------------
MSTree::MSTree(int n)
{
    int i;

    A = new TNode * [n];         // Tworzymy tablicê dynamiczn¹
    for (i = 0; i < n; i++) A[i] = NULL; // i wype³niamy j¹ pustymi listami
    Alen = n - 1;                  // Zapamiêtujemy d³ugoœæ tablicy
    weight = 0;                    // Zerujemy wagê drzewa
}

// Destruktor - usuwa listy oraz tablicê s¹siedztwa
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
            r = p;                     // Zapamiêtujemy wskazanie
            p = p->next;               // Przesuwamy siê do nastêpnego elementu listy
            delete r;                  // Usuwamy element
        }
    }

    delete[] A;                  // Usuwamy tablicê list s¹siedztwa
}

// Dodaje krawêdŸ do drzewa
//-------------------------
void MSTree::addEdge(Edge e)
{
    TNode* p;

    weight += e.weight;            // Do wagi drzewa dodajemy wagê krawêdzi
    p = new TNode;                 // Tworzymy nowy wêze³
    p->v = e.v2;                   // Wierzcho³ek koñcowy
    p->weight = e.weight;          // Waga krawêdzi
    p->next = A[e.v1];          // Dodajemy p do listy wierzcho³ka v1
    A[e.v1] = p;

    p = new TNode;                 // To samo dla krawêdzi odwrotnej
    p->v = e.v1;                   // Wierzcho³ek koñcowy
    p->weight = e.weight;          // Waga krawêdzi
    p->next = A[e.v2];          // Dodajemy p do listy wierzcho³ka v2
    A[e.v2] = p;
}

// Zwraca wskaŸnik pocz¹tku listy s¹siadów wierzcho³ka
//----------------------------------------------------
TNode* MSTree::getAList(int n)
{
    return A[n];
}

// Wyœwietla zawartoœæ drzewa oraz jego wagê
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
// *** PROGRAM G£ÓWNY ***
// **********************

int main()
{
    int n = 9, m = 12;                                                   // Liczba wierzcho³ków i krawêdzi
    Edge e;
    TNode* p;
    int i, v;

    Queue Q(m);                                                // Kolejka priorytetowa oparta na kopcu
    MSTree T(n);                                             // Minimalne drzewo rozpinaj¹ce
    MSTree G(n);                                               // Graf
    bool* visited = new bool[n];

    for (i = 0; i < n; i++)
        visited[i] = false;                                          // Inicjujemy tablicê odwiedzin

    for (i = 0; i < m; i++)
    {
        cin >> e.v1 >> e.v2 >> e.weight;                                           // Odczytujemy kolejne krawêdzie grafu
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