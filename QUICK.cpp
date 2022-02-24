#include <iostream>
#include<stdio.h> 
using namespace std;

///////////////////////////////////////////////

void Swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int Partition(int arr[], int low, int high)
{
    int pivot = arr[high];  
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            Swap(&arr[i], &arr[j]);
        }
    }
    Swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void Quick_Sort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = Partition(arr, low, high);

        Quick_Sort(arr, low, pi - 1);
        Quick_Sort(arr, pi + 1, high);
    }
}

///////////////////////////////////////////////////

int main()
{
	int ar2D[2][3];
    int arr[6];
    int k = 0;
 
    cout << "Podaj 6 elementow tablicy: " << endl;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << "Element " << i + 1 << "x" << j + 1 << " - ";
            cin >> ar2D[i][j];
            arr[k] = ar2D[i][j];
            k++;
        }
    }

    Quick_Sort(arr, 0, 5);
    cout << "Posortowana tablica: " << endl;

    for (int l = 0; l < 6; l++)
    {
        cout << arr[l] << ", ";
    }

	return 0;
}