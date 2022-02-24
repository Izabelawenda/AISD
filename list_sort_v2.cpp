#include <iostream>
#include <ctime>
#include <bits/stdc++.h> 
using namespace std;

struct Element
{
	int number;
	Element* next;
};

class List
{
public:
	Element* head;
	List();
	~List();
	void show();
	void push_front(char x);
	void pop_front();
	void split(List& ob1, List& ob2);
	void merge(List& ob1, List& ob2);
	void merge_sort();
	void selection_sort();
	void selection_sort_reverse();
	void reverse();
};

class Double
{
public:
	int number;
	Double* next;
	Double* prev;
};

struct Bucket
{
	Element* head;
};

struct Bucket_arr
{
	int V;
	Bucket* array;
};


void insertion_sort();
void insertion_sort_reverse();
void time_merge();
void time_insertion();
void time_selection();
void time_heap();
void time_quick();
void time_bucket();
void swap(int* x, int* y);
void print(int arr[]);
void bucket_sort(Bucket_arr* br, int buc, int value);

void show(Double* head)
{
	while (head)
	{
		cout << head->number << " ";
		head = head->next;
	}
	cout << endl;
}

void push(Double** head_ref, int new_data)
{
	Double* newnode = new Double;
	newnode->number = new_data;
	newnode->prev = NULL;
	newnode->next = (*head_ref);
	if ((*head_ref) != NULL) (*head_ref)->prev = newnode;
	(*head_ref) = newnode;
}

List::List() //konstruktor
{
	head = NULL;
}

List::~List() //destruktor
{
	while (head != 0)
	{
		pop_front();
	}
}

void List::show() //wyœwietlanie wszystkich elementów
{
	Element* el;
	for (el = head; el != 0; el = el->next)
	{
		cout << el->number << "  ";
	}
	cout << endl;
}

void List::push_front(char x) //dodawanie na pocz¹tek listy
{
	Element* el;
	el = new Element;
	el->next = head;
	el->number = x;
	head = el;
}

void List::pop_front() //usuwanie pierwszego elementu
{
	Element* el = head;
	if (el != 0)
	{
		head = el->next;
		delete el;
	}
}

void List::split(List& ob1, List& ob2) //podzia³ listy na czêœci
{
	Element* el1, * el2;
	bool check = false;
	ob1.push_front(0);
	ob2.push_front(0);
	el1 = ob1.head;
	el2 = ob2.head;
	while (head != 0)
	{
		if (check != 0)
		{
			el2->next = head;
			el2 = el2->next;
		}
		else
		{
			el1->next = head;
			el1 = el1->next;
		}
		head = head->next;
		check = !check;
	}
	el1->next = el2->next = NULL;
	ob1.pop_front();
	ob2.pop_front();
}

void List::merge(List& ob1, List& ob2) //po³¹czenie dwóch list
{
	Element* el;
	push_front(0);
	el = head;
	while (ob1.head != NULL && ob2.head != NULL)
	{
		if (ob1.head->number > ob2.head->number)
		{
			el->next = ob2.head;
			ob2.head = ob2.head->next;
		}
		else
		{
			el->next = ob1.head;
			ob1.head = ob1.head->next;
		}
		el = el->next;
	}
	while (ob1.head != NULL)
	{
		el->next = ob1.head;
		ob1.head = ob1.head->next;
		el = el->next;
	}
	while (ob2.head != NULL)
	{
		el->next = ob2.head;
		ob2.head = ob2.head->next;
		el = el->next;
	}
	pop_front();
}

void List::merge_sort() //sortowanie przez scalanie merge_sort
{
	List list1, list2;
	if (head != 0 && head->next != 0)
	{
		split(list1, list2);
		list1.merge_sort();
		list2.merge_sort();
		merge(list1, list2);
	}
}

void insertion_sort() //sortoanie przez wstawianie insertion_sort
{
	Element* el;
	Element* x, * y;
	el = new Element;
	el->next = new Element;
	el->next->next = NULL;
	el->next->number = 2147483647; //maksymalna wartosc inta
	for (int i = 0; i < 1000; i++)
	{
		int num = (rand() % (100 + 1));
		for (y = el; num > y->next->number; y = y->next);
		x = new Element;
		x->number = num;
		x->next = y->next;
		y->next = x;
	}
	for (y = el->next; y->next; y = y->next)
	{
		cout << y->number << "  ";
	}
	cout << endl;
	while (el != 0)
	{
		x = el;
		el = el->next;
		delete x;
	}
}

void insertion_sort_reverse()
{
	Element* el;
	Element* x, * y;
	el = new Element;
	el->next = new Element;
	el->next->next = new Element;
	el->next->next->next = NULL;
	el->number = 2147483647; //maksymalna wartosc inta
	for (int i = 0; i < 1000; i++)
	{
		int num = (rand() % (100 + 1));
		for (y = el->next; num < y->next->number; y = y->next);
		x = new Element;
		x->number = num;
		x->next = y->next;
		y->next = x;

	}
	for (y = el->next->next; y->next; y = y->next)
	{
		cout << y->number << "  ";
	}
	cout << endl;
	while (el != 0)
	{
		x = el;
		el = el->next;
		delete x;
	}
}

void List::selection_sort()
{
	Element* a, * b, * c, * d, * e;
	a = b = head;
	while (b->next != NULL)
	{
		c = d = b->next;
		while (d != NULL)
		{
			if (b->number > d->number)
			{
				if (b->next == d)
				{
					if (b == head)
					{
						b->next = d->next;
						d->next = b;
						e = b;
						b = d;
						d = e;
						c = d;
						head = b;
						d = d->next;
					}
					else
					{
						b->next = d->next;
						d->next = b;
						a->next = d;
						e = b;
						b = d;
						d = e;
						c = d;
						d = d->next;
					}
				}
				else
				{
					if (b == head)
					{
						e = b->next;
						b->next = d->next;
						d->next = e;
						c->next = b;
						e = b;
						b = d;
						d = e;
						c = d;
						d = d->next;
						head = b;
					}
					else
					{
						e = b->next;
						b->next = d->next;
						d->next = e;
						c->next = b;
						a->next = d;
						e = b;
						b = d;
						d = e;
						c = d;
						d = d->next;
					}
				}
			}
			else
			{
				c = d;
				d = d->next;
			}
		}
		a = b;
		b = b->next;
	}
}

void List::selection_sort_reverse()
{
	Element* a, * b, * c, * d, * e;
	a = b = head;
	while (b->next != NULL)
	{
		c = d = b->next;
		while (d != NULL)
		{
			if (b->number < d->number)
			{
				if (b->next == d)
				{
					if (b == head)
					{
						b->next = d->next;
						d->next = b;
						e = b;
						b = d;
						d = e;
						c = d;
						head = b;
						d = d->next;
					}
					else
					{
						b->next = d->next;
						d->next = b;
						a->next = d;
						e = b;
						b = d;
						d = e;
						c = d;
						d = d->next;
					}
				}
				else
				{
					if (b == head)
					{
						e = b->next;
						b->next = d->next;
						d->next = e;
						c->next = b;
						e = b;
						b = d;
						d = e;
						c = d;
						d = d->next;
						head = b;
					}
					else
					{
						e = b->next;
						b->next = d->next;
						d->next = e;
						c->next = b;
						a->next = d;
						e = b;
						b = d;
						d = e;
						c = d;
						d = d->next;
					}
				}
			}
			else
			{
				c = d;
				d = d->next;
			}
		}
		a = b;
		b = b->next;
	}
}

Double* get_tail(Double* tail)
{
	while (tail != NULL && tail->next != NULL)
	{
		tail = tail->next;
	}
	return tail;
}

void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

Double* divide(Double* el1, Double* el2)
{
	int pivot = el2->number;
	Double* i = el1->prev;
	for (Double* j = el1; j != el2; j = j->next)
	{
		if (j->number <= pivot)
		{
			i = (i == NULL) ? el1 : i->next;

			swap(&(i->number), &(j->number));
		}
	}
	i = (i == NULL) ? el1 : i->next;
	swap(&(i->number), &(el2->number));
	return i;
}

Double* divide_reverse(Double* el1, Double* el2)
{
	int pivot = el2->number;
	Double* i = el1->prev;
	for (Double* j = el1; j != el2; j = j->next)
	{
		if (j->number >= pivot)
		{
			i = (i == NULL) ? el1 : i->next;

			swap(&(i->number), &(j->number));
		}
	}
	i = (i == NULL) ? el1 : i->next;
	swap(&(i->number), &(el2->number));
	return i;
}

void quickend(Double* head, Double* end)
{
	if (end != NULL && head != end && head != end->next)
	{
		Double* el = divide(head, end);
		quickend(head, el->prev);
		quickend(el->next, end);
	}
}

void quickend_reverse(Double* head, Double* end)
{
	if (end != NULL && head != end && head != end->next)
	{
		Double* el = divide_reverse(head, end);
		quickend_reverse(head, el->prev);
		quickend_reverse(el->next, end);
	}
}

void quick_sort(Double* el)
{
	Double* end = get_tail(el);
	quickend(el, end);
}

void quick_sort_reverse(Double* el)
{
	Double* end = get_tail(el);
	quickend_reverse(el, end);
}

void heap(int arr[], int n, int i)
{
	int larg = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && arr[l] > arr[larg])
	{
		larg = l;
	}
	if (r < n && arr[r] > arr[larg])
	{
		larg = r;
	}
	if (larg != i)
	{
		swap(arr[i], arr[larg]);
		heap(arr, n, larg);
	}
}

void heap_reverse(int arr[], int n, int i)
{
	int small = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && arr[l] < arr[small])
	{
		small = l;
	}
	if (r < n && arr[r] < arr[small])
	{
		small = r;
	}
	if (small != i)
	{
		swap(arr[i], arr[small]);
		heap_reverse(arr, n, small);
	}
}

void heap_sort(int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heap(arr, n, i);
	}
	for (int i = n - 1; i > 0; i--)
	{
		swap(arr[0], arr[i]);
		heap(arr, i, 0);
	}
}

void heap_sort_reverse(int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heap_reverse(arr, n, i);
	}
	for (int i = n - 1; i > 0; i--)
	{
		swap(arr[0], arr[i]);
		heap_reverse(arr, i, 0);
	}
}

void show_arr(int arr[], int n)
{
	for (int i = 0; i < n; ++i)
		cout << arr[i] << " ";
	cout << "\n";
}

Element* add_node(char x)
{
	Element* el = new Element;
	el->number = x;
	el->next = NULL;
	return el;
}

Bucket_arr* newbucket(int v)
{
	Bucket_arr* br = new Bucket_arr;
	br->V = v;
	br->array = new Bucket[v];
	for (int i = 0; i < v; i++)
	{
		br->array[i].head = NULL;
	}
	return br;
}

void bucket_sort(Bucket_arr* br, int buc, int value)
{
	Element* newnode = add_node(value);
	Element* temp = new Element;
	if (br->array[buc].head != NULL)
	{
		temp = br->array[buc].head;
		if (temp->number > newnode->number)
		{
			newnode->next = br->array[buc].head;
			br->array[buc].head = newnode;
		}
		else
		{
			while (temp->next != NULL)
			{
				if ((temp->next)->number > newnode->number)
				{
					break;
				}
				temp = temp->next;
			}
			newnode->next = temp->next;
			temp->next = newnode;
		}
	}
	else
	{
		br->array[buc].head = newnode;
	}
}

void bucket_sort_reverse(Bucket_arr* br, int buc, int value)
{
	Element* newnode = add_node(value);
	Element* temp = new Element;
	if (br->array[buc].head != NULL)
	{
		temp = br->array[buc].head;
		if (temp->number < newnode->number)
		{
			newnode->next = br->array[buc].head;
			br->array[buc].head = newnode;
		}
		else
		{
			while (temp->next != NULL)
			{
				if ((temp->next)->number < newnode->number)
				{
					break;
				}
				temp = temp->next;
			}
			newnode->next = temp->next;
			temp->next = newnode;
		}
	}
	else
	{
		br->array[buc].head = newnode;
	}
}

void print_buc(Bucket_arr* br)
{
	Element* el = new Element;
	for (int i = 0; i < br->V; i++)
	{
		el = br->array[i].head;
		while (el != NULL)
		{
			cout << " " << el->number;
			el = el->next;
		}
	}
}

void time_bucket()
{
	clock_t start1, end1, start2, end2;
	srand(time(NULL));
	int arr[1000];
	int V = 10, range = 1000;
	struct Bucket_arr* bucket = newbucket(V);
	for (int i = 0; i < 1000; i++)
	{
		arr[i] = ((rand() % (100 + 1)));
	}
	cout << endl;
	cout << "LIST OF RANDOM NUMBERS" << endl;
	cout << endl;
	show_arr(arr,1000);
	cout << endl;
	start1 = clock();
	for (int i = 0; i < 1000; i++)
	{
		bucket_sort(bucket, arr[i] / 1000, arr[i]);
	}
	end1 = clock();
	long double time_taken1 = long double(end1 - start1) / long double(CLOCKS_PER_SEC);
	cout << "AFTER BUCKET SORT - INCREASING" << endl;
	cout << endl;
	print_buc(bucket);
	cout << endl;
	cout << "TIME : " << fixed << time_taken1 << setprecision(20);
	cout << " sec " << endl;
	cout << endl;
	start2 = clock();
	for (int i = 0; i < 1000; i++)
	{
		bucket_sort_reverse(bucket, arr[i] / 1000, arr[i]);
	}
	end2 = clock();
	long double time_taken2 = long double(end2 - start2) / long double(CLOCKS_PER_SEC);
	cout << endl;
	cout << "AFTER BUCKET SORT - DECREASING" << endl;
	cout << endl;
	print_buc(bucket);
	cout << endl;
	cout << "TIME : " << fixed << time_taken2 << setprecision(20);
	cout << " sec " << endl;
	cout << endl;
}

void time_heap()
{
	clock_t start1, end1, start2, end2;
	srand(time(NULL));
	int arr[1000];
	for (int i = 0; i < 1000; i++)
	{
		arr[i] = ((rand() % (100 + 1)));
	}
	cout << endl;
	cout << "LIST OF RANDOM NUMBERS" << endl;
	cout << endl;
	show_arr(arr, 1000);
	cout << endl;
	start1 = clock();
	heap_sort(arr, 1000);
	end1 = clock();
	long double time_taken1 = long double(end1 - start1) / long double(CLOCKS_PER_SEC);
	cout << "AFTER HEAP SORT - INCREASING" << endl;
	cout << endl;
	show_arr(arr, 1000);
	cout << endl;
	cout << "TIME : " << fixed << time_taken1 << setprecision(20);
	cout << " sec " << endl;
	cout << endl;
	start2 = clock();
	heap_sort_reverse(arr, 1000);
	end2 = clock();
	long double time_taken2 = long double(end2 - start2) / long double(CLOCKS_PER_SEC);
	cout << endl;
	cout << "AFTER HEAP SORT - DECREASING" << endl;
	cout << endl;
	show_arr(arr, 1000);
	cout << endl;
	cout << "TIME : " << fixed << time_taken2 << setprecision(20);
	cout << " sec " << endl;
	cout << endl;
}

void time_quick()
{
	clock_t start1, end1, start2, end2;
	Double* C = NULL;
	srand(time(NULL));
	for (int i = 0; i < 1000; i++)
	{
		push(&C, (rand() % (100 + 1)));
	}
	cout << endl;
	cout << "LIST OF RANDOM NUMBERS" << endl;
	cout << endl;
	show(C);
	cout << endl;
	start1 = clock();
	quick_sort(C);
	end1 = clock();
	long double time_taken1 = long double(end1 - start1) / long double(CLOCKS_PER_SEC);
	cout << "AFTER QUICK SORT - INCREASING" << endl;
	cout << endl;
	show(C);
	cout << endl;
	cout << "TIME : " << fixed << time_taken1 << setprecision(20);
	cout << " sec " << endl;
	cout << endl;
	start2 = clock();
	quick_sort_reverse(C);
	end2 = clock();
	long double time_taken2 = long double(end2 - start2) / long double(CLOCKS_PER_SEC);
	cout << endl;
	cout << "AFTER QUICK SORT - DECREASING" << endl;
	cout << endl;
	show(C);
	cout << endl;
	cout << "TIME : " << fixed << time_taken2 << setprecision(20);
	cout << " sec " << endl;
	cout << endl;
}

void time_merge()
{
	clock_t start1, end1, start2, end2;
	List A;
	srand(time(NULL));
	for (int i = 0; i < 1000; i++)
	{
		A.push_front(rand() % (100 + 1));
	}
	cout << endl;
	cout << "LIST OF RANDOM NUMBERS" << endl;
	cout << endl;
	A.show();
	cout << endl;
	start1 = clock();
	start2 = clock();
	A.merge_sort();
	end1 = clock();
	long double time_taken1 = long double(end1 - start1) / long double(CLOCKS_PER_SEC);
	cout << "AFTER MERGE SORT - INCREASING" << endl;
	cout << endl;
	A.show();
	cout << endl;
	cout << "TIME : " << fixed << time_taken1 << setprecision(20);
	cout << " sec " << endl;
	cout << endl;
	A.reverse();
	end2 = clock();
	long double time_taken2 = long double(end2 - start2) / long double(CLOCKS_PER_SEC);
	cout << endl;
	cout << "AFTER MERGE SORT - DECREASING" << endl;
	cout << endl;
	A.show();
	cout << endl;
	cout << "TIME : " << fixed << time_taken2 << setprecision(20);
	cout << " sec " << endl;
	cout << endl;
}

void time_insertion()
{
	clock_t start1, end1, start2, end2;
	srand(time(NULL));
	cout << "AFTER INSERTION SORT - INCREASING" << endl;
	cout << endl;
	start1 = clock();
	insertion_sort();
	end1 = clock();
	long double time_taken1 = long double(end1 - start1) / long double(CLOCKS_PER_SEC);
	cout << endl;
	cout << "TIME : " << fixed << time_taken1 << setprecision(20);
	cout << " sec " << endl;
	cout << endl;
	cout << "AFTER INSERTION SORT - DECREASING" << endl;
	cout << endl;
	start2 = clock();
	insertion_sort_reverse();
	end2 = clock();
	long double time_taken2 = long double(end2 - start2) / long double(CLOCKS_PER_SEC);
	cout << endl;
	cout << "TIME : " << fixed << time_taken2 << setprecision(20);
	cout << " sec " << endl;
	cout << endl;
}

void time_selection()
{
	clock_t start1, end1, start2, end2;
	List B;
	srand(time(NULL));
	for (int i = 0; i < 1000; i++)
	{
		B.push_front(rand() % (100 + 1));
	}
	cout << "LIST OF RANDOM NUMBERS" << endl;
	cout << endl;
	B.show();
	cout << endl;
	cout << "AFTER SELECTION SORT - INCREASING" << endl;
	cout << endl;
	start1 = clock();
	B.selection_sort();
	end1 = clock();
	long double time_taken1 = long double(end1 - start1) / long double(CLOCKS_PER_SEC);
	B.show();
	cout << endl;
	cout << "TIME : " << fixed << time_taken1 << setprecision(20);
	cout << " sec " << endl;
	cout << endl;
	start2 = clock();
	B.selection_sort_reverse();
	end2 = clock();
	long double time_taken2 = long double(end2 - start2) / long double(CLOCKS_PER_SEC);
	cout << endl;
	cout << "AFTER SELECTION SORT - DECREASING" << endl;
	cout << endl;
	B.show();
	cout << endl;
	cout << "TIME : " << fixed << time_taken2 << setprecision(20);
	cout << " sec " << endl;
	cout << endl;
}

void List::reverse()
{
	Element* el1, * el2;
	if (head != NULL)
	{
		el2 = head;
		while (el2->next)
		{
			el1 = el2->next;
			el2->next = el1->next;
			el1->next = head;
			head = el1;
		}
	}
}

int main()
{
	int choice;

	do
	{
		system("cls");
		cout << "-------------------------\n";
		cout << "     SORTING METHODS\n";
		cout << "-------------------------\n\n"
			"           MENU\n"
			" ------------------------\n"
			"|  0  -  EXIT            |\n"
			"|  1  -  MERGE SORT      |\n"
			"|  2  -  INSERTION SORT  |\n"
			"|  3  -  SELECTION SORT  |\n"
			"|  4  -  HEAP SORT       |\n"
			"|  5  -  QUICK SORT      |\n"
			"|  6  -  BUCKET SORT      |\n"
			" ------------------------\n"
			"\n"
			"Your choice : ";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1: time_merge(); break;
		case 2: time_insertion(); break;
		case 3: time_selection(); break;
		case 4: time_heap(); break;
		case 5: time_quick(); break;
		case 6: time_bucket(); break;
		}
		if ((choice >= 1) && (choice <= 6))
		{
			cout << endl;
			system("pause");
		}
	} while (choice);


	getchar(); getchar();
	return 0;
}