#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <iostream>
#include "RBT.h"
using namespace std;
#define endl '\n'

class Personajes
{
    public:
        Personajes(int i,const string &nom);
        int getId() const;
        string getNombre() const;
        void setPos(int nx, int ny);
        int getX() const;
        int getY() const;

        virtual ~Personajes();

    protected:
        int id;
        string nombre;
        int x,y;

};

class NPC:public Personajes
{
    private:
        int relacionNatural;
        bool apareceEnNivel[30];
    public:
        NPC(int i,const string &nom,int relacion);
        void setAparece(int nivel,bool v);
        bool aparece(int nivel) const;
        int getRelacionNatural() const;
        ~NPC();
};

class Jugador:public Personajes
{
    private:
        int ph;
        RBT<int> amigos;
        RBT<int> enemigos;
        RBT<int> ignorados;
        int phCheckpoint;
        RBT<int> amigosCheckpoint;
        RBT<int> enemigosCheckpoint;
        RBT<int> ignoradosCheckpoint;
    public:
        Jugador();

        void setPh(int v);
        int getPh() const;
        void hacerAmigo(int npc);
        void hacerEnemigo(int npc);
        void ignorar(int npc);

        bool esAmigo(int npc);
        bool esEnemigo(int npc);
        void mover(int dx, int dy);
        void guardarCheckpoint();
        void cargarCheckpoint();

        ~Jugador();
};

#endif // PERSONAJE_H
