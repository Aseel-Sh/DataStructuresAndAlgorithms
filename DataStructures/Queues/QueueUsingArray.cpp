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

    void printQueue() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }

        for (int i = front; i <= rear; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }

    void bubbleSort() {
        int len = getLength();
        for (int i = 0; i < len - 1; i++) {
            for (int j = front; j < rear - i; j++) {
                if (array[j] > array[j + 1]) {
                    swap(array[j], array[j + 1]);
                }
            }
        }
    }

    void selectionSort() {
        int len = getLength();
        for (int i = front; i < rear; i++) {
            int minIndex = i;
            for (int j = i + 1; j <= rear; j++) {
                if (array[j] < array[minIndex]) {
                    minIndex = j;
                }
            }
            swap(array[i], array[minIndex]);
        }
    }

    void insertionSort() {
        int len = getLength();
        for (int i = front + 1; i <= rear; i++) {
            int key = array[i];
            int j = i - 1;
            while (j >= front && array[j] > key) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = key;
        }
    }


};

int main() {
    Queue queue(5);

    queue.enqueue(10);
    queue.enqueue(90);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50); 

    queue.bubbleSort();
    queue.printQueue();

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