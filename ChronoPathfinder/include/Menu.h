#ifndef MENU_H
#define MENU_H
#include<iostream>
#define endl '\n'
using namespace std;

class MenuPrincipal
{
    public:
        MenuPrincipal();

        void mostrar() const;
        int leerOpcion() const;

        ~MenuPrincipal();
};


class MenuPausa
{
    public:
        MenuPausa();

        void mostrar() const;
        int leerOpcion() const;

        ~MenuPausa();
};

#endif // MENU_H
