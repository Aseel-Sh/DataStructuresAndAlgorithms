#include <iostream>
using namespace std;

//Define Node type that represents a single node
class Node {
    public:
    int data;
    Node* next;

    //Default ctor
    Node(){
        data = 0;
        next = nullptr;
    }

    //Parameterized ctor
    Node (int data){
        this->data = data;
        this->next = nullptr;
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

        //insert the new node
        newNode->next = this->head;
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
            return;
        } else{ //if not empty set tail to last element
            tail->next = newNode;
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
        prevNode->next = newNode;
        
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


};

int main(){
    LinkedList list;
    LinkedList list2;
    LinkedList list3;
    LinkedList list4;

    cout << "Prepended List: ";
    list.Prepend(4);
    list.Prepend(3);
    list.Prepend(7);

    list.print();
    cout << endl;

    cout << "Appended List: ";
    list2.Append(1);
    list2.Append(0);
    list2.Append(9);

    list2.print();
    cout<<endl;

    cout<< "Insert After: ";
    Node* node3 = list.Find(3);
    list.InsertAfter(node3, 1);
    list.print();
    cout<<endl;

    cout<< "Insert After 10 (not found): ";
    Node* nodeNull = list.Find(10);
    list.InsertAfter(nodeNull, 1);

    cout<< "Insert After 4: ";
    Node* node4 = list.Find(4);
    list.InsertAfter(node4, 2);
    list.print();
    cout<<endl;

    list3.InsertAfter(nullptr, 13);
    cout <<"list3 (empty): ";   
    list3.print();
    cout<<endl; 

    cout<<"Removing head: ";
    list2.DeleteAfter(nullptr);
    list2.print();
    cout<<endl;

    cout << "Remove node 1 (after node 3): ";
    list.DeleteAfter(list.Find(3));
    list.print();
    cout<<endl;


    cout << "Remove tail (after node 4): ";
    list.DeleteAfter(list.Find(4));
    list.print();
    cout<<endl;

    cout << "Remove from Last node: ";
    list.DeleteAfter(list2.Find(9));
    cout<<endl;

    cout << "Remove from empty list: ";
    list.DeleteAfter(nullptr);
    list4.print();

    cout << "check if empty: "<<endl;
    cout<< list2.isEmpty() << endl;
    cout<< list4.isEmpty() << endl;

    return 0;
}