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

}

int LineaTemporal::getPadre() {

}

void LineaTemporal::mostrarInfo() {
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

}

void Jugador::mostrar() {
     cout << "nombre" << nombre << endl;
 cout <<  "puntaje" << puntaje << endl;
 cout << "tiempo" << tiempo << endl;
}

int Jugador::getPuntaje() {
    return puntaje;
}

const char* Jugador::getNombre() {
    return nombre;
}

void BaseDeDatosPuntaje::agregar(const Jugador& j) {
}

void BaseDeDatosPuntaje::guardarArchivo() {
}

void BaseDeDatosPuntaje::cargarArchivo() {
}

void BaseDeDatosPuntaje::mostrarRanking() {
}

int BaseDeDatosPuntaje::mejorPuntaje() {}


void JuegoPrincipal::iniciar(){}

void JuegoPrincipal::menu() {}

void JuegoPrincipal::procesarDecision() {}

void JuegoPrincipal::mostrarEstadoActual() {}

bool JuegoPrincipal::verificarFin() {}

void JuegoPrincipal::guardarPuntaje() {}
