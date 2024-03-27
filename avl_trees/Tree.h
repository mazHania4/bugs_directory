#ifndef BUGS_DIRECTORY_TREE_H
#define BUGS_DIRECTORY_TREE_H
#include <iostream>
#include "../Lists/List.h"
#include "../Lists/List.cpp"

template <typename T, typename L>
struct Node {
    Node<T, L> *left, *right, *sup;
    int bf, hl, hr, id;
    T value;
    List<L> *list;
};

template <typename T, typename L>
class Tree {
private:
    Node<T, L> *root;
    int nodes;
    int calcHeightsAndBf(Node<T, L> *);
    void rotateRR(Node<T, L> *);
    void rotateLL(Node<T, L> *);
    void rotateLR(Node<T, L> *);
    void rotateRL(Node<T, L> *);
    void balance(Node<T, L> *);
    void insertNode(Node<T, L> *, Node<T, L>*);
    void search(Node<T, L> *, T, List<List<L>*>*);
public:
    List<List<L>*>* get(T);
    Tree();
    void insert(T, List<L>*);
    std::string dotGraphOfNode(Node<T, L>*);
    Node<T, L> * getRoot();
};

#endif
