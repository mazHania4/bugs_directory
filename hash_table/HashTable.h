#ifndef BUGS_DIRECTORY_HASHTABLE_H
#define BUGS_DIRECTORY_HASHTABLE_H

#include "Pair.h"
#include "Pair.cpp"
#include "../List.h"
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

template <typename K, typename V>
class HashTable {
private:
    int size;
    List<K> *keys;
    Pair<K, V> *table;
    bool hasKey(K);
    void rehash();
    int hashFunction(K);
    void insertP(K, V) noexcept(false);
public:
    HashTable();
    void insert(K, V) noexcept(false);
    V get(K) noexcept(false);
    string dotGraph(const string&);
    List<Pair<int, V>*>* getValues(); //for graphs
    void print();
    List<K> * getKeys();
};

template<typename K, typename V>
List<K> *HashTable<K, V>::getKeys() {
    return keys;
}

template<typename K, typename V>
HashTable<K, V>::HashTable() {
    size = 5;
    table = new Pair<K, V>[size];
    keys = new List<K>();
}

template<typename K, typename V>
int HashTable<K, V>::hashFunction(K key) { //Multiplication method
    int st_hash = hash<K>()(key) % 10000000;
    double R = 0.6180339887;
    double decimals = st_hash*R - floor(st_hash*R);
    return static_cast<int>(decimals * size);
}

template<typename K, typename V>
void HashTable<K, V>::insert(K newKey, V newValue) noexcept(false) {
    insertP(newKey, newValue);
    keys->add(newKey);
}


template<typename K, typename V>
void HashTable<K, V>::insertP(K newKey, V newValue)  noexcept(false){
    if (hasKey(newKey)) throw invalid_argument("(!)Repeated key");
    if (newKey == K()) throw invalid_argument("(!)Empty key");
    if ((double)(keys->getSize()+1)/size > 0.6) rehash(); //rehash if more than 60% is used
    int index = hashFunction(newKey);
    while (table[index].getKey() != K()) { //in case of collision, rehash until solved
        rehash();
        index = hashFunction(newKey);
    }
    table[index].setKey(newKey);
    table[index].setValue(newValue);
}

template<typename K, typename V>
void HashTable<K, V>::rehash() {
    int oldSize = size;
    size = int(size*1.4);
    Pair<K, V>* oldTable = table;
    table = new Pair<K, V>[size]();
    for (int i = 0; i < oldSize; ++i) {
        if (oldTable[i].getKey() != K()){
            insertP(oldTable[i].getKey(), oldTable[i].getValue());
        }
    }
}

template<typename K, typename V>
V HashTable<K, V>::get(K key) noexcept(false) {
    int index = hashFunction(key);
    if (index<size && table[index].getValue() != V()) return table[index].getValue();
    throw invalid_argument("(!)Key not found");
}

template<typename K, typename V>
bool HashTable<K, V>::hasKey(K key) {
    int index = hashFunction(key);
    return (table[index].getKey() != K()) && (table[index].getKey() == key);
}


template<typename K, typename V>
void HashTable<K, V>::print() {
    cout<<"\nsize:"<<size<<" elements:"<<keys->getSize()<<endl;
    for (int i = 0; i < size; ++i) {
        cout<<"{k:"<<table[i].getKey()<<" v:"<<table[i].getValue()<<"}";
    }
    cout<<endl<<"Keys:";
    for (int i = 0; i < keys->getSize(); i++) {
        cout<<"{k:"<<keys->get(i)<<"}";
    }
}


template<typename K, typename V>
string HashTable<K, V>::dotGraph(const string& id) {
    string ans = "\n   pair"+id+" [\n"
                 "    label = \"";
    for (int i = 0; i < size; ++i) {
        ans.append(" <c" +  to_string(i) + "> ");
        if (table[i].getKey() != K()){
            stringstream ss;
            ss << table[i].getValue();
            ans.append(table[i].getKey() + ":" + ss.str() + " ");
        }
        if (i != size-1) ans.append("|");
    }
    ans.append("\"\n    shape = \"record\"\n   ];\n"
               "   key"+id+" [\n"
               "    label = \"");
    for (int i = 0; i < keys->getSize(); i++) {
        ans.append(" <c" +  to_string(i) + "> " + keys->get(i)+" ");
        if (i != keys->getSize()-1) ans.append("|");
    }
    ans.append("\"\n    shape = \"record\"\n   ];");
    for (int i = 0; i < keys->getSize(); i++) {
        ans.append("\n    key"+id+":c"+ to_string(i));
        ans.append(" -> pair"+id+":c"+ to_string(hashFunction(keys->get(i))));
    }
    return ans;
}

template<typename K, typename V>
List<Pair<int, V>*>* HashTable<K, V>::getValues() {
    auto *list = new List<Pair<int, V>*>();
    for (int i = 0; i < keys->getSize(); i++) {
        int index = hashFunction(keys->get(i));
        list->add(new Pair<int, V>(index, table[index].getValue()));
    }
    return list;
}


#endif
