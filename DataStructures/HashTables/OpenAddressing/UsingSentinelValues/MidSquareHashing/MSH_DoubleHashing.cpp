#include <iostream>
#include <iomanip>
#include <cassert>
#include <math.h>
using namespace std;

typedef int ItemType; 
const int TABLE_SIZE = 31; 
const int EMPTY = -1;
const int DELETED = -999;

struct TableNode {
    int key;         
    ItemType data;   

    TableNode() : key(EMPTY), data(0) {} //EMPTY means empty
};

class HashTable {
public:
    HashTable();
    void insert(const TableNode& entry);
    void remove(int key);
    void find(int key, bool& found, TableNode& result) const;
    int size() const;
    void print() const;

private:
    int midSquareHash(int key) const;
    int secondaryHash(int key) const;
    int doubleHash(int key, int attempt) const;
    void findIndex(int key, bool& found, int& index) const;

    TableNode table[TABLE_SIZE]; 
    int used;
};

HashTable::HashTable() {
    used = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].key = EMPTY; //init all slots to empty
    }
}

//primary hash using midsquare method
int HashTable::midSquareHash(int key) const {
    long long squared = static_cast<long long>(key) * key; 

    if (squared < 100) {
        return squared % TABLE_SIZE;
    }

    int totalDigits = log10(squared) + 1;          
    int divisor = pow(10, totalDigits / 2 - 1);           
    int middle = (squared / divisor) % 1000;     
    return middle % TABLE_SIZE; 
}

//secondary hash function to reduce clustering
int HashTable::secondaryHash(int key) const {
    return 1 + (key % (TABLE_SIZE - 1)); //ensures step size is non-zero
}

//double hashing combines primary and secondary hash
int HashTable::doubleHash(int key, int attempt) const {
    return (midSquareHash(key) + attempt * secondaryHash(key)) % TABLE_SIZE;
}

void HashTable::findIndex(int key, bool& found, int& index) const {
    int attempt = 0;
    while (attempt < TABLE_SIZE) {
        index = doubleHash(key, attempt); //use double hashing for probing

        if (table[index].key == EMPTY || (table[index].key == key && table[index].key != DELETED)) {
            found = (table[index].key == key); //check if key matches
            return;
        }
        attempt++;
    }

    found = false; //not found after probing
}

void HashTable::insert(const TableNode& entry) {
    bool alreadyThere;
    int index;

    findIndex(entry.key, alreadyThere, index);
    if (alreadyThere) {
        table[index].data = entry.data; //update data if key exists
    } else {

        if (size() == TABLE_SIZE) {
            cout << "Unable to insert key: " << entry.key << ". Hash table is full.\n";
            return;
        } //table should not be full

        int attempt = 0;
        while (attempt < TABLE_SIZE) {
            index = doubleHash(entry.key, attempt); //find next slot using double hash

            if (table[index].key == EMPTY || table[index].key == DELETED) { //empty or deleted slot
                table[index] = entry;
                used++; //increment count
                return;
            }
            attempt++;
        }

        cout << "unable to insert key: " << entry.key << ". hash table full.\n";
    }
}

void HashTable::remove(int key) {
    bool found;
    int index;

    findIndex(key, found, index);

    if (!found) {
        cout << "key not found.\n";
        return;
    }

    table[index].key = DELETED; //mark slot as deleted
    used--; //decrease count

    cout << "key " << key << " removed.\n";
}

void HashTable::find(int key, bool& found, TableNode& result) const {
    int index;
    findIndex(key, found, index);

    if (found) {
        result = table[index]; //return found record
    }
}

int HashTable::size() const {
    return used; //return number of used slots
}

void HashTable::print() const {
    cout << "the hash table is:\n";
    cout << "index   key   data\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << setw(5) << i << setw(6) << table[i].key;
        if (table[i].key != EMPTY && table[i].key != DELETED) {
            cout << setw(8) << table[i].data;
        }
        cout << endl;
    }
    cout << endl;
}

void print_menu() {
    cout << "\nthe following choices are available:\n";
    cout << " i   insert a new record or update an existing record\n";
    cout << " f   find a record\n";
    cout << " s   get the number of records\n";
    cout << " r   remove a record\n";
    cout << " q   quit this test program\n\n";
}

int main() {
    HashTable dataTable;
    TableNode rec;
    int key;
    bool found;
    char choice;

    do {
        print_menu();
        cout << "enter choice: ";
        cin >> choice;
        cout << endl;
        choice = toupper(choice);

        switch (choice) {
            case 'I': //insert
                cout << "enter key (int >= 0) for record: ";
                cin >> rec.key;
                cout << "enter data (int) for record: ";
                cin >> rec.data;
                dataTable.insert(rec);
                cout << "record inserted.\n";
                dataTable.print();
                break;

            case 'F': //find
                cout << "enter key (int >= 0) to search for: ";
                cin >> key;
                dataTable.find(key, found, rec);
                if (found) {
                    cout << "record found:\n";
                    cout << "   key  = " << rec.key << "\n";
                    cout << "   data = " << rec.data << "\n\n";
                } else {
                    cout << "record with key " << key << " not found.\n\n";
                }
                break;

            case 'S': //size
                cout << "there are " << dataTable.size() << " records in the table.\n";
                cout << "there are " << (TABLE_SIZE - dataTable.size()) << " empty slots left in the table.\n\n";
                break;

            case 'R': //remove
                cout << "enter key (int >= 0) to remove: ";
                cin >> key;
                dataTable.remove(key);
                dataTable.print();
                break;

            case 'Q': //quit
                cout << "exiting program.\n";
                break;

            default:
                cout << choice << " is an invalid choice.\n";
        }
    } while (choice != 'Q');

    return 0;
}
