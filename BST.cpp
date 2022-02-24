#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;


///////////////////////////////////////////////////////////////////////////////////////


struct BSTNode
{
	int key;
	BSTNode* up;
	BSTNode* left;
	BSTNode* right;
};

class BST
{
public:
    BSTNode* root;  // korzeñ drzewa
    int counter;       // liczba wêz³ów

    BST();  //konstruktor klasy
    ~BST();  //destruktor klasy
    bool Insert(BSTNode* n);  //wstawia element do struktury BST
    BSTNode* Search(int key);  // Wyszukuje element wg wartoœci klucza
    BSTNode* MaxNode(BSTNode* x);  // Zwraca wêze³ z maksymalnym kluczem
    BSTNode* MinNode(BSTNode* x);  // Zwraca wêze³ z minimalnym kluczem
    BSTNode* Previous(BSTNode* x);  // Zwraca wêze³ poprzednika
    BSTNode* Next(BSTNode* x);  // Zwraca wêze³ nastêpnika
    BSTNode* Remove(BSTNode* x);  // Usuwa element x ze struktury BST. Zwraca usuniêty wêze³
    void Inorder(BSTNode* x);  // Przechodzi przez BST metod¹ inorder
    void Queue();  // Wypisuje do cout liczbê wêz³ów drzewa BST
};


/////////////////////////////////////////////////////////////////////////////////////////


BST::BST() //konstruktor klasy
{
    root = NULL;
    counter = 0;
}

BST::~BST() //destruktor klasy
{
    while (root) delete(Remove(root));
}

bool BST::Insert(BSTNode* n)  // Wstawia element do struktury BST
{
    BSTNode* y, * x = root;

    y = n->left = n->right = NULL;

    while (x)
    {
        y = x;
        if (n->key == x->key)
        {
            delete n;
            return false;
        }
        
        x = (n->key < x->key) ? x->left : x->right;
    }

    n->up = y;

    if (!y)
    {
        root = n;
    }
    else if (n->key < y->key)
    {
        y->left = n;
    }
    else
    {
        y->right = n;
    }

    counter++;
    return true;
}

BSTNode* BST::Search(int key)  // Wyszukuje element wg wartoœci klucza
{
    BSTNode* x = root;

    while ((x) && (x->key != key))
    {
        x = (key < x->key) ? x->left : x->right;
    }

    return x;
}

BSTNode* BST::MinNode(BSTNode* x)  // Zwraca wêze³ z minimalnym kluczem
{
    while (x->left)
    {
        x = x->left;
    }
    return x;
}

BSTNode* BST::MaxNode(BSTNode* x)  // Zwraca wêze³ z maksymalnym kluczem
{
    while (x->right)
    {
        x = x->right;
    }
    return x;
}

BSTNode* BST::Previous(BSTNode* x)  // Zwraca wêze³ poprzednika
{
    if (x->left)
    {
        return MaxNode(x->left);
    }

    BSTNode* y;

    do
    {
        y = x;
        x = x->up;
    } while (x && (x->right != y));

    return x;
}

BSTNode* BST::Next(BSTNode* x)  // Zwraca wêze³ nastêpnika
{
    if (x->right)
    {
        return MinNode(x->right);
    }

    BSTNode* y;

    do
    {
        y = x;
        x = x->up;
    } while (x && (x->left != y));

    return x;
}

BSTNode* BST::Remove(BSTNode* x)  // Usuwa element ze struktury BST. Zwraca usuniêty wêze³
{
    BSTNode* y = x->up, * z;

    if ((x->left) && (x->right))
    {
        z = (rand() % 2) ? Remove(Previous(x)) : Remove(Next(x));
        z->left = x->left;   if (z->left)  z->left->up = z;
        z->right = x->right; if (z->right) z->right->up = z;
        counter++;
    }
    else
    {
        z = (x->left) ? x->left : x->right;
    }

    if (z)
    {
        z->up = y;
    }

    if (!y)
    {
        root = z;
    }
    else if (y->left == x)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }

    counter--;
    return x;
}

void BST::Inorder(BSTNode* x)  // Przechodzi przez BST metod¹ inorder
{
    if (x)
    {
        Inorder(x->left);
        cout << x->key << " - ";
        Inorder(x->right);
    }
}

void BST::Queue()  // Wypisuje liczbê wêz³ów drzewa BST
{
    cout << "\nLiczba oczekujacych rezerwacji : " << counter << endl << endl;
}


//////////////////////////////////////////////////////////////////////////////////////////


void Add(BST* T)  // Dodaje nowe wêz³y do drzewa BST
{
    cout << "--------------------\n";
    cout << "REZERWACJA PRZYLOTU\n"
            "--------------------\n\n";
    cout << "AKTUALNY CZAS : "<< t <<endl;
   
    T->Queue();
    cout << "W kolejce : ";
    T->Inorder(T->root);

    cout << "\n\nPodaj czas rezerwacji : ";

    BSTNode* x;
    x = new BSTNode;
   
    cin >> x->key;

    for (int i = -3; i <= 3; i++)
    {
        if (T->Search((x->key) + i))
        {
            cout << "\nBrak mozliwosci rezerwacji. Wymagany odstep czasowy rowny 3 minuty." << endl;
            return;
        }
    }
    T->Insert(x);
    cout << endl;
    T->Queue();
}

void Del(BST* T)  // Usuwa wêze³ o zadanym kluczu
{
    cout << "------------------------------\n";
    cout << "ODWOLANIE REZERWACJI PRZYLOTU\n"
            "------------------------------\n\n";
    T->Queue();
    cout << "W kolejce : ";
    T->Inorder(T->root);

    BSTNode* x;
    int key;

    cout << "\n\nPodaj czas odwolywanej rezerwacji : "; cin >> key;

    x = T->Search(key);

    if (x)
    {
        delete T->Remove(x);
        cout << endl;
        T->Queue();
    }
    else cout << "\nNie ma takiej rezerwacji.\n";
}

void Inord(BST* T) // Przechodzi przez drzewo algorytmem inorder
{
    cout << "---------------------------------------\n";
    cout << "TABLICA REZERWACJI PRZYLOTOW SAMOLOTOW\n";
    cout << "---------------------------------------\n\n";
    cout << "  ";
    T->Inorder(T->root);
}


/////////////////////////////////////////////////////////////////////////////////////////////
	

int main()
{
    BST* T = new BST();
    int choice;

    do
    {
        system("cls"); 
        cout << "----------------------------------------------\n";
        cout << "PORT LOTNICZY IM. JANA PAWLA II KRAKOW-BALICE\n";
        cout << "----------------------------------------------\n\n"
            "           MENU\n"
            " --------------------------\n"
            "|  0  -  Koniec            |\n"
            "|  1  -  Dodaj rezerwacje  |\n"
            "|  2  -  Usun rezerwacje   |\n"
            "|  3  -  Wyswietl kolejke  |\n"
            " --------------------------\n"
            "Twoj wybor : ";
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1: Add(T); break;  // Dodaje nowe wêz³y do drzewa BST
        case 2: Del(T); break;  // Usuwa wêze³ o zadanym kluczu
        case 3: Inord(T); break;  // Przechodzi przez drzewo algorytmem inorder
        }
        if ((choice >= 1) && (choice <= 3))
        {
            cout << endl;
            system("pause");
        }
    } while (choice);

    delete T;
	return 0;
}