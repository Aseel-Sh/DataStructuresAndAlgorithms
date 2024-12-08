#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

typedef int ItemType;
const int TABLE_SIZE = 31;

struct TableNode {
    int key;
    ItemType data;

    TableNode() : key(-1), data(0) {}
};

class HashTable {
public:
    HashTable();
    void insert(const TableNode& tableNode, char method);
    void remove(int key, char method);
    void find(int key, bool& found, TableNode& result, char method) const;
    int size() const;
    void print() const;

private:
    int hash(int key) const;
    int linearProbe(int key, int attempt) const;
    int quadraticProbe(int key, int attempt) const;
    int midSquareHash(int key, int attempt) const;
    int doubleHash(int key, int attempt) const;
    void findIndex(int key, bool& found, int& index, char method) const;

    TableNode table[TABLE_SIZE];
    int used;
};

HashTable::HashTable() : used(0) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].key = -1;
    }
}

int HashTable::hash(int key) const {
    return key % TABLE_SIZE;
}

int HashTable::linearProbe(int key, int attempt) const {
    return (hash(key) + attempt) % TABLE_SIZE;
}

int HashTable::quadraticProbe(int key, int attempt) const {
    return (hash(key) + attempt * attempt) % TABLE_SIZE;
}

int HashTable::midSquareHash(int key, int attempt) const {
    long squared = static_cast<long>(key) * key;
    int middle = (squared / 100) % 1000;
    return (middle + attempt) % TABLE_SIZE;
}

int HashTable::doubleHash(int key, int attempt) const {
    int hash2 = 1 + (key % (TABLE_SIZE - 1));
    return (hash(key) + attempt * hash2) % TABLE_SIZE;
}

void HashTable::findIndex(int key, bool& found, int& index, char method) const {
    int attempt = 0;
    while (attempt < TABLE_SIZE) {
        switch (method) {
            case 'L':
                index = linearProbe(key, attempt);
                break;
            case 'Q':
                index = quadraticProbe(key, attempt);
                break;
            case 'M':
                index = midSquareHash(key, attempt);
                break;
            case 'D':
                index = doubleHash(key, attempt);
                break;
            default:
                index = linearProbe(key, attempt);
        }

        if (table[index].key == -1 || (table[index].key == key && table[index].key != -999)) {
            found = (table[index].key == key);
            return;
        }
        attempt++;
    }

    found = false;
}

void HashTable::insert(const TableNode& tableNode, char method) {
    bool alreadyThere;
    int index;

    findIndex(tableNode.key, alreadyThere, index, method);
    if (alreadyThere) {
        table[index].data = tableNode.data;
    } else {
        assert(size() < TABLE_SIZE);

        int attempt = 0;
        while (attempt < TABLE_SIZE) {
            switch (method) {
                case 'L':
                    index = linearProbe(tableNode.key, attempt);
                    break;
                case 'Q':
                    index = quadraticProbe(tableNode.key, attempt);
                    break;
                case 'M':
                    index = midSquareHash(tableNode.key, attempt);
                    break;
                case 'D':
                    index = doubleHash(tableNode.key, attempt);
                    break;
                default:
                    index = linearProbe(tableNode.key, attempt);
            }

            if (table[index].key == -1 || table[index].key == -999) {
                table[index] = tableNode;
                used++;
                return;
            }
            attempt++;
        }

        cout << "Unable to insert key: " << tableNode.key << ". Hash table is full.\n";
    }
}

void HashTable::remove(int key, char method) {
    bool found;
    int index;

    findIndex(key, found, index, method);

    if (!found) {
        cout << "Key not found.\n";
        return;
    }

    table[index].key = -999;
    used--;

    cout << "Key " << key << " removed.\n";
}

void HashTable::find(int key, bool& found, TableNode& result, char method) const {
    int index;
    findIndex(key, found, index, method);

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
        if (table[i].key != -1 && table[i].key != -999) {
            cout << setw(8) << table[i].data;
        }
        cout << endl;
    }
    cout << endl;
}

void Menu() {
    cout << "\nThe following choices are available:\n";
    cout << " I   Insert a new record or update an existing record\n";
    cout << " F   Find a record\n";
    cout << " S   Get the number of records\n";
    cout << " R   Remove a record\n";
    cout << " P   Print the hash table\n";
    cout << " M   Select hashing method\n";
    cout << " Q   Quit this test program\n\n";
}

int main() {
    HashTable dataTable;
    TableNode rec;
    int key;
    bool found;
    char choice;
    char method = 'L'; 

    do {
        Menu();
        cout << "Enter choice: ";
        cin >> choice;
        cout << endl;
        choice = toupper(choice);

        switch (choice) {
            case 'I':
                cout << "Enter key (int >= 0) for record: ";
                cin >> rec.key;
                cout << "Enter data (int) for record: ";
                cin >> rec.data;
                dataTable.insert(rec, method);
                cout << "Record inserted.\n";
                dataTable.print();
                break;

            case 'F':
                cout << "Enter key (int >= 0) to search for: ";
                cin >> key;
                dataTable.find(key, found, rec, method);
                if (found) {
                    cout << "Record found:\n";
                    cout << "   Key  = " << rec.key << "\n";
                    cout << "   Data = " << rec.data << "\n\n";
                } else {
                    cout << "Record with key " << key << " not found.\n\n";
                }
                break;

            case 'S':
                cout << "There are " << dataTable.size() << " records in the table.\n";
                cout << "There are " << (TABLE_SIZE - dataTable.size()) << " empty slots left in the table.\n\n";
                break;

            case 'R':
                cout << "Enter key (int >= 0) to remove: ";
                cin >> key;
                dataTable.remove(key, method);
                dataTable.print();
                break;

            case 'P':
                dataTable.print();
                break;

            case 'M':
                cout << "Select hashing method:\n";
                cout << " L - Linear Probing\n";
                cout << " Q - Quadratic Probing\n";
                cout << " M - Mid-Square Hashing\n";
                cout << " D - Double Hashing\n";
                cin >> method;
                method = toupper(method);
                if (method == 'L' || method == 'Q' || method == 'M' || method == 'D') {
                    cout << "Hashing method changed.\n";
                } else {
                    cout << "Invalid selection. Defaulting to Linear Probing.\n";
                    method = 'L';
                }
                break;

            case 'Q':
                cout << "Exiting program.\n";
                break;

            default:
                cout << choice << " is an invalid choice.\n";
        }
    } while (choice != 'Q');

    return 0;
}
