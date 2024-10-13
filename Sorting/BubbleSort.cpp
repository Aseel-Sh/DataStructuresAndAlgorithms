#include <iostream>
#include <vector>
using namespace std;

void bubbleSort(vector<int>& arr){

    int n = arr.size();

    for (int i = 0; i < n - 1; i++){
    
        for (int j = 0; j < n- i - 1; j++)
        {
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }

    }   
}

void printArray(vector<int> arr){
    for (int i = 0; i < arr.size(); i++)
    {
        cout << " " << arr[i];
    }
    
}

//bubble sort no vector

void bubbleSort2(int arr[], int size){
    //loop to go through each element
    for (int i = 0; i < size - 1; i++)
    {
        //loop to compare against each other
        for (int j = 0; j < size - i - 1; j++)
        {
            //swap in asc order
            if (arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
            
        }
        
    }
    
}

void printArray2(int arr[], int size){
    for (int i = 0; i < size; i++)
    {
        cout << " " << arr[i];
    }
    
}

int main(){
    vector <int> meow = {6, 7, 3, 4};
    int arr[] = {6, 3, 4, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(meow);
    printArray(meow);
    cout << endl;
    bubbleSort2(arr, size);
    printArray2(arr, size);


    
}
