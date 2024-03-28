#include "Field.h"

const string &Field::getIdentifier() const {
    return identifier;
}

Type Field::getType() const {
    return type;
}

Field::Field(const string &identifier, Type type) :
identifier(identifier), type(type) {}

Field::~Field() {

}
