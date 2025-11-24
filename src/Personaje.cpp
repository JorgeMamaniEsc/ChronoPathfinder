#include "Personaje.h"

Personajes::Personajes(int i,const string &nom)
{
    id=i;
    nombre=nom;
    x=0;
    y=0;
}

int Personajes::getId()const{
    return id;
}

string Personajes::getNombre()const {
    return nombre;
}

void Personajes::setPos(int nx, int ny){
    x = nx;
    y = ny;
}

int Personajes::getX() const {
    return x;
}
int Personajes::getY() const {
    return y;
}

Personajes::~Personajes()
{
    //dtor
}

NPC::NPC(int i,const string &nom,int relacion):Personajes(id,nom){
    relacionNatural=relacion;
    for(int i=0;i<30;i++) apareceEnNivel[i]=false;
}

void NPC::setAparece(int nivel,bool v){
    apareceEnNivel[nivel]=true;
}

bool NPC::aparece(int nivel) const{
    return apareceEnNivel[nivel];
}

int NPC::getRelacionNatural() const{
    return relacionNatural;
}

NPC::~NPC(){
    //dtr;
}

Jugador::Jugador():Personajes(-1,"Jugador"){
    ph=10;
    phCheckpoint=ph;
    amigos.clear();
    enemigos.clear();
    ignorados.clear();
    lvlCheckpoint = 0;
}

void Jugador::setPh(int v){
    ph=v;
}

int Jugador::getPh() const{
    return ph;
}

void Jugador::hacerAmigo(int npc){
    amigos.insert(npc);
}

void Jugador::hacerEnemigo(int npc){
    enemigos.insert(npc);
}

void Jugador::ignorar(int npc){
    ignorados.insert(npc);
}

bool Jugador::esAmigo(int npc){
    return amigos.find(npc);
}

bool Jugador::esEnemigo(int npc) {
    return enemigos.find(npc);
}

void Jugador::guardarCheckpoint(int nivel){
    phCheckpoint=ph;
    amigosCheckpoint = amigos;
    enemigosCheckpoint = enemigos;
    ignoradosCheckpoint = ignorados;
    lvlCheckpoint = nivel;
}

int Jugador::cargarCheckpoint(){
    ph=phCheckpoint;
    amigos = amigosCheckpoint;
    enemigos = enemigosCheckpoint;
    ignorados = ignoradosCheckpoint;
    return lvlCheckpoint;
}

void Jugador::mover(int dx, int dy)
{
    x += dx;
    y += dy;
}


Jugador::~Jugador(){
    //ddd
}
