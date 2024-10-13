#include <iostream>
using namespace std;

#define MAX 1000

class Stack {
    int top;

    public:
    int arr[MAX];

    Stack(){
        top = -1;
    }

    void push (int data){
        //check if stack is full
        if(top == MAX - 1){
            cout<<"stack is full";
            return;
        }

        arr[++top] = data;
    }

    int pop(){
        //check if stack is empty
        if (top == -1)
        {
            cout << "stack is empty";
        }
        
        return arr[top--];
    }

    bool isEmpty(){
        //check if empty
        return (top == -1);
    }

    int Peek(){
        return arr[top];
    }

    int getLength() {
        return top + 1;
    }

    void printStack() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return;
        }
        for (int i = 0; i <= top; i++) {
            cout << arr[i] << " "; 
        }
        cout << endl;
    }

    void selectionSort() {
        int length = getLength();
        for (int i = 0; i < length - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < length; j++) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            swap(arr[i], arr[minIndex]);
        }
    }

    void insertionSort() {
        int length = getLength();
        for (int i = 1; i < length; i++) {
            int key = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    void bubbleSort() {
    int length = getLength();
    bool swapped;  

    for (int i = 0; i < length - 1; i++) {
        swapped = false;  

        for (int j = 0; j < length - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);  
                swapped = true;  
            }
        }

        if (!swapped) {
            break;
        }
    }
}

};

int main (){


    Stack s;
    Stack s1;

    s.push(1);
    s.push(3);
    cout << s.getLength() <<endl;
    cout << s.pop()<<endl;
    cout << s.Peek()<<endl;
    s.push(7);
    cout << s.Peek()<<endl;
    cout<< s.isEmpty()<<endl;
    cout<< s1.isEmpty()<<endl;
    s1.pop();

    return 0;
}