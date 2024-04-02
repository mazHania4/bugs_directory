#ifndef BUGS_DIRECTORY_CONTROLLER_H
#define BUGS_DIRECTORY_CONTROLLER_H
#include <iostream>
#include "model/Field.h"
#include "List.cpp"
#include "hash_table/HashTable.cpp"
#include "Tree.cpp"
#include "FileManager.cpp"

using namespace std;

class Controller {
private:
    HashTable<string, HashTable<string,Tree<string>*>* > *groups;
    FileManager *files;
    List<string> *log;
    static DataType getType(const string& s);
    List<Field*>* getFields(string);
    static List<string>* getData(string);
    void drawCompleteGraph();
    void drawCompleteGraph(string);
    void drawGraph(string);
public:
    Controller();
    void analyze(const string&);
    void printStatus();
    virtual ~Controller() = default;
};


#endif
