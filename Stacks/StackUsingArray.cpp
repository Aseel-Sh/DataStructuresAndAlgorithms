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

};

int main (){


    Stack s;
    Stack s1;

    s.push(1);
    s.push(3);
    cout << s.pop()<<endl;
    cout << s.Peek()<<endl;
    s.push(7);
    cout << s.Peek()<<endl;
    cout<< s.isEmpty()<<endl;
    cout<< s1.isEmpty()<<endl;
    s1.pop();

    return 0;
}