#include "HashTable.h"
#include <cmath>
#include <iostream>

using namespace std;

template<typename K, typename V>
HashTable<K, V>::HashTable() {
    size = 5;
    elements = 0;
    table = new Pair<K, V>[size];
}

template<typename K, typename V>
int HashTable<K, V>::hashFunction(K key) { //Multiplication method
    int st_hash = hash<K>()(key) % 10000000;
    double R = 0.6180339887;
    double decimals = st_hash*R - floor(st_hash*R);
    return static_cast<int>(decimals * size);
}


template<typename K, typename V>
void HashTable<K, V>::insert(K newKey, V newValue)  noexcept(false){
    if (hasKey(newKey)) throw invalid_argument("(!)Repeated key");
    if (newKey == K()) throw invalid_argument("(!)Empty key");
    if ((double)elements/size > 0.6) rehash(); //rehash if more than 60% is used
    int index = hashFunction(newKey);
    while (table[index].getKey() != K()) { //in case of collision, rehash until solved
        cout<<"\n#collision";
        rehash();
        index = hashFunction(newKey);
    }
    table[index].setKey(newKey);
    table[index].setValue(newValue);
    elements++;
}

template<typename K, typename V>
void HashTable<K, V>::rehash() {
    cout<<"\n#rehashing";
    int oldSize = size;
    size = int(size*1.4);
    Pair<K, V>* oldTable = table;
    table = new Pair<K, V>[size]();
    for (int i = 0; i < oldSize; ++i) {
        if (oldTable[i].getKey() != K())
            insert(oldTable[i].getKey(), oldTable[i].getValue());
    }
}

template<typename K, typename V>
V HashTable<K, V>::get(K key) noexcept(false) {
    for (int i = 0; i < size; ++i) {
        if (table[i].getKey() == key) return table[i].getValue();
    }
    throw invalid_argument("(!)Key not found");
}

template<typename K, typename V>
bool HashTable<K, V>::hasKey(K key) {
    int index = hashFunction(key);
    return (table[index].getKey() != K()) && (table[index].getKey() == key);
}


template<typename K, typename V>
void HashTable<K, V>::print() {
    cout<<"\nsize:"<<size<<" elements:"<<elements<<endl;
    for (int i = 0; i < size; ++i) {
        cout<<"{k:"<<table[i].getKey()<<" v:"<<table[i].getValue()<<"}";
    }
}
