#include <iostream>
#include <string>

using namespace std;

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
		cout << i << " " << PI[i] << endl;
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

int main()
{
	string s = "asdasasdfasadgasa";
	string w = "asad";

	int pos = navie_pattern(s, w);
	pos = KnuttMorrisPratt(s, w);
	
	if (pos == -1)
		cout << "Wzorzec nie znaleziono" << endl;
	else
		cout << "Wzorzec znaleziono na poszycji " << pos << endl;

	system("pause");
}