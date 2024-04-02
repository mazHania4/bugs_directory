#ifndef BUGS_DIRECTORY_LIST_CPP
#define BUGS_DIRECTORY_LIST_CPP

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
    virtual ~List() = default;
};


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
    E<T> *tmp = head;
    for (int j = 0; j < i; ++j) {
        tmp = tmp->next;
    }
    return tmp->data;
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

#endif