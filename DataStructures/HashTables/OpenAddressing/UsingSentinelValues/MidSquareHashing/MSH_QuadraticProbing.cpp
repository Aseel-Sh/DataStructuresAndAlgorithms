#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

typedef int ItemType; 
const int TABLE_SIZE = 31; 

struct TableNode {
    int key;         
    ItemType data;   

    TableNode() : key(-1), data(0) {} //-1 means empty
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
    int midSquareHash(int key, int attempt) const;
    void findIndex(int key, bool& found, int& index) const;

    TableNode table[TABLE_SIZE]; 
    int used;
};

HashTable::HashTable() {
    used = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].key = -1; //init all slots to empty
    }
}

//midsquare hashing with quadratic probing
int HashTable::midSquareHash(int key, int attempt) const {
    long squared = static_cast<long>(key) * key; //square the key
    int middle = (squared / 100) % 1000; //take middle digits
    return (middle + attempt * attempt) % TABLE_SIZE; //quadratic probing
}

void HashTable::findIndex(int key, bool& found, int& index) const {
    int attempt = 0;
    while (attempt < TABLE_SIZE) {
        index = midSquareHash(key, attempt); //get hashed index

        if (table[index].key == -1 || (table[index].key == key && table[index].key != -999)) {
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
        assert(size() < TABLE_SIZE); //table should not be full

        int attempt = 0;
        while (attempt < TABLE_SIZE) {
            index = midSquareHash(entry.key, attempt); //find next slot

            if (table[index].key == -1 || table[index].key == -999) { //empty or deleted slot
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

    table[index].key = -999; //mark slot as deleted
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
        if (table[i].key != -1 && table[i].key != -999) {
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
