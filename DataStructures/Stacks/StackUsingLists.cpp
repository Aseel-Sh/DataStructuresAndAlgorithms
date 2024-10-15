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

class Stack {
    Node* top; // Pointer to the top of the stack

public:
    Stack() {
        top = nullptr; // Initialize stack as empty
    }

    // Push a new element onto the stack
    void push(int data) {
        Node* newNode = new Node(data); // Create a new node
        newNode->next = top; // Link new node to the current top
        top = newNode; // Update top pointer to the new node
    }

    // Pop the top element from the stack
    int pop() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return -1;
        }
        int poppedData = top->data; // Get the top data
        Node* temp = top; // Temporarily store the top node
        top = top->next; // Move top pointer to the next node
        delete temp; // Delete the old top node
        return poppedData;
    }

    // Check if the stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    // Peek at the top element of the stack
    int Peek() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return top->data;
    }

    // Get the length of the stack
    int getLength() {
        int count = 0;
        Node* current = top;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    // Print the stack elements
    void printStack() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return;
        }
        Node* current = top;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Selection sort on the stack
    void selectionSort() {
        if (isEmpty()) return;

        for (Node* i = top; i->next != nullptr; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (j->data < minNode->data) {
                    minNode = j;
                }
            }
            swap(i->data, minNode->data);
        }
    }

    // Insertion sort on the stack
    void insertionSort() {
        if (isEmpty()) return;

        Node* sorted = nullptr;

        while (top != nullptr) {
            Node* current = top;
            top = top->next;

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
        top = sorted;
    }

    // Bubble sort on the stack
    void bubbleSort() {
        if (isEmpty()) return;

        bool swapped;
        Node* ptr1;
        Node* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = top;

            while (ptr1->next != lptr) {
                if (ptr1->data > ptr1->next->data) {
                    swap(ptr1->data, ptr1->next->data);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }
};

int main() {
    Stack s;
    Stack s1;

    s.push(1);
    s.push(3);
    cout << "Length of stack: " << s.getLength() << endl;
    cout << "Popped element: " << s.pop() << endl;
    cout << "Top element: " << s.Peek() << endl;
    s.push(7);
    cout << "Top element: " << s.Peek() << endl;
    cout << "Is stack empty? " << s.isEmpty() << endl;
    cout << "Is second stack empty? " << s1.isEmpty() << endl;
    s1.pop();  // Attempt to pop from an empty stack

    return 0;
}
