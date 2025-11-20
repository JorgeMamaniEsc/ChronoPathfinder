#ifndef JUEGO_H
#define JUEGO_H
#include <iostream>

class Juego
{
    public:
        Juego();
        virtual ~Juego();

    protected:

    private:
};

const int MAX = 100;

class NodoBase {
protected:
    int id;
    bool paradoja;
public:
    NodoBase(int id = 0);
    int getId();
    bool esParadoja();
    void setParadoja(bool);
    virtual void mostrarInfo() = 0;
    virtual ~NodoBase();
};

class NodoLista {
private:
    int id;
    NodoLista* sig;
public:
    NodoLista(int id);
    friend class ListaNodos;
};


class ListaNodos {
private:
    NodoLista* inicio;
public:
    void agregar(int id);
    void mostrar();
    bool contiene(int id);
    bool vacia();
    void eliminar(int id);
};


class LineaTemporal : public NodoBase {
private:
    int estado;
    int padre;
    ListaNodos* hijos;
    bool _esCheckpoint;
public:
    LineaTemporal(int id, int estado, int padre);
    void agregarHijo(int idHijo);
    bool verificarParadoja();
    int getEstado();
    int getPadre();
    void mostrarInfo();
    void setCheckpoint(bool);
    bool esCheckpoint();
};


class GrafoTemporal {
private:
    LineaTemporal lineas[MAX];
    int totalLineas;
public:
    void agregarLinea(int estado, int padre);
    LineaTemporal* buscarLinea(int id);
    void conectar(int origen, int destino);
    void dfs(int inicio);
    void mostrarGrafo();
    void generarParadoja(int id);
    void propagarParadoja(int id);
    int getCheckpointCercano(int id);
};


class NodoHistorial {
private:
    int idLinea;
    NodoHistorial* ant;
    bool esCheckpoint;
public:
    NodoHistorial(int id);
    friend class PilaHistorial;
};


class PilaHistorial {
private:
    NodoHistorial* tope;
public:
    void push(int id);
    void push(int id, bool checkpoint);
    int pop();
    int cima();
    bool vacia();
    void mostrar();
    int volverCheckpoint();
};

class Jugador {
private:
    char nombre[20];
    int puntaje;
    int tiempo;
public:
    void setDatos(const char* n, int p, int t);
    void mostrar();
    int getPuntaje();
    const char* getNombre();
};


class BaseDeDatosPuntaje {
private:
    Jugador jugadores[MAX];
    int total;
public:
    BaseDeDatosPuntaje();
    void agregar(const Jugador& j);
    void guardarArchivo();
    void cargarArchivo();
    void mostrarRanking();
    int mejorPuntaje();
};


class JuegoPrincipal {
private:
    GrafoTemporal grafo;
    PilaHistorial pila;
    BaseDeDatosPuntaje db;
    Jugador jugador;
    int lineaActual;
    bool fin;
public:
    //JuegoPrincipal();
    void iniciar();
    void menu();
    void procesarDecision();
    void mostrarEstadoActual();
    bool verificarFin();
    void guardarPuntaje();
};

#endif // JUEGO_H
