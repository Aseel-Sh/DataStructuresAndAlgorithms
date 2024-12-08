#include <iostream>
#include <iomanip>
using namespace std;

typedef int ItemType; 

//key-value pair
struct TableNode {
    int key;
    ItemType data;
};

//node in the linked list
struct Node {
    TableNode entry; //key-value pair aka data
    Node* next; 

    Node(int key, ItemType data) : entry({key, data}), next(nullptr) {}   
};

class HashTable {
private:
    static const int TABLE_SIZE = 31; 
    Node* table[TABLE_SIZE]; //arr of ptrs to linked lists

    int midSquareHash(int key) const {
        int squared = key * key;
        string squaredStr = to_string(squared);
        int start = (squaredStr.length() / 2) - 1;
        int middleDigits = stoi(squaredStr.substr(start, 3));
        return middleDigits % TABLE_SIZE;
    }

    bool findPtr(int key, Node*& nodePtr, int& index) const {
        index = midSquareHash(key); 
        Node* current = table[index];

        while (current != nullptr) {
            if (current->entry.key == key) {
                nodePtr = current; 
                return true;      
            }
            current = current->next;
        }
        nodePtr = nullptr;
        return false;
    }

public:
    //ctor initializes the table with null pointers
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    //free memory
    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp; //free for each node
            }
        }
    }

    bool insert(int key, ItemType data) {
        Node* existingNode;
        int index;
        if (findPtr(key, existingNode, index)) {
            existingNode->entry.data = data;
            return false; //only got updated
        }

        //add node at the beginning of the chain
        Node* newNode = new Node(key, data);
        newNode->next = table[index];
        table[index] = newNode;
        return true; //added new node
    }

    bool find(int key, ItemType& data) const {
        Node* result;
        int index;
        if (findPtr(key, result, index)) {
            data = result->entry.data;
            return true;
        }
        return false;
    }

    bool remove(int key) {
        int index = midSquareHash(key);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->entry.key == key) {
                if (prev == nullptr) {
                    table[index] = current->next; //remove first node
                } else {
                    prev->next = current->next; //make prevs ptr point to element after deleted element
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false; //not found
    }

    void print() const {
        cout << "The hash table is:" << endl;
        cout << "Index    Key    Data" << endl;

        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << setw(5) << i << " : ";

            Node* ptr = table[i];

            while (ptr != nullptr) {
                cout << setw(5) << ptr->entry.key << setw(8) << ptr->entry.data << " -> ";
                ptr = ptr->next; 
            }
            cout << "nullptr" << endl;
        }
    }
};

int main() {
    HashTable ht;

    ht.insert(10, 100);
    ht.insert(40, 200); //may cause collision with key 10
    ht.insert(72, 300);
    ht.insert(103, 400); //another possible collision
    ht.insert(133, 500);

    cout << "Initial Table:\n";
    ht.print();

    int value;
    if (ht.find(41, value)) {
        cout << "Found key 41 with value: " << value << endl;
    } else {
        cout << "Key 41 not found.\n";
    }

    ht.remove(41);
    cout << "\nTable after removing key 41:\n";
    ht.print();

    if (ht.find(41, value)) {
        cout << "Found key 41 with value: " << value << endl;
    } else {
        cout << "Key 41 not found.\n";
    }

    return 0;
}