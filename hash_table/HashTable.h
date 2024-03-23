#ifndef BUGS_DIRECTORY_HASHTABLE_H
#define BUGS_DIRECTORY_HASHTABLE_H

#include "Pair.h"
#include "Pair.cpp"

template <typename K, typename V>
class HashTable {
private:
    int size;
    int elements;
    Pair<K, V> *table;
    int hashFunction(K);
    bool hasKey(K);
    void rehash();
public:
    HashTable();
    void insert(K, V) noexcept(false);
    V get(K) noexcept(false);
    void print();

};

#endif
