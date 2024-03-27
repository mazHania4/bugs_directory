#include "List.h"

template<typename T>
void List<T>::add(T val) {
    E<T> *n = new E<T>();
    n->data = val;
    n->next = head;
    head = n;
    size++;
}

template<typename T>
T List<T>::get(int i) {
    E<T> tmp = head;
    for (int j = 0; j < i; ++j) {
        tmp = tmp->next;
    }
    return tmp->value;
}

template<typename T>
bool List<T>::contains(T val) {
    E<T> *tmp = head;
    while(tmp->next) {
        if(tmp->data == val) return true;
        else tmp = tmp->next;
    }
    delete tmp;
    return false;
}

template<typename T>
List<T>::List() {
    head = nullptr;
    size = 0;
}


template<typename T>
int List<T>::getSize() {
    return size;
}