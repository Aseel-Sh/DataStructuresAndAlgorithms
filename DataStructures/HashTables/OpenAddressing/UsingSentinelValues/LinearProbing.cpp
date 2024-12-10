#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

typedef int ItemType;
const int TABLE_SIZE = 31;
const int EMPTY = -1;
const int DELETED = -999;

struct TableNode {
    int key;
    ItemType data;

    TableNode() : key(EMPTY), data(0) {} 
};

class HashTable {
public:
    HashTable();
    void insert(int key, int data);
    void remove(int key);
    void find(int key, bool& found, int& data) const;
    int size() const;
    void print() const;

private:
    int hash(int key) const;
    int linearProbe(int key, int attempt) const;
    void findIndex(int key, bool& found, int& index) const;

    TableNode table[TABLE_SIZE];
    int used;
};

HashTable::HashTable() {
    used = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].key = EMPTY;
    }
}

int HashTable::hash(int key) const {
    return key % TABLE_SIZE;
}

int HashTable::linearProbe(int key, int attempt) const {
    return (hash(key) + attempt) % TABLE_SIZE;
}

void HashTable::findIndex(int key, bool& found, int& index) const {
    int attempt = 0;
    while (attempt < TABLE_SIZE) {
        index = linearProbe(key, attempt);

        if (table[index].key == EMPTY || (table[index].key == key && table[index].key != DELETED)) {
            found = (table[index].key == key);
            return;
        }
        attempt++;
    }

    found = false;
}

void HashTable::insert(int key, int data) {
    bool alreadyThere;
    int index;

    findIndex(key, alreadyThere, index);
    if (alreadyThere) {
        table[index].data = data; //update existing record
    } else {
        assert(size() < TABLE_SIZE); //ensure there's room for a new record

        int attempt = 0;
        while (attempt < TABLE_SIZE) {
            index = linearProbe(key, attempt);

            if (table[index].key == EMPTY || table[index].key == DELETED) { //empty or deleted slot
                table[index].key = key;
                table[index]. data = data;
                used++;
                return;
            }
            attempt++;
        }

    }
}

void HashTable::remove(int key) {
    bool found;
    int index;

    findIndex(key, found, index);

    if (!found) {
        cout << "Key not found.\n";
        return;
    }

    table[index].key = DELETED; //mark slot as deleted
    used--;

    cout << "Key " << key << " removed.\n";
}

void HashTable::find(int key, bool& found, int& data) const {
    int index;
    findIndex(key, found, index);

    if (found) {
        data = table[index].data;
    }
}

int HashTable::size() const {
    return used;
}

void HashTable::print() const {
    cout << "The hash table is:\n";
    cout << "Index   Key   Data\n";
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
    cout << "\nThe following choices are available:\n";
    cout << " I   Insert a new record or update an existing record\n";
    cout << " F   Find a record\n";
    cout << " S   Get the number of records\n";
    cout << " R   Remove a record\n";
    cout << " Q   Quit this test program\n\n";
}

int main() {
    HashTable dataTable;
    int key, data;
    bool found;
    char choice;

    do {
        print_menu();
        cout << "Enter choice: ";
        cin >> choice;
        cout << endl;
        choice = toupper(choice);

        switch (choice) {
            case 'I': //insert
                cout << "Enter key (int >= 0) for record: ";
                cin >> key;
                cout << "Enter data (int) for record: ";
                cin >> data;
                dataTable.insert(key, data);
                cout << "Record inserted.\n";
                dataTable.print();
                break;

            case 'F': //find
                cout << "Enter key (int >= 0) to search for: ";
                cin >> key;
                dataTable.find(key, found, data);
                if (found) {
                    cout << "Record found:\n";
                    cout << "   Key  = " << key << "\n";
                    cout << "   Data = " << data << "\n\n";
                } else {
                    cout << "Record with key " << key << " not found.\n\n";
                }
                break;

            case 'S': //size
                cout << "There are " << dataTable.size() << " records in the table.\n";
                cout << "There are " << (TABLE_SIZE - dataTable.size()) << " empty slots left in the table.\n\n";
                break;

            case 'R': //remove
                cout << "Enter key (int >= 0) to remove: ";
                cin >> key;
                dataTable.remove(key);
                dataTable.print();
                break;

            case 'Q': //quit
                cout << "Exiting program.\n";
                break;

            default:
                cout << choice << " is an invalid choice.\n";
        }
    } while (choice != 'Q');

    return 0;
}
