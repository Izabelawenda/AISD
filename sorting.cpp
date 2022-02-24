#include <iostream>
#include <climits>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;                                 //x, x = liczba operacji

// 1

int difference(int arr[], int size, int stud)
{
	int diff = INT_MAX;								//1 przypisanie
	for (int i = 0; i + stud - 1 < size; i++)		
	{
		int tmp = arr[i + stud - 1] - arr[i];		//5 przypisanie
		if (tmp < diff)								//wykona sie tylko gdy prawda
		{
			diff = tmp;								//1
		}
	}
	return diff;									//1
}

void swap(int* a, int* b)
{
	int tmp = *a;			//1 przypisanie
	*a = *b;				//1 przypisanie
	*b = tmp;				//1 przypisanie
}

int part(int arr[], int min, int max)
{
	int pivot = arr[max];					//1 przypisanie	
	int i = (min - 1);						//1 przypisanie	

	for (int j = min; j <= max - 1; j++)	//min = 0, max = 11
	{
		if (arr[j] <= pivot)				
		{
			i++;							//12 iteracja
			swap(&arr[i], &arr[j]);			//12 wywolanie funkcji
		}
	}
	swap(&arr[i + 1], &arr[max]);			//1 wywolanie funkcji
	return (i + 1);							//1
}

void sort(int arr[], int min, int max )
{
	if (min < max)                            //jesli tak to wykona 
	{
		int tmp = part(arr, min, max);        //2 przypisanie + wywolanie funkcji
		sort(arr, min, tmp - 1);              //1 wywolanie funkcji
		sort(arr, tmp + 1, max);              //1 wywolanie funkcji
	}
}

// 2

void swap2(double* a, double* b)			
{
	double tmp = *a;					//1 przypisanie
	*a = *b;							//1 przypisanie
	*b = tmp;							//1 przypisanie
}

void swap3(string* a, string* b)
{
	string tmp = *a;				//1 przypisanie
	*a = *b;						//1 przypisanie
	*b = tmp;						//1 przypisanie
}

int part2(string arr2[], double arr[], int min, int max)
{
	int pivot = arr[max];									//1 przypisanie
	int pivot2 = atoi(arr2[max].c_str());					//1 przypisanie
	int i = (min - 1);										//1 przypisanie

	for (int j = min; j <= max - 1; j++)					
	{
		if (arr[j] >= pivot)								//jesli tak to wykona sie
		{
			i++;											//27
			swap2(&arr[i], &arr[j]);						//27 wywolanie funkcji	
			swap3(&arr2[i], &arr2[j]);						//27 wywolanie funkcji
		}
	}
	swap2(&arr[i + 1], &arr[max]);							//1 wywolanie funkcji
	swap3(&arr2[i + 1], &arr2[max]);						//1 wywolanie funkcji
	return (i + 1);											//1
}

void sort2(string arr2[], double arr[], int min, int max)
{
	if (min < max)											//jesli tak to wykona sie
	{
		int tmp = part2(arr2, arr, min, max);				//2 przypisanie + wywolanie funkcji
		sort2(arr2, arr, min, tmp - 1);						//1 wywolanie funkcji
		sort2(arr2, arr, tmp + 1, max);						//1 wywolanie funkcji
	}
}

// 3

void function(int arr1[], int size1, int A, int B, int C)
{
	for (int i = 0; i < size1; i++)								
	{
		arr1[i] = A * arr1[i] * arr1[i] + B * arr1[i] + C;		//9 przypisanie
	}
	int inx, maximum = INT_MIN;									//2 przypisanie
	for (int i = 0; i < size1; i++)								
	{
		if (maximum < arr1[i])									//jesli tak to wykona sie
		{
			inx = i;											//9 przypisanie
			maximum = arr1[i];									//9 przypisanie
		}
	}
	int i = 0, j = size1 - 1, temp[9], k = 0;					//4 przypisanie
	while (i < inx && j > inx)									//gdy prawda to wykona sie
	{
		if (arr1[i] < arr1[j])									
		{
			temp[k++] = arr1[i++];								//1 przypisanie albo 
		}														
		else
		{
			temp[k++] = arr1[j--];								//w kazdym przypadku bedzie wykonana 1 operacja
		}
	}
	while (i < inx)												//jesli tak to wykona sie
	{
		temp[k++] = arr1[i++];									//1 przypisanie
	}
	while (j > inx)												//jesli tak to wykona sie
	{
		temp[k++] = arr1[j--];									//1 przypisanie
	}
	temp[size1 - 1] = maximum;									//1 przypisanie
	for (int i = 0; i < size1; i++)								
		arr1[i] = temp[i];										//9 przypisanie
}

// 4
/*
struct Element
{
	int number;
	Element* next;
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
		break;
	}
}*/

// 5

void tab(int arr2[], int size2)
{
	sort(arr2, 0, size2-1);							//1 wywolanie funkcji

	for (int i = 0; i < size2 / 2; i++)				
	{
		cout << arr2[i] << " ";						//11 wypisanie
	}
	for (int j = size2 - 1; j >= size2 / 2; j--)		
	{
		cout << arr2[j] << " ";						//11 wypisanie
	}
}


int main()
{
	// 1

	int arr[] = { 9,8,10,15,20,22,41,34,38,29,23,17 }; //1 przypisanie
	int stud = 8;                                      //1 przypisanie
	int size = sizeof(arr) / sizeof(arr[0]);           //1 przypisanie
	cout << "min difference between chocolates: ";     //1 wyswietlenie
	sort(arr, 0, size - 1);                            //1 wywolanie funkcji
	cout << difference(arr, size, stud);               //2 wyswietlenie + wywolanie fukncji

	// 2

	string name[27];																  //1
	string score[27];														          //1
	double final[27];																  //1
	ifstream file;																	  //1
	file.open("medals.txt", ios::in);												  //1
	for (int i = 0; i < 27; i++)
	{
		getline(file, name[i], '\n');												  //27
		getline(file, score[i], '\n');												  //27
	}
	cout << "\n";																	  //1 wyswietlenie
	for (int k = 0; k < 27; k++)
	{
		final[k] = atof(score[k].c_str());											  //27 przypisanie
	}
	int size3 = sizeof(final) / sizeof(final[0]);                                     //1 przypisanie
	sort2(name, final, 0, size3 - 1);                                                 //1 wywolanie funkcji
	int x;                                                                            //1
	cout << "type which place you want to display: ";                                 //1 wyswietlenie
	cin >> x;                                                                         //1 wczytanie
	while(x<28)
	{
		cout << x << "place:" << endl;                                                //1 wyswietlenie
		cout << "Name: " << name[x-1] << " " << "Score: " << final[x-1] << endl;      //1 wyswietlenie
		break;                                                                        //1
	}

	// 3

	int arr1[] = {-15, -10, -9, 2, 4, 7, 9, 13, 14};		//1 przypisanie
	int size1= sizeof(arr1) / sizeof(arr1[0]);				//1 przypisanie
	int A = -2, B = 3, C = 5;                               //3 przypisanie
	function(arr1, size1, A, B, C);							//1 wywolanie funkcji
	cout << "sorted after function:" << endl;				//1 wyswietlenie	
	for (int i = 0; i < size; i++)							//zalezy od wielkosci tablicy
	{
		cout << arr1[i] << "  ";							//9 wyswietlenie
	}
	cout << endl;											//1 wyswietlenie	

	// 4
	/*
	int array[10000];
	srand(time(NULL));
	int V = 10;
	struct Bucket_arr* bucket = newbucket(V);
	for (int i = 0; i < 10000; i++)
	{
		array[i] = (rand() % (100 + 1));
	}
	for (int i = 0; i < 10000; i++)
	{
		bucket_sort_reverse(bucket, arr[i] / 10000, arr[i]);
	}
	print_buc(bucket);
	*/

	// 5

	int arr2[] = {1, 9, 15, 3, 4, 7, 2, 12, 10, 5, 8};  //1 przypisanie
	int size2 = sizeof(arr2) / sizeof(arr2[0]);			//1 przypisanie
	tab(arr2, size2);									//1 wywolanie funkcji

	return 0;											//1 
}