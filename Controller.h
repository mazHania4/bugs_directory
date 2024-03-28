#ifndef BUGS_DIRECTORY_CONTROLLER_H
#define BUGS_DIRECTORY_CONTROLLER_H
#include <iostream>
#include "model/Field.h"
#include "List.h"
#include "hash_table/HashTable.h"
#include "Tree.h"

using namespace std;

class Controller {
private:
    HashTable<string, HashTable<string,Tree<string>*>* > *groups;
    static Type getType(const string& s);
    static List<Field*>* getFields(string);
public:
    Controller();
    void analyze(const string&);
    void drawCompleteGraph();
};


#endif
