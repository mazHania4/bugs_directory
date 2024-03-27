#include "Tree.h"
#include <string>

using namespace std;

template<typename T, typename L>
void Tree<T, L>::insertNode(Node<T, L> * newNode, Node<T, L> *tmp) {
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


template<typename T, typename L>
void Tree<T, L>::insert(T newValue, List<L> *newList) {
    nodes++;
    auto *newNode = new Node<int, string>();
    newNode->value = newValue;
    newNode->list = newList;
    newNode->id = nodes;
    insertNode(newNode, root);
    balance(root);
    cout << "\n\n\ntree: " << dotGraphOfNode(getRoot());
}



template<typename T, typename L>
void Tree<T, L>::search(Node<T, L> *node, T value, List<List<L>*> *listL) {
    cout<<" !  ";
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

template<typename T, typename L>
List<List<L> *>* Tree<T, L>::get(T value) {
    auto *listL = new List<List<L>*>();
    search(root, value, listL);
    return listL;
}

template<typename T, typename L>
void Tree<T, L>::balance(Node<T, L> *node) {
    if (node != nullptr) {
        balance(node->left);
        balance(node->right);
        calcHeightsAndBf(root);
        if ((node->bf==2)||(node->bf==-2)){
            Node<T, L> *next = node->right;
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

template<typename T, typename L>
void Tree<T, L>::rotateRL(Node<T, L> *node) {
        Node<T, L> *next = node->right;
        Node<T, L> *nextNext = next->left;
    if (node == root){
        root = nextNext;
        nextNext->sup = nullptr;
    }else{
        Node<T, L> *prev = node->sup;
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

template<typename T, typename L>
void Tree<T, L>::rotateLR(Node<T, L> *node) {
    cout<<"rotate node: "<<node->value;
    Node<T, L> *next = node->left;
    Node<T, L> *nextNext = next->right;
    if (node == root) {
        root = nextNext;
        nextNext->sup = nullptr;
    } else {
        Node<T, L> *prev = node->sup;
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

template<typename T, typename L>
void Tree<T, L>::rotateLL(Node<T, L> *node) {
    cout<<"rotate LL"<<node->value;
    Node<T, L> *next = node->right;
    if (node == root){
        root = next;
        next->sup = nullptr;
    }else{
        Node<T, L> *prev = node->sup;
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

template<typename T, typename L>
void Tree<T, L>::rotateRR(Node<T, L> *node) {
    cout<<"rotate RR"<<node->value;
    Node<T, L> *next = node->left;
    if (node == root){
        root = next;
        next->sup = nullptr;
    }else{
        Node<T, L> *prev = node->sup;
        prev->left = next;
        next->sup = prev;
    }
    if (next->right != nullptr){
        cout<<"pooow";
        node->left = next->right;
        next->right->sup = node;
    } else{
        node->left = nullptr;
    }
    node->sup = next;
    next->right = node;
}


template<typename T, typename L>
int Tree<T, L>::calcHeightsAndBf(Node<T, L> *node) { //returns the overall height of the node
    if (node == nullptr) return 0 ;
    else {
        node->hl = calcHeightsAndBf(node->left);
        node->hr = calcHeightsAndBf(node->right);
        node->bf = node->hr - node->hl;
        if (node->hl > node->hr) return node->hl + 1;
        else return node->hr + 1;
    }
}

template<typename T, typename L>
string Tree<T, L>::dotGraphOfNode(Node<T, L> *node) {
    string ans;
    if (node != nullptr) {
        ans = "\nn" + to_string(node->id) + " ;"+"\nn"+ to_string(node->id) +" [label=\""+ to_string(node->value) +"\"] ;";
        if (node->left != nullptr){
            ans.append("\nn"+  to_string(node->id) + " -- n" + to_string(node->left->id) + " ;");
            ans.append(dotGraphOfNode(node->left));
        }
        if (node->right != nullptr){
            ans.append("\nn"+  to_string(node->id) + " -- n" + to_string(node->right->id) + " ;");
            ans.append(dotGraphOfNode(node->right));
        }
    }
    return ans;
}

template<typename T, typename L>
Tree<T, L>::Tree() {
    root = nullptr;
    nodes = 0;
}

template<typename T, typename L>
Node<T, L> * Tree<T, L>::getRoot() {
    return root;
}

