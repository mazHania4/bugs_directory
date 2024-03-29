#include <iostream>
#include "hash_table/HashTable.h"
#include "Tree.h"
#include "Controller.h"
#include <stdexcept>

using namespace std;
 void testTable(){
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
 }

 void testTree() {
     auto *avlTree = new Tree<string>();
     auto *list = new List<string> ();
     list->add("h");
     list->add("i");
     avlTree->insert("3", list);
     avlTree->insert("2", list);
     avlTree->insert("1", list);
     avlTree->insert("6", list);
     avlTree->insert("8", list);
     avlTree->insert("12", list);
     avlTree->insert("7", list);
     avlTree->insert("34", list);
     avlTree->insert("21", list);
     avlTree->insert("36", list);
     avlTree->insert("21", list);
     avlTree->insert("21", list);
     List<List<string>*> *lists = avlTree->get("21");
     cout<<"\nFound: "<<lists->getSize();
 }

int main() {
    Controller *controller = new Controller();
    controller->analyze("ADD NEW-GROUP clientes FIELDS (nombre1 STRING, apellido STRING, celular INTEGER);");
    controller->analyze("ADD NEW-GROUP amigos FIELDS (nombre STRING, apellido STRING, celular INTEGER, nacimiento DATE);");
    controller->analyze("ADD CONTACT IN clientes FIELDS (Lucia, Lopez, 96413287);");
    controller->analyze("ADD CONTACT IN amigos FIELDS (Pedro, Alvarez, 12345678, 02-05-1998);");
    controller->analyze("ADD CONTACT IN amigos FIELDS (Pedro, Perez, 85256545, 04-09-1989);");
    controller->analyze("ADD CONTACT IN amigos FIELDS (Marta, Martinez, 41526378, 28-12-1995);");
    controller->analyze("ADD CONTACT IN amigos FIELDS (Juan, Juarez, 78963214, 14-08-20024);");
    controller->analyze("FIND CONTACT IN amigos CONTACT-FIELD nombre=ASD");
    controller->drawCompleteGraph();
    cout<<"\n\nBye!";
    return 0;
}
