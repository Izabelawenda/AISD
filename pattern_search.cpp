#include <iostream>
#include <string>
#include <fstream>

using namespace std;
string line[23216];

int navie_pattern(string s, string w)
{
	bool found = false;
	for (int i = 0; i < s.length(); i++)
	{
		found = true;
		for (int j = 0; j < w.length(); j++)
		{
			if (s[j + i] != w[j])
			{
				found = false;
				break;
			}
		}
		if (found == true)
		{
			return i;
		}
	}

	return -1;
}

int KnuttMorrisPratt(string s, string w)
{
	int* PI;
	PI = new int[w.length()];


	for (int i = 0; i < w.length(); i++)
		PI[i] = 0;

	int b = -1;
	PI[0] = -1;


	for (int i = 1; i < w.length(); i++)
	{
		while ((b > -1) && w[b] != w[i - 1]) b = PI[b];
		++b;
		if (i == w.length() || (w[i] != w[b])) PI[i] = b;
		else PI[i] = PI[b];
		//cout << i << " " << PI[i] << endl;
	}

	int pos = 0;
	b = 0;

	for (int i = 0; i < s.length(); i++)
	{
		while ((b > -1) && (w[b] != s[i])) b = PI[b];
		if (++b == w.length())
		{
			while (pos < i - b + 1)
				pos++;
			b = PI[b];
		}
	}

	return pos;
}

void read_file()
{
	ifstream file;
	file.open("Job-case1.inp");

	if (file.is_open())
	{
		for (int i = 0; i < 23216; i++)
		{
			getline(file, line[i]);
			//cout << line[i];
		}
	}
	else
	{
		cout << "Cannot open file";
	}

	file.close();
}

void PKT1()
{
	read_file();
	string s;
	string w = "*Part, name=";

	for (int i = 0; i < 23216; i++)
	{
		int pos = navie_pattern(line[i], w);
		pos = KnuttMorrisPratt(line[i], w);

		if (pos == -1)
			cout << "Pattern not found" << endl;
		else
		{
			cout << "Pattern found on position: " << pos << endl;
			s = line[i];
			for (int i = 12; i < s.length(); i++)
			{
				cout << s[i]; //wypisujemy nazwy czêœci po znakach *Part, name=
			}
		}
	}
}

void PKT2()
{
	read_file();
	string s;
	string w = "*Elset, elset=";
	string x = "*Nset, nset=";

	for (int i = 0; i < 23216; i++)
	{
		//ELSET
		int pos = navie_pattern(line[i], w);
		pos = KnuttMorrisPratt(line[i], w);

		if (pos == -1)
			cout << "Pattern not found" << endl;
		else
		{
			cout << "Pattern found on position: " << pos << endl;
			s = line[i];
			for (int i = 14; i < s.length(); i++)
			{
				cout << s[i]; //wypisujemy nazwy elsetów po znakach *Elset, elset=
			}
		}

		//NSET
		int pos = navie_pattern(line[i], x);
		pos = KnuttMorrisPratt(line[i], x);

		if (pos == -1)
			cout << "Pattern not found" << endl;
		else
		{
			cout << "Pattern found on position: " << pos << endl;
			s = line[i];
			for (int i = 12; i < s.length(); i++)
			{
				cout << s[i]; //wypisujemy nazwy nsetów po znakach *Nset, nset=
			}
		}
	}
}

void PKT3()
{
	read_file();
	string s;
	string w = "*Element, type=";

	for (int i = 0; i < 23216; i++)
	{
		int pos = navie_pattern(line[i], w);
		pos = KnuttMorrisPratt(line[i], w);

		if (pos == -1)
			cout << "Pattern not found" << endl;
		else
		{
			cout << "Pattern found on position: " << pos << endl;
			s = line[i];
			for (int i = 15; i < s.length(); i++)
			{
				cout << s[i]; //wypisujemy u¿yty typ elementu po znakach *Element, type=
			}
		}
	}
}

void PKT4()
{
	read_file();
	string s;
	string x;
	string w = "*Material, name=";
	struct materials 
	{
		string name, conductivity, density, specific_heat;
	}tab[100];

	for (int i = 0; i < 23216; i++)
	{
		int pos = navie_pattern(line[i], w);
		pos = KnuttMorrisPratt(line[i], w);

		if (pos == -1)
			cout << "Pattern not found" << endl;
		else
		{
			cout << "Pattern found on position: " << pos << endl;
			s = line[i];
			for (int j = 15; j < s.length(); j++)
			{
				x[j] = s[j];
			}
			tab[i].name = x;
			tab[i].conductivity = line[i + 2];
			tab[i].density = line[i + 4];
			tab[i].specific_heat = line[i + 6];

			cout << tab[i].name << " " << tab[i].conductivity << " " << tab[i].density << " " << tab[i].specific_heat << endl; //wypisujemy struktury z danymi
		}
	}
}

int main()
{
	PKT1();
	PKT2();
	PKT3();
	PKT4();

	system("pause");
}