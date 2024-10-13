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

    void printQueue() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }

        int i = front;
        while (true) {
            cout << array[i] << " ";
            if (i == rear) break;  
            i = (i + 1) % size;  
        }
        cout << endl;
    }

    void bubbleSort() {
    int length = getLength();
    bool swapped;

    for (int i = 0; i < length - 1; i++) {
        swapped = false;
        int current = front;
        for (int j = 0; j < length - i - 1; j++) {
            int next = (current + 1) % size;  
            if (array[current] > array[next]) {
                swap(array[current], array[next]);
                swapped = true;
            }
            current = next;  
        }

        if (!swapped) {
            break;  
        }
        }
    }
    void selectionSort(){
    int length = getLength();
    for (int i = 0; i < length - 1; i++) {
        int currentIndex = (front + i) % size;
        int minIndex = currentIndex;
        for (int j = i + 1; j < length; j++) {
            int nextIndex = (front + j) % size;
            if (array[nextIndex] < array[minIndex]) {
                minIndex = nextIndex;
            }
        }
            swap(array[currentIndex], array[minIndex]);
        }
    }

    void insertionSort() {
    int length = getLength();
    for (int i = 1; i < length; i++) {
        int currentIndex = (front + i) % size;
        int key = array[currentIndex];
        int j = i - 1;
        int prevIndex = (front + j) % size;

        while (j >= 0 && array[prevIndex] > key) {
            int nextIndex = (prevIndex + 1) % size;
            array[nextIndex] = array[prevIndex];
            j--;
            prevIndex = (front + j) % size;
        }
        array[(prevIndex + 1) % size] = key;
    }
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
