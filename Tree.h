#ifndef BUGS_DIRECTORY_TREE_H
#define BUGS_DIRECTORY_TREE_H
#include <iostream>
#include "List.h"

using namespace std;

template <typename T>
struct Node {
    Node<T> *left, *right, *sup;
    int bf, hl, hr, id;
    T value;
    List<string> *list;
};

template <typename T>
class Tree {
private:
    Node<T> *root;
    int nodes;
    int calcHeightsAndBf(Node<T> *);
    void rotateRR(Node<T> *);
    void rotateLL(Node<T> *);
    void rotateLR(Node<T> *);
    void rotateRL(Node<T> *);
    void balance(Node<T> *);
    void insertNode(Node<T> *, Node<T>*);
    void search(Node<T> *, T, List<List<string>*>*);
public:
    List<List<string>*>* get(T);
    Tree();
    void insert(T, List<string>*);
    std::string dotGraphOfNode(Node<T>*, string);
    Node<T> * getRoot();
};


template<typename T>
void Tree<T>::insertNode(Node<T> * newNode, Node<T> *tmp) {
    if (root == nullptr){ //add first node
        root=newNode;
        root->sup= nullptr;
    }else{
        if(hash<T>()(newNode->value) < hash<T>()(tmp->value)){
            if(tmp->left != nullptr){
                insertNode(newNode, tmp->left);
            }else{
                tmp->left=newNode;
                newNode->sup=tmp;
            }
        }else{ // newValue > tmpValue
            if (tmp->right != nullptr){
                insertNode( newNode, tmp->right);
            }else{
                tmp->right=newNode;
                newNode->sup=tmp;
                return;
            }
        }
    }
}


template<typename T>
void Tree<T>::insert(T newValue, List<string> *newList) {
    nodes++;
    auto *newNode = new Node<T>();
    newNode->value = newValue;
    newNode->list = newList;
    newNode->id = nodes;
    insertNode(newNode, root);
    balance(root);
}



template<typename T>
void Tree<T>::search(Node<T> *node, T value, List<List<string>*> *listL) {
    if (node != nullptr){
        if(hash<T>()(value) < hash<T>()(node->value)){
            search(node->left, value, listL);
        }else if (hash<T>()(value) > hash<T>()(node->value)){
            search(node->right, value, listL);
        }else{ // (==)
            listL->add(node->list);
            search(node->left, value, listL);
            search(node->right, value, listL);
        }
    }
}

template<typename T>
List<List<string> *>* Tree<T>::get(T value) {
    auto *listL = new List<List<string>*>();
    search(root, value, listL);
    return listL;
}

template<typename T>
void Tree<T>::balance(Node<T> *node) {
    if (node != nullptr) {
        balance(node->left);
        balance(node->right);
        calcHeightsAndBf(root);
        if ((node->bf==2)||(node->bf==-2)){
            Node<T> *next = node->right;
            if ((node->bf>1)&&(next->bf>0)){
                rotateLL(node);
            }else if((node->bf>1)&&(next->bf<0)){
                rotateRL(node);
            }else{
                next=node->left;
                if((node->bf<-1)&&(next->bf<0)){
                    rotateRR(node);
                }else if((node->bf<-1)&&(next->bf>0)){
                    rotateLR(node);
                }
            }
        }
    }
}

template<typename T>
void Tree<T>::rotateRL(Node<T> *node) {
    Node<T> *next = node->right;
    Node<T> *nextNext = next->left;
    if (node == root){
        root = nextNext;
        nextNext->sup = nullptr;
    }else{
        Node<T> *prev = node->sup;
        prev->right = nextNext;
        nextNext->sup = prev;
    }
    nextNext->left = node;
    nextNext->right = next;
    next->left = nullptr;
    next->sup = nextNext;
    node->sup = nextNext;
    node->right = nullptr;
}

template<typename T>
void Tree<T>::rotateLR(Node<T> *node) {
    Node<T> *next = node->left;
    Node<T> *nextNext = next->right;
    if (node == root) {
        root = nextNext;
        nextNext->sup = nullptr;
    } else {
        Node<T> *prev = node->sup;
        prev->left = nextNext;
        nextNext->sup = prev;
    }
    nextNext->left = next;
    nextNext->right = node;
    next->right = nullptr;
    next->sup = nextNext;
    node->sup = nextNext;
    node->left = nullptr;
}

template<typename T>
void Tree<T>::rotateLL(Node<T> *node) {
    Node<T> *next = node->right;
    if (node == root){
        root = next;
        next->sup = nullptr;
    }else{
        Node<T> *prev = node->sup;
        prev->right = node->right;
        next->sup = prev;
    }
    if (next->left != nullptr){
        node->right = next->left;
        next->left->sup = node;
    } else{
        node->right = nullptr;
    }
    next->left = node;
    node->sup = next;
}

template<typename T>
void Tree<T>::rotateRR(Node<T> *node) {
    Node<T> *next = node->left;
    if (node == root){
        root = next;
        next->sup = nullptr;
    }else{
        Node<T> *prev = node->sup;
        prev->left = next;
        next->sup = prev;
    }
    if (next->right != nullptr){
        node->left = next->right;
        next->right->sup = node;
    } else{
        node->left = nullptr;
    }
    node->sup = next;
    next->right = node;
}


template<typename T>
int Tree<T>::calcHeightsAndBf(Node<T> *node) { //returns the overall height of the node
    if (node == nullptr) return 0 ;
    else {
        node->hl = calcHeightsAndBf(node->left);
        node->hr = calcHeightsAndBf(node->right);
        node->bf = node->hr - node->hl;
        if (node->hl > node->hr) return node->hl + 1;
        else return node->hr + 1;
    }
}

template<typename T>
string Tree<T>::dotGraphOfNode(Node<T> *node, string id) {
    string ans;
    if (node != nullptr) {
        string val = node->value;
        ans = "\n    "+id+"_n" + to_string(node->id) + " ;"+"\n    "+id+"_n"+ to_string(node->id) +" [label=\"" + val +"\"] ;";
        if (node->left != nullptr){
            ans.append("\n    "+id+"_n"+  to_string(node->id) + " -> "+id+"_n" + to_string(node->left->id) + " ;");
            ans.append(dotGraphOfNode(node->left, id));
        }
        if (node->right != nullptr){
            ans.append("\n    "+id+"_n"+  to_string(node->id) + " -> "+id+"_n" + to_string(node->right->id) + " ;");
            ans.append(dotGraphOfNode(node->right, id));
        }
    }
    return ans;
}

template<typename T>
Tree<T>::Tree() {
    root = nullptr;
    nodes = 0;
}

template<typename T>
Node<T> * Tree<T>::getRoot() {
    return root;
}

#endif
