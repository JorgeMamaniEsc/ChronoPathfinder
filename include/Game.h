#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include "DataStructures.h"
#include "Personaje.h"
#include "Menu.h"
#define endl '\n'
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
        Vec npcEnPos;


    public:
        Juego(int cantNPC, int cantNiveles);

        void inicializarNPCs();
        void inicializarNiveles();
        void colocarNPCsDelNivel(int n);
        void moverJugador();
        void mostrarMapaNivel(int n);
        int npcEn(int x, int y);
        void interactuarConNPC(int id);
        void guardarCheckpoint();
        void jugarNivel(int n);
        bool isCan();
        void juegar();
        ~Juego();
};

class ScoreDB {
private:
    string archivo;

public:
    ScoreDB(const string& path);
    void guardarScore(int puntos);
    void mostrarRanking();
    ~ScoreDB();
};

#endif // GAME_H
