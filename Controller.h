#ifndef BUGS_DIRECTORY_CONTROLLER_H
#define BUGS_DIRECTORY_CONTROLLER_H
#include <iostream>
#include "model/Field.h"
#include "List.h"
#include "hash_table/HashTable.h"
#include "Tree.h"
#include "FileManager.cpp"

using namespace std;

class Controller {
private:
    HashTable<string, HashTable<string,Tree<string>*>* > *groups;
    FileManager *files;
    static DataType getType(const string& s);
    List<Field*>* getFields(string);
    static List<string>* getData(string);
public:
    Controller();
    void analyze(const string&);
    void printStatus();
    void drawCompleteGraph();
};


#endif
