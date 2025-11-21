#include "Trees.h"

Node::Node(int k){
    key=k;
    red=true;
    left=nullptr;
    right=nullptr;
    parent=nullptr;
}

int Node::getKey(){
    return key;
}

bool Node::isRed(){
    return red;
}

Node* Node::getLeft(){
    return left;
}

Node* Node::getRight(){
    return right;
}

Node* Node::getParent(){
    return parent;
}

void Node::setKey(int k){
    key=k;
}

void Node::setRed(bool rd){
    red=rd;
}

void Node::setLeft(Node* l){
    left=l;
    if(l) l->parent=this;
}

void Node::setRight(Node* r){
    right=r;
    if(r) r->parent=this;
}

void Node::setParent(Node* p){
    parent=p;
}

bool Node::isBlack(){
    return !red;
}

void Node::makeRed(){
    red=true;
}

void Node::makeBlack(){
    red=false;
}


Node::~Node() {
    //su jijijaja
}


