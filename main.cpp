#include <iostream>
#include <fstream>
#include "RBT.h"
#include "Menu.h"
#include "DataStructures.h"
#include "TwoSAT.h"
#include "Personaje.h"
#include "Game.h"
#define f(i,a,b,c) for(int i=a;i<b;i+=c)
#define rf(i,a,b,c) for(int i=a;i>=b;i-=c)
#define endl '\n'

using namespace std;

void cleanScreen() {
    for(int i=0;i<50;i++) cout<<'\n';
    //system("cls");
}



int main()
{
    MenuPrincipal menu;
    Juego game(3, 2);
    while(true)
    {
        menu.mostrar();
        int op = menu.leerOpcion();

        if(op == 1){
            cout << "\nIniciando juego...\n\n";
            game.jugarNivel(0);
        }else if(op == 2){
            cout << "\nPuntajes aún no implementados.\n";
        }else if(op == 3){
            cout << "Saliendo del juego...\n";
            break;
        }else{
            cout << "Opción inválida.\n";
        }
    }
    return 0;
}
