#include <iostream>
#include <fstream>
#include "Menu.h"
#include "DataStructures.h"
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

    while(true)
    {
        menu.mostrar();
        int op = menu.leerOpcion();

        if(op == 1){
            cout << "\nIniciando juego...\n\n";
            Juego game(3, 2);
            game.juegar();
        }else if(op == 2){
            ScoreDB db("scores.txt");
            db.mostrarRanking();
        }else if(op == 3){
            cout << "Saliendo del juego...\n";
            break;
        }else{
            cout << "Opción inválida.\n";
        }
    }
    cout<<"owo"<<endl;
    return 0;
}
