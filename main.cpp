#include <iostream>
#include "hash_table/HashTable.h"
#include "hash_table/HashTable.cpp"
#include <stdexcept>

using namespace std;

int main() {
    auto *hashTable = new HashTable<string , string>();
    try {
        hashTable->insert("19", "val1key1");
        hashTable->insert("1", "val1ngcsyub");
        hashTable->insert("145", "val3");
        hashTable->insert("46", "val4");
        hashTable->insert("4", "val5");
        hashTable->insert("14752", "val6");
        hashTable->insert("782752", "val notas");
        hashTable->insert("14", "val apellido");
        hashTable->insert("141", "val fecha");
        cout<<"\nget: "<<hashTable->get("147");
    } catch (invalid_argument e) {
        cout<<e.what()<<"---"<<endl;
    }
    cout<<"Bye!";
    return 0;
}
