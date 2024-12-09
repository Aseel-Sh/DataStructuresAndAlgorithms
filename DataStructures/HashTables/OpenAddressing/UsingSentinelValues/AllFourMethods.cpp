
//Normal Hash
    // int HashTable::hash(int key) const {
    //     return key % TABLE_SIZE;
    // }

//midsquare hashing
    // int HashTable::midSquareHash(int key, int attempt) const {
    //     long squared = static_cast<long>(key) * key;
    //     int middle = (squared / 100) % 1000;
    //     return (middle + attempt) % TABLE_SIZE;
    // }

//open addressing linearprobe
    // int HashTable::linearProbe(int key, int attempt) const {
    //     return (hash(key) + attempt) % TABLE_SIZE;
    // }

//open addressing quadraticProbe
    // int HashTable::quadraticProbe(int key, int attempt) const {
    //     return (hash(key) + attempt * attempt) % TABLE_SIZE;
    // }

//open addressing doubleHash
    // int HashTable::doubleHash(int key, int attempt) const {
    //     int hash2 = 1 + (key % (TABLE_SIZE - 1));
    //     return (hash(key) + attempt * hash2) % TABLE_SIZE;
    // }

//closed addressing chaining
    //using linkedlists



