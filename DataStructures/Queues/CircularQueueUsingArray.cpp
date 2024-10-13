#include <iostream>
using namespace std;

class Queue{
    int front, rear, size, capacity;
    int* array;

public:
    Queue(int size){
        this->size = size;
        array = new int[size];
        front = -1;
        rear = -1;
        capacity = 0;  
    }

    ~Queue(){
        delete[] array;
    }

    // Check if the queue is empty
    bool isEmpty(){
        return capacity == 0;  
    }

    // Check if the queue is full
    bool isFull(){
        return capacity == size;  
    }

    // Enqueue an element
    void enqueue(int data){
        if (isFull()){
            cout << "Queue is full. Cannot enqueue " << data << endl;
            return;
        }

        // If queue is empty
        if (front == -1){ 
            front = 0;
        }

        // Circular increment of rear
        rear = (rear + 1) % size;
        array[rear] = data;
        capacity++; 
        cout << data << " enqueued" << endl;
    }

    // Dequeue an element
    int dequeue(){
        if (isEmpty()){
            cout << "Queue is empty. Cannot dequeue." << endl;
            return -1;
        }

        int data = array[front];
        // Circular increment of front
        front = (front + 1) % size;
        capacity--;
        
        // If the queue becomes empty after dequeue, reset front and rear
        if (capacity == 0){
            front = -1;
            rear = -1;
        }

        cout << data << " dequeued" << endl;
        return data;
    }

    // Peek at the front element
    int peek(){
        if (isEmpty()){
            cout << "Queue is empty." << endl;
            return -1;
        }

        return array[front];
    }

    // Get the current length of the queue
    int getLength(){
        return capacity; 
    }
};

int main() {
    Queue queue(5); 

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50);  

    cout << "Current length of queue: " << queue.getLength() << endl;

    queue.dequeue();
    queue.dequeue();

    cout << "Current length after 2 dequeues: " << queue.getLength() << endl;

    queue.enqueue(60);  
    queue.enqueue(70); 

    cout << "Current length after enqueueing 60 and 70: " << queue.getLength() << endl;

    cout << "Front element is: " << queue.peek() << endl;

    return 0;
}
