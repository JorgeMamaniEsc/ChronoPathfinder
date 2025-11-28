#include "DataStructures.h"

Pair::Pair(int f,int s)
{
    first=f;
    second=s;

}
Pair::Pair()
{
    first=0;
    second=0;

}

bool Pair::operator < (const Pair &o) const{
    if(first==o.first)return second>o.second;
    return first>o.first;
}
bool Pair::operator > (const Pair &o) const{
    return o<*this;
}
bool Pair::operator == (const Pair &o) const{
    return second==o.second && first==o.first;
}

ostream& operator<<(ostream& os, const Pair& p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

Pair::~Pair()
{
    //dtor
}




Vec::Vec(){
    cap=4;
    len=0;
    data = new int[cap];
}


Vec::Vec(int n) {
    cap=n;
    len=n;
    data=new int[cap];
    for(int i = 0; i < n; i++) data[i]=0;
}

int Vec::size() const{
    return len;
}

int Vec::operator[](int i)const{
    return data[i];
}

void Vec::push(int x){
    if(len==cap){
        int *nd=new int[cap*2];
        for(int i=0;i<len;i++) nd[i]=data[i];
        delete[] data;
        data=nd;
        cap*=2;
    }
    data[len]=x;
    len++;
}



void Vec::resize(int n)
{
    if (n > cap) reserve(n);
    len = n;
}
void Vec::reserve(int n)
{
    if (n <= cap) return;

    int *nd = new int[n];

    for (int i = 0; i < len; i++) nd[i] = data[i];
    delete[] data;
    data = nd;
    cap = n;
}

int& Vec::operator[](int i){
    return data[i];
}

void Vec::clear(){
    len=0;
}

void Vec::printElements(){
    cout<<endl<<"[ ";
    for(int i=0;i<len;i++) cout<<data[i]<<" ";
    cout<<"]"<<endl;
}

Vec::~Vec(){
    delete[] data;
}

