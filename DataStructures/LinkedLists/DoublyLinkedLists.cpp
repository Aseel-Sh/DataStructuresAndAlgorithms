#include <iostream>
using namespace std;

//Define Node type that represents a single node
class Node {
    public:
    int data;
    Node* next;
    Node* prev;

    //Default ctor
    Node(){
        data = 0;
        next = nullptr;
        prev = nullptr;
    }

    //Parameterized ctor
    Node (int data){
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

//Define class that contains ptr to the head and all basic func
class LinkedList {

    Node *head;
    Node *tail;

    public:
    //Default ctor
    LinkedList(){
        head =  nullptr;
        tail = nullptr;
    }

    //insert at head
    void Prepend(int data){
        //create new node
        Node *newNode = new Node(data);

        //if list empty then set head and tail to new node
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
            return;
        }

        //insert the new node
        newNode->next = this->head;
        head->prev = newNode;
        this->head = newNode;
    }

    //insert at tail
    void Append(int data){
        //create new node
        Node *newNode = new Node(data);

        //assign head and tail if list empty
        if (head == nullptr){
            head = newNode;
            tail = newNode;
        } else{ //if not empty set tail to last element
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    //find a specific node
    Node* Find(int val){
        Node *temp = head;
        while (temp != nullptr)
        {
            if(temp->data == val){
                return temp;
            }else{
                temp = temp->next;
            }
        }

        return nullptr;
        
    }

    //insert After
    void InsertAfter(Node *prevNode, int data){

        //if empty list just append
        if(head == nullptr){
            Append(data);
            return;
        }

        //prev ptr cant be null (prev ptr not found)
        if(prevNode == nullptr){
            cout << "Prev node cant be null"<<endl;
            return;
        }

        //insert node
        Node *newNode = new Node(data);
        newNode->next = prevNode->next;
        newNode->prev = prevNode;
        prevNode->next = newNode;

        //if the nodes next ptr prev ptr
        if (newNode-> next != nullptr)      
        {
            newNode->next->prev = newNode;
        }
        
        
        //if prev node is tail then insert node as new tail
        if (prevNode == tail)
        {
            tail = newNode;
        }
        

    }

    //Remove Ater
    void DeleteAfter(Node *prevNode){
        //special case: if prev node is null remove head
        if (prevNode == nullptr)
        {
            //if list already empty
            if (head == nullptr)
            {
                cout <<"List is empty";
                return;
            }
            
            Node *sucNode = head->next;
            delete head;
            head = sucNode;

            //if del made list empty make tail nullptr
            if (head == nullptr)
            {
                tail = nullptr;
            } else {
                head->prev = nullptr;
            }

            return;
            
        }

        //remove node
        Node *sucNode = prevNode->next;
        //if no sucnode then del nthn
        if (sucNode == nullptr)
        {
            cout << "No node to remove";
            return;
        }
        prevNode->next = sucNode->next;
        //if suc node next ptr not null then update prev ptr
        if (sucNode->next != nullptr)
        {
            sucNode->next->prev = prevNode;
        }
        
        delete sucNode;

        //update tail (if tail was removed)
        if (prevNode->next == nullptr)
        {
            tail = prevNode;
        }
        
    }

    //check if empty
    bool isEmpty(){
        return head == nullptr;
    }

    void print(){
        Node *temp = head;

        //check if list is empty
        if (head == nullptr){
            cout << "List empty" << endl;
            return;
        }

        //traverse list
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

    //print reverse list
    void printReverse(){
                
        Node *temp = tail;

        //check if list is empty
        if (tail == nullptr){
            cout << "List empty" << endl;
            return;
        }

        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        
    }

    void remove(int data) {
        Node* temp = head;
        while (temp != nullptr && temp->data != data) {
            temp = temp->next;
        }
        if (temp == nullptr) {
            cout << "Node with data " << data << " not found." << endl;
            return;
        }
        if (temp == head) {
            head = temp->next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
            delete temp;
            return;
        }
        if (temp == tail) {
            tail = temp->prev;
            tail->next = nullptr;
            delete temp;
            return;
        }
        Node* prevNode = temp->prev;
        Node* nextNode = temp->next;
        if (prevNode != nullptr) {
            prevNode->next = nextNode;
        }
        if (nextNode != nullptr) {
            nextNode->prev = prevNode;
        }
        delete temp;
    }

    //getlength
    int getLength(){
        int length = 0;
        Node *temp = head;

        while(temp != nullptr){
            length ++;
            temp = temp->next;
        }

        return length;
    }
    // Bubble sort
    void bubbleSort() {
        if (head == nullptr) return;

        bool swapped;
        Node* ptr1;
        Node* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = head;

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

    // Selection sort
    void selectionSort() {
        if (head == nullptr) return;

        for (Node* i = head; i->next != nullptr; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (j->data < minNode->data) {
                    minNode = j;
                }
            }
            swap(i->data, minNode->data);
        }
    }

    // Insertion sort
    void insertionSort() {
        if (head == nullptr) return;

        Node* sorted = nullptr;

        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            if (sorted == nullptr || sorted->data >= current->data) {
                current->next = sorted;
                if (sorted != nullptr) sorted->prev = current;
                sorted = current;
                sorted->prev = nullptr;
            }
            else {
                Node* temp = sorted;
                while (temp->next != nullptr && temp->next->data < current->data) {
                    temp = temp->next;
                }
                current->next = temp->next;
                if (temp->next != nullptr) temp->next->prev = current;
                temp->next = current;
                current->prev = temp;
            }
            current = next;
        }
        head = sorted;

        // Update tail
        tail = head;
        while (tail->next != nullptr) {
            tail = tail->next;
        }
    }

};

int main() {
    LinkedList list;

    cout << "Prepended List: ";
    list.Prepend(4);
    list.Prepend(3);
    list.Prepend(7);
    list.print();

    cout << "Appended List: ";
    list.Append(1);
    list.Append(0);
    list.Append(9);
    list.print();

    cout << "Insert After 3: ";
    Node* node3 = list.Find(3);
    list.InsertAfter(node3, 1);
    list.print();

    cout << "Remove node after 3: ";
    list.DeleteAfter(node3);
    list.print();
    
    
    list.printReverse();

    return 0;
}