#include <iostream>
using namespace std;

class Queue{
    int front, rear, size;
    int* array;

    public:
    Queue(int size){
        this->size = size;
        array = new int[size];
        front = -1;
        rear = -1;
    }

    ~Queue(){
        delete[] array;
    }

    bool isEmpty(){
        return  (front == -1 || front > rear );
    }

    bool isFull(){
        return rear == size - 1;
    }

    void enqueue(int data){
        if (isFull()){
            cout<< "Stack is full";
            return;
        }

        if (front == -1)    
        {
            front = 0;
        }

        rear ++;
        array[rear] = data;
    }

    int dequeue(){
        if (isEmpty())
        {
            cout<<"empty queue";
            return -1;
        }

        int data = array[front];
        front ++;
        return data;
        
    }

    int peek(){
        if(isEmpty()){
            cout<<"queue is empty";
            return -1;
        }

        return array[front];
    }

    int getLength(){
        if(isEmpty()){
            return 0;
        }
        return rear - front + 1;
    }
};

int main() {
    Queue queue(5);

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50); 

    cout<<queue.getLength()<<endl; 

    queue.dequeue();
    queue.dequeue();

    cout<<queue.getLength()<<endl; 

    queue.enqueue(60); 
    cout <<endl;

    cout<<queue.getLength()<<endl; 

    cout<<queue.peek()<<endl;

    return 0;
}