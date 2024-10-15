#include <iostream>
using namespace std;

// Node structure for linked list
class Node {
public:
    int data;
    Node* next;

    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

class Queue {
    Node* front; // Pointer to the front of the queue
    Node* rear;  // Pointer to the rear of the queue
    int size;    // To keep track of the number of elements in the queue

public:
    Queue() {
        front = rear = nullptr;
        size = 0;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }

    // Enqueue a new element to the queue
    void enqueue(int data) {
        Node* newNode = new Node(data);

        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    // Dequeue the front element from the queue
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return -1;
        }

        int dequeuedData = front->data;
        Node* temp = front;
        front = front->next;

        if (front == nullptr) { // If the queue becomes empty after dequeue
            rear = nullptr;
        }

        delete temp;
        size--;
        return dequeuedData;
    }

    // Peek at the front element of the queue
    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return -1;
        }
        return front->data;
    }

    // Get the length of the queue
    int getLength() {
        return size;
    }

    // Print the queue elements
    void printQueue() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }

        Node* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Bubble sort on the queue
    void bubbleSort() {
        if (isEmpty()) return;

        for (int i = 0; i < size - 1; i++) {
            Node* current = front;
            Node* next = front->next;
            for (int j = 0; j < size - i - 1; j++) {
                if (current->data > next->data) {
                    swap(current->data, next->data);
                }
                current = next;
                next = next->next;
            }
        }
    }

    // Selection sort on the queue
    void selectionSort() {
        if (isEmpty()) return;

        for (Node* i = front; i->next != nullptr; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (j->data < minNode->data) {
                    minNode = j;
                }
            }
            swap(i->data, minNode->data);
        }
    }

    // Insertion sort on the queue
    void insertionSort() {
        if (isEmpty()) return;

        Node* sorted = nullptr;

        while (front != nullptr) {
            Node* current = front;
            front = front->next;

            if (sorted == nullptr || sorted->data >= current->data) {
                current->next = sorted;
                sorted = current;
            } else {
                Node* temp = sorted;
                while (temp->next != nullptr && temp->next->data < current->data) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
        }
        front = sorted;
    }
};

int main() {
    Queue queue;

    queue.enqueue(10);
    queue.enqueue(90);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50);

    queue.bubbleSort();
    queue.printQueue();

    cout << "Queue length: " << queue.getLength() << endl;

    queue.dequeue();
    queue.dequeue();

    cout << "Queue length after dequeue: " << queue.getLength() << endl;

    queue.enqueue(60);
    cout << "Queue length after enqueue: " << queue.getLength() << endl;

    cout << "Front element: " << queue.peek() << endl;

    return 0;
}
