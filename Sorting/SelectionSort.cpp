#include<iostream>
#include <vector>
using namespace std;

void selectionSort(vector<int> &arr){
    int n = arr.size();

    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
            
        }

        swap(arr[i], arr[minIndex]);
        
    }
    
}

void printArray(vector<int> &arr){
    for (int i = 0; i < arr.size(); i++)
    {
        cout << " " << arr[i];
    }
    
}

//selection sort no vector
void selectionSort2(int arr[], int n){

    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
            
        }

        swap(arr[i], arr[minIndex]);
        
    }
    
}

void printArray2(int arr[], int n){
    for (int i = 0; i < n ; i++)
    {
        cout << " " << arr[i];
    }
    
}

int main(){
    vector <int> meow = {6, 7, 3, 4};
    int arr[] = {6, 3, 4, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    selectionSort(meow);
    printArray(meow);
    cout << endl;

    selectionSort2(arr, n);
    printArray2(arr, n);


    
}