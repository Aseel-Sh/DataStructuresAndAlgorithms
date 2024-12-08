#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

//only changes from lp is insert, findindex, and quadratic hashing func

//this is so that if we need to change the type of the data held then it can 
//be easily changed without having to edit entire codebase
using ItemType = int; 

class HashTable{
    private:
        static const int TABLE_SIZE = 31; //pick a prime number

        struct TableNode
        {
            int key;
            ItemType data;
            bool isOccupied;
            bool isDeleted;

            //ctor to initialize empty slots
            TableNode() : key(0), data(0), isOccupied(false), isDeleted(false) {}
        };

        //can also use TableNode table[TABLE_SIZE]
        vector<TableNode> table;
        int used;

        int hash(int key) const{
           return key % TABLE_SIZE;
        }

        int quadraticProbe(int key, int attempt) const {
            return (hash(key) + attempt * attempt) % TABLE_SIZE;
        }


        void findIndex(int key, bool &found, int &index) const{
            
            int attempt = 0;

            while (attempt < TABLE_SIZE) {
                index = quadraticProbe(key, attempt);

                if (!table[index].isOccupied || (table[index].key == key && !table[index].isDeleted)) {
                    found = table[index].isOccupied && table[index].key == key && !table[index].isDeleted;
                    return;
                }
                attempt++;
            }

            found = false;
        }


    public:
        //ctor to initialize the table with TABLE_SIZE elements
        //no need for thi if using table ds
        HashTable() : table(TABLE_SIZE), used(0) {}

        int size(){
            return used;
        }


    bool insert(int key, ItemType data) {
        if (used >= TABLE_SIZE) {
            cout << "Hash table is full.\n";
            return false;
        }

        bool found;
        int index;

        findIndex(key, found, index);

        if (found) {
            table[index].data = data;
            return true;
        }

        int attempt = 0;
        while (attempt < TABLE_SIZE) {
            index = quadraticProbe(key, attempt);

            if (!table[index].isOccupied || table[index].isDeleted) {
                table[index].key = key;
                table[index].data = data;
                table[index].isOccupied = true;
                table[index].isDeleted = false;
                used++;
                return true;
            }
            attempt++;
        }

        cout << "Unable to insert key: " << key << "\n";
        return false;
    }

        bool remove(int key){
            bool found;
            int index;

            findIndex(key, found, index);

            if (!found) {
                cout << "Key not found!\n";
                return false;
            }

            table[index].isDeleted = true;
            used--;
            return true;
        }

        bool find(int key, ItemType &data){
            bool found;
            int index;

            findIndex(key, found, index);

            if (found) {
                data = table[index].data;
                return true;
            }

            return false;
        }

        // void print() const {
        //     cout << "Hash Table:" << endl;
        //     for (int i = 0; i < TABLE_SIZE; i++) {
        //         if (table[i].isOccupied) {
        //             if (table[i].isDeleted) {
        //                 cout << "[" << i << "]: Deleted" << endl;
        //             } else {
        //                 cout << "[" << i << "]: Key = " << table[i].key 
        //                     << ", Data = " << table[i].data << endl;
        //             }
        //         } else {
        //             cout << "[" << i << "]: Empty" << endl;
        //         }
        //     }
        // }
        
        void print() const {
            cout << "The hash table is:\n";
            cout << "Index   Key   Data\n";
            for (int i = 0; i < TABLE_SIZE; i++) {
                cout << setw(5) << i;

                if (!table[i].isOccupied) {
                    cout << setw(6) << "(E)"; 
                } else if (table[i].isDeleted) {
                    cout << setw(6) << "(D)";
                } else {
                    cout << setw(6) << table[i].key << setw(8) << table[i].data;
                }

                cout << endl;
            }
            cout << endl;
    }

};

int main() {
    HashTable ht;


    ht.insert(10, 100);
    ht.insert(41, 200); // Causes a collision with key=10
    ht.insert(72, 300); 
    ht.insert(15, 100);
    ht.insert(46, 200);
    ht.insert(77, 300);
    ht.insert(108, 300);
    ht.insert(139, 300);     

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