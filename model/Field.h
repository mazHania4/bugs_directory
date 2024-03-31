#ifndef BUGS_DIRECTORY_FIELD_H
#define BUGS_DIRECTORY_FIELD_H
#include <string>

enum DataType { INTEGER, STRING, CHAR, DATE };
using namespace std;
class Field {
private:
    string identifier;
    DataType type;
public:
    Field(const string &identifier, DataType type);
    const string &getIdentifier() const;
    DataType getType() const;
    virtual ~Field();
};


#endif