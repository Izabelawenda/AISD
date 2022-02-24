#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

//zamienilam date panowania u ostatniego prezydenta bo byla na odwrot

struct Person
{
	string name;
	string surname;
	int start_year;
	int end_year;
	string party;
	Person* next;
};

//dodawanie poczatkowego elementu

void add_front(Person *&head, string n, string sn, int st, int en, string fa) 
{
	Person* pom = head;
	Person* tmp = new Person;

	tmp->name = n;
	tmp->surname = sn;
	tmp->start_year = st;
	tmp->end_year = en;
	tmp->party = fa;

	tmp->next = head;
	head = tmp;
}

//dodawanie koncowego elemntu

void add_back(Person *&head, string n, string sn, int st, int en, string fa)
{
	Person *pom = head;
	Person *tmp = new Person;

	tmp->name = n;
	tmp->surname = sn;
	tmp->start_year = st;
	tmp->end_year = en;
	tmp->party = fa;

	tmp->next = NULL;
	if (head)
	{
		while (pom->next != NULL)
		{
			pom = pom->next;
		}
		pom->next = tmp;
	}
	else
	{
		head = tmp;
	}
}

//wypisanie

void show(Person*& head)                                                      
{
	Person* tmp = head;
	while (tmp)
	{
		cout << tmp->name << endl;
		cout << tmp->surname << endl;
		cout << tmp->start_year << endl;
		cout << tmp->end_year << endl;
		cout << tmp->party << endl;
		cout << endl;
		tmp = tmp->next;
	}
}

//lista 

struct List                                                                             
{
	string nam;
	string surn;
	int year;
	List* next;
};


void List_addfront(List*& head, string n, string sn, int y)
{
	List* pom = head;
	List* tmp = new List;

	tmp->nam = n;
	tmp->surn = sn;
	tmp->year = y;
	tmp->next = head;
	head = tmp;
}


void List_show(List *&head)
{
	List* tmp = head;
	while (tmp)
	{
		cout << tmp->nam << " ";
		cout << tmp->surn << endl;
		cout << tmp->year << endl;
		tmp = tmp->next;
	}
}

// najkrotszy czas przy wladzy

List* shortest(Person*& head)                                                   
{
	List* list_1 = new List;
	list_1 = NULL;                                      


	string n, m;
	Person* tmp = head;
	int minimum = INT_MAX;
	while (tmp)
	{
		if ((tmp->end_year - tmp->start_year) < minimum)
		{
			minimum = (tmp->end_year - tmp->start_year);     
		}
		tmp = tmp->next;
	}

	tmp = head;
	while (tmp)
	{
		if ((tmp->end_year - tmp->start_year) == minimum)
		{
			n = tmp->name;
			m = tmp->surname;
			List_addfront(list_1, n, m, minimum);
		}
		tmp = tmp->next;
	}
	return list_1;
}


struct List_party
{
	string nam;
	string surn;
	int fac;
	List_party* next;
};


void Party_addfront(List_party*& head, string n, string sn)
{
	List_party* pom = head;
	List_party* tmp = new List_party;

	tmp->nam = n;
	tmp->surn = sn;

	tmp->next = head;
	head = tmp;
}


void Party_show(List_party*& head)
{
	List_party* tmp = head;
	while (tmp)
	{
		cout << tmp->nam << " ";
		cout << tmp->surn << endl;
		tmp = tmp->next;
	}
}

// prezydenci podanej partii

List_party* party_fun(Person*& head, string f)                                               
{
	List_party* list_f = new List_party;
	list_f = NULL;


	Person* tmp_f = head;
	string n, sn;
	while (tmp_f)
	{
		if (tmp_f->party == f)
		{
			n = tmp_f->name;
			sn = tmp_f->surname;
			Party_addfront(list_f, n, sn);
		}
		tmp_f = tmp_f->next;
	}
	return list_f;
}

// nazwisko w podanym roku

string year_of_control(Person *& head, int rok)                                                          
{
	Person* tmp = head;
	string nick;
	while (tmp)
	{
		if (rok <= tmp->end_year && rok >= tmp->start_year)
		{
			nick = tmp->name + " " + tmp->surname;
		}
		tmp = tmp->next;
	}
	return nick;
}


int main()
{
	Person* list = new Person;
	list = NULL;
	string buffer;
	fstream file("presidents.txt", std::ios::in);

	while (!file.eof())   //czytanie do chwili az nie bedzie linii do czytania
	{
		string name;
		string surname;
		int start_year;
		int end_year;
		string party;

		for (int i = 0; i <= 4; i++)
		{
			file >> buffer;


			if (i == 2)                                                               //dwa nazwiska
			{
				if (isdigit(buffer[0]))
				{
					i++;
				}
			}

			switch (i)
			{
			case 0:
				name = buffer;

				break;

			case 1:
				surname = buffer;
				break;

			case 2:
				surname += " " + buffer;
				break;

			case 3:
			{
				string st = buffer.substr(0, 4);
				string en = buffer.substr(5, 4);
				start_year = stoi(st);
				end_year = stoi(en);
				break;
			}

			case 4:
				party = buffer;
				break;
			}
		}
		add_back(list, name, surname, start_year, end_year, party);
	}

	//POLECENIE 1

	cout << "Exercise 1:" << endl;
	List* list_2 = shortest(list);
	List_show(list_2);

	//POLECENIE 2

	cout << endl << "Exercise 2:" << endl;
	string partytype;
	cout << "Type a party that you choose: ";
	cin >> partytype;
	cout << endl;
	List_party* list_p = party_fun(list, partytype);
	Party_show(list_p);
	cout << endl;

	//POLECENIE 3

	cout << "Exercise 3:" << endl;
	int n;
	cout << "Type a year that you choose: ";
	cin >> n;
	string c = year_of_control(list, n);
	cout << "In year " << n << " " << c << " in control of the kingdom was " << endl << endl;

	return 0;
}