#include "RBT.h"

template <typename T>
RBT<T>::RBT() {
    root = nullptr;
}

template <typename T>
Node<T>* RBT<T>::bstInsert(T key) {
    Node<T>* y = nullptr;
    Node<T>* x = root;
    Node<T>* z = new Node<T>(key);

    while (x != nullptr) {
        y = x;
        if (key < x->getKey())
            x = x->getLeft();
        else
            x = x->getRight();
    }

    z->setParent(y);

    if (y == nullptr) {
        root = z;
    } else if (key < y->getKey()) {
        y->setLeft(z);
    } else {
        y->setRight(z);
    }

    return z;
}

template <typename T>
void RBT<T>::rotateLeft(Node<T>* x) {
    Node<T>* y = x->getRight();
    if (!y) return;

    x->setRight(y->getLeft());
    if (y->getLeft())
        y->getLeft()->setParent(x);

    y->setParent(x->getParent());
    if (!x->getParent()) {
        root = y;
    } else if (x == x->getParent()->getLeft()) {
        x->getParent()->setLeft(y);
    } else {
        x->getParent()->setRight(y);
    }

    y->setLeft(x);
    x->setParent(y);
}

template <typename T>
void RBT<T>::rotateRight(Node<T>* x) {
    Node<T>* y = x->getLeft();
    if (!y) return;

    x->setLeft(y->getRight());
    if (y->getRight())
        y->getRight()->setParent(x);

    y->setParent(x->getParent());
    if (!x->getParent()) {
        root = y;
    } else if (x == x->getParent()->getRight()) {
        x->getParent()->setRight(y);
    } else {
        x->getParent()->setLeft(y);
    }

    y->setRight(x);
    x->setParent(y);
}

template <typename T>
void RBT<T>::fixInsert(Node<T>* z) {
    while (z != root && z->getParent()->isRed()) {
        Node<T>* parent = z->getParent();
        Node<T>* gparent = parent->getParent();

        if (parent == gparent->getLeft()) {
            Node<T>* uncle = gparent->getRight();
            if (uncle && uncle->isRed()) {
                parent->makeBlack();
                uncle->makeBlack();
                gparent->makeRed();
                z = gparent;
            } else {
                if (z == parent->getRight()) {
                    z = parent;
                    rotateLeft(z);
                }
                parent->makeBlack();
                gparent->makeRed();
                rotateRight(gparent);
            }
        } else {
            Node<T>* uncle = gparent->getLeft();
            if (uncle && uncle->isRed()) {
                parent->makeBlack();
                uncle->makeBlack();
                gparent->makeRed();
                z = gparent;
            } else {
                if (z == parent->getLeft()) {
                    z = parent;
                    rotateRight(z);
                }
                parent->makeBlack();
                gparent->makeRed();
                rotateLeft(gparent);
            }
        }
    }
    root->makeBlack();
}

template <typename T>
void RBT<T>::insert(T key) {
    Node<T>* z = bstInsert(key);
    fixInsert(z);
}

template <typename T>
bool RBT<T>::find(T key) {
    Node<T>* cur = root;
    while (cur) {
        if (key == cur->getKey()) return true;
        cur = (key < cur->getKey()) ? cur->getLeft() : cur->getRight();
    }
    return false;
}

template <typename T>
void RBT<T>::inorder(Node<T>* x) {
    if (!x) return;
    inorder(x->getLeft());
    cout << x->getKey() <<endl;
    inorder(x->getRight());
}

template <typename T>
void RBT<T>::printInOrder() {
    inorder(root);
    cout << "\n";
}

template <typename T>
void RBT<T>::clearRec(Node<T>* x) {
    if (!x) return;
    clearRec(x->getLeft());
    clearRec(x->getRight());
    delete x;
}

template <typename T>
void RBT<T>::clear() {
    clearRec(root);
    root = nullptr;
}

template <typename T>
RBT<T>::~RBT() {
    clear();
}
