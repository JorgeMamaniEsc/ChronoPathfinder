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

NPC::NPC(int i,const string &nom,int relacion,int niveles):Personajes(i,nom){
    relacionNatural=relacion;
    apareceEnNivel = new bool[niveles];
    for(int i=0;i<niveles;i++) apareceEnNivel[i]=false;
    posNivel =  new Pair[niveles];
    dialogolvl = new string[niveles];
    for(int i=0;i < niveles;i++) dialogolvl[i]="EN MANTENIMIENTO...";
}

string NPC::getDialogo(int nivel){
    return dialogolvl[nivel];
}

void NPC::setDialogo(string dialogo,int nivel){
    dialogolvl[nivel]=dialogo;
}

void NPC::setAparece(int nivel){
    apareceEnNivel[nivel]=true;
}
int NPC::getPosX(int nivel){
    return posNivel[nivel].first;
}

int NPC::getPosY(int nivel){
    return posNivel[nivel].second;
}

bool NPC::aparece(int nivel) const{
    return apareceEnNivel[nivel];
}

int NPC::getRelacionNatural() const{
    return relacionNatural;
}

void NPC::setNivel(int nivel,int x,int y){
    posNivel[nivel].first=x;
    posNivel[nivel].second=y;
}


NPC::~NPC(){
    delete[] apareceEnNivel;
    delete[] posNivel;
}

Jugador::Jugador():Personajes(-1,"Jugador"){
    ph=30;
    phCheckpoint=ph;
    lvlCheckpoint = 0;
}

void Jugador::ini(int n){
    estadoRelacion = new int[n];
    estadoRelacionCheckPoint = new int[n];
    for(int i=0;i<n;i++){
        estadoRelacion[i]=0;
        estadoRelacionCheckPoint[i]=0;
    }
}



void Jugador::setPh(int v){
    ph=v;
}

int Jugador::getPh(){
    return ph;
}

void Jugador::hacerAmigo(int npc){
    estadoRelacion[npc]=1;
}

void Jugador::hacerEnemigo(int npc){
    estadoRelacion[npc]=-1;
}

void Jugador::ignorar(int npc){
    estadoRelacion[npc]=0;
}


bool Jugador::esAmigo(int npc){
    return (estadoRelacion[npc]==1?true:false);
}

bool Jugador::esEnemigo(int npc) {
    return (estadoRelacion[npc]==-1?true:false);;
}

void Jugador::guardarCheckpoint(int nivel,int t){
    phCheckpoint=ph;
    lvlCheckpoint = nivel;
    for(int i=0;i<t;i++) estadoRelacionCheckPoint[i] = estadoRelacion[i];
}

int Jugador::getLvl(){
    return lvlCheckpoint;
}

int Jugador::cargarCheckpoint(int t){
    ph=phCheckpoint;
    for(int i=0;i<t;i++) estadoRelacion[i] = estadoRelacionCheckPoint[i];
    return lvlCheckpoint;
}

void Jugador::mover(int dx, int dy)
{
    x += dx;
    y += dy;
}


Jugador::~Jugador(){
    delete[] estadoRelacion;
    delete[] estadoRelacionCheckPoint;
    estadoRelacion = nullptr;
    estadoRelacionCheckPoint = nullptr;
}
