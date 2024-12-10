#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

//try 10, 41, 72,

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
    void insert(const TableNode& entry);
    void remove(int key);
    void find(int key, bool& found, TableNode& result) const;
    int size() const;
    void print() const;

private:
    int hash(int key) const;
    int hash2(int key) const;
    int doubleHash(int key, int attempt) const;
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

int HashTable::hash2(int key) const {
    return 1 + (key % (TABLE_SIZE - 1));
}

int HashTable::doubleHash(int key, int attempt) const {
    return (hash(key) + attempt * hash2(key)) % TABLE_SIZE;
}

void HashTable::findIndex(int key, bool& found, int& index) const {
    int attempt = 0;
    while (attempt < TABLE_SIZE) {
        index = doubleHash(key, attempt);

        if (table[index].key == EMPTY || (table[index].key == key && table[index].key != DELETED)) {
            found = (table[index].key == key);
            return;
        }
        attempt++;
    }

    found = false;
}

void HashTable::insert(const TableNode& entry) {
    bool alreadyThere;
    int index;

    findIndex(entry.key, alreadyThere, index);
    if (alreadyThere) {
        table[index].data = entry.data;
    } else {
        assert(size() < TABLE_SIZE);

        int attempt = 0;
        while (attempt < TABLE_SIZE) {
            index = doubleHash(entry.key, attempt);

            if (table[index].key == EMPTY || table[index].key == DELETED) {
                table[index] = entry;
                used++;
                return;
            }
            attempt++;
        }

        cout << "Unable to insert key: " << entry.key << ". Hash table is full.\n";
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

    table[index].key = DELETED;
    used--;

    cout << "Key " << key << " removed.\n";
}

void HashTable::find(int key, bool& found, TableNode& result) const {
    int index;
    findIndex(key, found, index);

    if (found) {
        result = table[index];
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
    TableNode rec;
    int key;
    bool found;
    char choice;

    do {
        print_menu();
        cout << "Enter choice: ";
        cin >> choice;
        cout << endl;
        choice = toupper(choice);

        switch (choice) {
            case 'I': // insert
                cout << "Enter key (int >= 0) for record: ";
                cin >> rec.key;
                cout << "Enter data (int) for record: ";
                cin >> rec.data;
                dataTable.insert(rec);
                cout << "Record inserted.\n";
                dataTable.print();
                break;

            case 'F': // find
                cout << "Enter key (int >= 0) to search for: ";
                cin >> key;
                dataTable.find(key, found, rec);
                if (found) {
                    cout << "Record found:\n";
                    cout << "   Key  = " << rec.key << "\n";
                    cout << "   Data = " << rec.data << "\n\n";
                } else {
                    cout << "Record with key " << key << " not found.\n\n";
                }
                break;

            case 'S': // size
                cout << "There are " << dataTable.size() << " records in the table.\n";
                cout << "There are " << (TABLE_SIZE - dataTable.size()) << " empty slots left in the table.\n\n";
                break;

            case 'R': // remove
                cout << "Enter key (int >= 0) to remove: ";
                cin >> key;
                dataTable.remove(key);
                dataTable.print();
                break;

            case 'Q': // quit
                cout << "Exiting program.\n";
                break;

            default:
                cout << choice << " is an invalid choice.\n";
        }
    } while (choice != 'Q');

    return 0;
}
