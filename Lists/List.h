#ifndef BUGS_DIRECTORY_LIST_H
#define BUGS_DIRECTORY_LIST_H

template <typename T>
struct E {
    T data;
    E *next;
};

template <typename T> class List{
private:
    E<T> *head;
    int size;
public:
    List();
    void add(T val);
    T get(int);
    bool contains(T val);
    int getSize();
};

#endif