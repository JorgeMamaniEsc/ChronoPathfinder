#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "DataStructures.h"
#include "TwoSAT.h"
#include "Personaje.h"
#include "Menu.h"
using namespace std;

class Nivel
{
    private:
        int numero;
        Vec defensores;
        Vec atacantes;
        Vec presentes;

    public:
        Nivel(int n);

        void agregarDefensor(int npc);
        void agregarAtacante(int npc);
        void agregarNPC(int npc);

        const Vec& getDefensores() const;
        const Vec& getAtacantes() const;
        const Vec& getPresentes() const;

        virtual ~Nivel();
};

class Mapa
{
    private:
        int ALT;
        int ANC;
        char** grid;

    public:
        Mapa(int alt,int anc);

        void limpiar();
        void dibujar() const;
        void colocarJugador(int x, int y);
        void colocarNPC(int x, int y, char simbolo);
        void colocarPuerta(int x, int y);
        bool esPuerta(int x, int y) const;
        int getAltura() const;
        int getAncho() const;

        ~Mapa();
};

class Juego
{
    private:
        Jugador jugador;
        NPC** npcs;
        Nivel** niveles;
        int nivelActual;
        int totalNPC;
        int totalNiveles;

        Mapa mapa;

        TwoSAT construirTwoSATActual();

    public:
        Juego(int cantNPC, int cantNiveles);

        void inicializarNPCs();
        void inicializarNiveles();

        void moverJugador();
        void mostrarMapaNivel(int n);

        void guardarCheckpoint();
        void jugarNivel(int n);

        ~Juego();
};

#endif // GAME_H
