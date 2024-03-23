#ifndef BUGS_DIRECTORY_PAIR_H
#define BUGS_DIRECTORY_PAIR_H

template <typename K, typename V>
class Pair {
private:
    K key;
    V value;
public:
    Pair(K, V);
    Pair() : key(K()), value(V()) {}
    K getKey();
    V getValue();
    void setValue(V);
    void setKey(K);
};


#endif
