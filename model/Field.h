#ifndef BUGS_DIRECTORY_FIELD_H
#define BUGS_DIRECTORY_FIELD_H
#include <string>

enum Type { INTEGER, STRING, CHAR, DATE };
using namespace std;
class Field {
private:
    string identifier;
    Type type;
public:
    Field(const string &identifier, Type type);
    const string &getIdentifier() const;
    Type getType() const;
    virtual ~Field();
};


#endif