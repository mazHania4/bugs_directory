#include "Field.h"

const string &Field::getIdentifier() const {
    return identifier;
}

DataType Field::getType() const {
    return type;
}

Field::Field(const string &identifier, DataType type) :
identifier(identifier), type(type) {}

Field::~Field() {

}
