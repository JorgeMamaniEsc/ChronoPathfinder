#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H
#include<iostream>
using namespace std;
#define endl '\n'
class Pair
{
    public:
        Pair();
        Pair(int f,int s);
        int first,second;
        virtual ~Pair();
        bool operator < (const Pair &o) const;
        bool operator == (const Pair &o) const;
        bool operator > (const Pair &o) const;
};
ostream& operator<<(ostream& os, const Pair& p);

class Vec{
    private:
        int *data;
        int cap;
        int len;
    public:
        Vec();
        Vec(int n);
        ~Vec();

        void push(int x);
        int size() const;
        int operator[](int i)const;
        int& operator[](int i);
        void clear();
        void reserve(int n);
        void resize(int n);
        void printElements();
};

#endif // DATASTRUCTURES_H
