#ifndef RBT_H
#define RBT_H

#include "Trees.h"

template <typename T>
class RBT {
private:
    Node<T>* root;
    Node<T>* bstInsert(T key);
    void rotateLeft(Node<T>* x);
    void rotateRight(Node<T>* x);
    void fixInsert(Node<T>* z);
    void inorder(Node<T>* x);
    void clearRec(Node<T>* x);
public:
    RBT();
    void insert(T key);
    bool find(T key);
    void printInOrder();
    void clear();
    ~RBT();
};

#include "RBT.tpp"

#endif
