#include <iostream>
using namespace std;


///////////////////////////////////////////////////////////////////////////////////////


struct AVLNode
{
    int score;
    string name;
    AVLNode* left;
    AVLNode* right;
    AVLNode* up;
    int height;
};

string cr, cl, cp;

/////////////////////////////////////////////////////////////////////////////////////////


void Print(string s1, string s2, AVLNode* x) //funkcja wypisujaca drzewo
{
    string s;

    if (x)
    {
        s = s1;
        if (s2 == cr) s[s.length() - 2] = ' ';
        Print(s + cp, cr, x->right);

        s = s.substr(0, s1.length() - 2);
        cout << s << s2 << x->score << ":" << x->height << endl;

        s = s1;
        if (s2 == cl) s[s.length() - 2] = ' ';
        Print(s + cp, cl, x->left);
    }
}

void Delete(AVLNode* x) 
{
    if (x)
    {
        Delete(x->left);
        Delete(x->right);
        delete x;
    }
}

void Insert(AVLNode*& root, int k, string na) 
{
    AVLNode* w, * p, * r;
    bool t;

    w = new AVLNode; 
    w->left = w->right = w->up = NULL;
    w->score = k;
    w->name = na;
    w->height = 0;

    p = root;            

    if (!p) root = w;     
    else
    {                      
        while (true)
            if (k < p->score)   
            {
                if (!p->left)   
                {
                    p->left = w;   
                    break;        
                }
                p = p->left;    
            }
            else
            {
                if (!p->right) 
                {
                    p->right = w; 
                    break;        
                }
                p = p->right;    
            }

        w->up = p;          

        if (p->height) p->height = 0;
        else
        {
            if (p->left == w)
                p->height = 1;
            else
                p->height = -1;

            r = p->up;      
                            
            t = false;
            while (r)
            {
                if (r->height)
                {
                    t = true;    
                    break;       
                };

                if (r->left == p) r->height = 1;
                else               r->height = -1;

                p = r;          
                r = r->up;
            }

            if (t)           
            {                 
                if (r->height == 1)
                {
                    if (r->right == p) r->height = 0;
                    else if (p->height == -1) LR(root, r);
                    else                   LL(root, r);
                }
                else
                {              
                    if (r->left == p) r->height = 0;
                    else if (p->height == 1) RL(root, r);
                    else                  RR(root, r);
                }
            }
        }
    }
}

AVLNode* Previous(AVLNode* x) //funkcja znajdujaca poprzednik wezla
{
    AVLNode* y;

    if (x)
    {
        if (x->left)
        {
            x = x->left;
            while (x->right) x = x->right;
        }
        else
        {
            do
            {
                y = x;
                x = x->up;
            } while (x && x->right != y);
        }
    }
    return x;
}

AVLNode* Find(AVLNode* x, string k) 
{
    while (x && x->name != k)
        x = (k < x->name) ? x->left : x->right;

    return x;
}

AVLNode* Remove(AVLNode*& root, AVLNode* x)
{
    AVLNode* t, * y, * z;
    bool nest;

    if (x->left && x->right)
    {
        y = Remove(root, Previous(x));
        nest = false;
    }
    else
    {
        if (x->left)
        {
            y = x->left; x->left = NULL;
        }
        else
        {
            y = x->right; x->right = NULL;
        }
        x->height = 0;
        nest = true;
    }

    if (y)
    {
        y->up = x->up;
        y->left = x->left;  if (y->left)   y->left->up = y;
        y->right = x->right; if (y->right)  y->right->up = y;
        y->height = x->height;
    }

    if (x->up)
    {
        if (x->up->left == x) x->up->left = y; else x->up->right = y;
    }
    else root = y;

    if (nest)
    {
        z = y;
        y = x->up;
        while (y)
        {
            if (!y->height)
            {           
                if (y->left == z)  y->height = -1; else y->height = 1;
                break;
            }
            else
            {
                if (((y->height == 1) && (y->left == z)) || ((y->height == -1) && (y->right == z)))
                {          
                    y->height = 0;
                    z = y; y = y->up;
                }
                else
                {
                    if (y->left == z)  t = y->right; else t = y->left;
                    if (!t->height)
                    {         
                        if (y->height == 1) LL(root, y); else RR(root, y);
                        break;
                    }
                    else if (y->height == t->height)
                    {         
                        if (y->height == 1) LL(root, y); else RR(root, y);
                        z = t; y = t->up;
                    }
                    else
                    {         
                        if (y->height == 1) LR(root, y); else RL(root, y);
                        z = y->up; y = z->up;
                    }
                }
            }
        }
    }
    return x;
}


///////////////ROTACJE////////////////////////////////////////////////////////////////////


void RR(AVLNode*& root, AVLNode* X) //rotacja rr
{
    AVLNode* Y = X->right, * p = X->up;

    X->right = Y->left;
    if (X->right) X->right->up = X;

    Y->left = X;
    Y->up = p;
    X->up = Y;

    if (p)
    {
        if (p->left == X) p->left = Y; else p->right = Y;
    }
    else root = Y;

    if (Y->height == -1) X->height = Y->height = 0;
    else
    {
        X->height = -1; Y->height = 1;
    }
}

void LL(AVLNode*& root, AVLNode* X) //rotacja ll
{
    AVLNode* Y = X->left, * p = X->up;

    X->left = Y->right;
    if (X->left) X->left->up = X;

    Y->right = X;
    Y->up = p;
    X->up = Y;

    if (p)
    {
        if (p->left == X) p->left = Y; else p->right = Y;
    }
    else root = Y;

    if (Y->height == 1) X->height = Y->height = 0;
    else
    {
        X->height = 1; Y->height = -1;
    }
}

void RL(AVLNode*& root, AVLNode* X) //rotacja rl
{
    AVLNode* Y = X->right, * Z = Y->left, * p = X->up;

    Y->left = Z->right;
    if (Y->left) Y->left->up = Y;

    X->right = Z->left;
    if (X->right) X->right->up = X;

    Z->left = X;
    Z->right = Y;
    X->up = Y->up = Z;
    Z->up = p;

    if (p)
    {
        if (p->left == X) p->left = Z; else p->right = Z;
    }
    else root = Z;

    if (Z->height == -1) X->height = 1; else X->height = 0;
    if (Z->height == 1) Y->height = -1; else Y->height = 0;

    Z->height = 0;
}

void LR(AVLNode*& root, AVLNode* X) //rotacja lr
{
    AVLNode* Y = X->left, * Z = Y->right, * p = X->up;

    Y->right = Z->left;
    if (Y->right) Y->right->up = Y;

    X->left = Z->right;
    if (X->left) X->left->up = X;

    Z->right = X;
    Z->left = Y;
    X->up = Y->up = Z;
    Z->up = p;

    if (p)
    {
        if (p->left == X) p->left = Z; else p->right = Z;
    }
    else root = Z;

    if (Z->height == 1) X->height = -1; else X->height = 0;
    if (Z->height == -1) Y->height = 1; else Y->height = 0;

    Z->height = 0;
}


void Findx(AVLNode* x)
{
    string imie;
    cout << "Wpisz nazwisko zawodnika ktorego chcesz wyszukac: ";
    cin >> imie;
    Find(x, imie);
}

void Change()
{

}

void Add(AVLNode* x)
{
    int wynik; string imie;
    cout << "Podaj imie zawodnika: ";
    cin >> imie;
    cout << "Podaj jego wynik: ";
    cin >> wynik;
    Insert(x, wynik, imie);
}


/////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
    AVLNode* root = NULL;
    int choice;


    do
    {
        system("cls");
        cout << "---------------------------\n";
        cout << "     ZAWODY NARCIARSKIE    \n";
        cout << "---------------------------\n"
            "           OPCJE\n"
            " --------------------------\n"
            "|  1  -  Dodaj wynik       |\n"
            "|  2  -  Zmien wynik       |\n"
            "|  3  -  Wyszukaj wynik    |\n"
            "|  4  -  Wyswietl wyniki   |\n"
            " --------------------------\n"
            "Twoj wybor : ";
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1: Add(root); break;
        case 2: Change(); break;
        case 3: Findx(root); break;
        case 4: Print("", "", root); break;
        }
        if ((choice >= 1) && (choice <= 4))
        {
            cout << endl;
            system("pause");
        }
    } while (choice);

    return 0;
}