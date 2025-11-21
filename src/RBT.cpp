#include "RBT.h"

RBT::RBT(){
    root = nullptr;
}

Node* RBT::bstInsert(int key){
    Node* y= nullptr;
    Node* x = root;
    Node* z = new Node(key);

    while(x!=nullptr){
        y=x;
        if(key < x->getKey()){
            x = x->getLeft();
        }else {
            x = x->getRight();
        }
    }

    z->setParent(y);

    if(y==nullptr){
        root=z;
    }else if(key<y->getKey()){
        y->setLeft(z);
    }else{
        y->setRight(z);
    }

    return z;
}

RBT::~RBT()
{
    //jij jaja
}
