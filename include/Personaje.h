#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <iostream>
#include "DataStructures.h"
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
        bool* apareceEnNivel;
        Pair* posNivel;
        string* dialogolvl;
    public:
        NPC(int i,const string &nom,int relacion,int niveles);
        string getDialogo(int nivel);
        void setDialogo(string dialogo,int nivel);
        void setAparece(int nivel);
        bool aparece(int nivel) const;
        int getRelacionNatural() const;
        void setNivel(int nivel,int x,int y);
        int getPosX(int nivel);
        int getPosY(int nivel);
        ~NPC();
};

class Jugador:public Personajes
{
    private:
        int ph;
        int lvlCheckpoint;
        int* estadoRelacion;
        int* estadoRelacionCheckPoint;
        int phCheckpoint;
    public:
        Jugador();
        void setPh(int v);
        int getPh();
        void hacerAmigo(int npc);
        void hacerEnemigo(int npc);
        void ignorar(int npc);
        void ini(int n);
        bool esAmigo(int npc);
        bool esEnemigo(int npc);
        void mover(int dx, int dy);
        void guardarCheckpoint(int nivel,int t);
        int cargarCheckpoint(int t);
        int getLvl();
        ~Jugador();
};

#endif // PERSONAJE_H
