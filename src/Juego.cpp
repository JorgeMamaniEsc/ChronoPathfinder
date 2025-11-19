#include "Juego.h"
#include <iostream>
using namespace std;

Juego::Juego()
{
    //ctor
}

Juego::~Juego()
{
    //dtor
}

NodoBase::NodoBase(int id) : id(id), paradoja() {}

int NodoBase::getId() {
}

bool NodoBase::esParadoja() {

}

void NodoBase::setParadoja(bool p) {
}

NodoBase::~NodoBase() {}

NodoLista::NodoLista(int id) {
}

void ListaNodos::agregar(int id) {
}

void ListaNodos::mostrar() {
}

bool ListaNodos::contiene(int id) {

}

bool ListaNodos::vacia() {

}

void ListaNodos::eliminar(int id) {
}


LineaTemporal::LineaTemporal(int id, int estado, int padre) : NodoBase(id){
}
void LineaTemporal::agregarHijo(int idHijo) {
}

bool LineaTemporal::verificarParadoja() {

}

int LineaTemporal::getEstado() {
   return estado;
}

int LineaTemporal::getPadre() {
   return padre;
}

void LineaTemporal::mostrarInfo() {
    cout << "------Linea Temporal------" << endl;
    cout << "ID: " << id << endl;
    cout << "Estado: " << estado << endl;
    cout << "Padre: " << padre << endl;
    cout << "Es Checkpoint: " << (_esCheckpoint ? "Si" : "No") << endl;
    cout << "Tiene Paradoja: " << (paradoja ? "Si" : "No") << endl;
    cout << "Hijos: ";
    if (hijos->vacia()) {
        cout << "Ninguno" << endl;
    } else {
        hijos->mostrar();
    }
    cout << "-------------------" << endl;
}


void LineaTemporal::setCheckpoint(bool) {
}

bool LineaTemporal::esCheckpoint() {

}


void GrafoTemporal::agregarLinea(int estado, int padre) {
}

LineaTemporal* GrafoTemporal::buscarLinea(int id) {

}

void GrafoTemporal::conectar(int origen, int destino) {
}

void GrafoTemporal::dfs(int inicio) {
}

void GrafoTemporal::mostrarGrafo() {
}

void GrafoTemporal::generarParadoja(int id) {
}

void GrafoTemporal::propagarParadoja(int id) {
}

int GrafoTemporal::getCheckpointCercano(int id) {

}


NodoHistorial::NodoHistorial(int id) {
}


void PilaHistorial::push(int id) {
}

void PilaHistorial::push(int id, bool checkpoint) {
}

int PilaHistorial::pop() {

}

int PilaHistorial::cima() {

}

bool PilaHistorial::vacia() {

}

void PilaHistorial::mostrar() {
}

int PilaHistorial::volverCheckpoint() {

}



void Jugador::setDatos(const char* n, int p, int t) {
int i = 0;
    while (n[i] != '\0' && i < 19) {
        nombre[i] = n[i];
        i++;
    }
    nombre[i] = '\0';

    puntaje = p;
    tiempo = t;
}

void Jugador::mostrar() {
 cout << "nombre" << nombre << endl;
 cout << "puntaje" << puntaje << endl;
 cout << "tiempo" << tiempo << endl;
}

int Jugador::getPuntaje() {
    return puntaje;
}

const char* Jugador::getNombre() {
    return nombre;
}

BaseDeDatosPuntaje::BaseDeDatosPuntaje()
{
    total = 0;
}
void BaseDeDatosPuntaje::agregar(const Jugador& j)
{
    if (total < MAX){
        jugadores[total] = j;
        total++;
    }
}

void BaseDeDatosPuntaje::guardarArchivo() {
}

void BaseDeDatosPuntaje::cargarArchivo() {
}

void BaseDeDatosPuntaje::mostrarRanking()
{
    cout << "------RANKING-----"<<endl;
    for (int i = 0; i<total; i++){
        cout << i+1 <<". ";
        jugadores[i].mostrar();
    }
}


int BaseDeDatosPuntaje::mejorPuntaje()
{
    if (total==0){
        return 0;
    }
    else{
        int mejor = jugadores[0].getPuntaje();
        for (int i= 1; i<total;i++){
            if (jugadores[i].getPuntaje()>mejor){
                mejor = jugadores[i].getPuntaje();
            }
        }
        return mejor;
    }
}


void JuegoPrincipal::iniciar(){}

void JuegoPrincipal::menu() {}

void JuegoPrincipal::procesarDecision() {}

void JuegoPrincipal::mostrarEstadoActual() {}

bool JuegoPrincipal::verificarFin() {}

void JuegoPrincipal::guardarPuntaje() {}
