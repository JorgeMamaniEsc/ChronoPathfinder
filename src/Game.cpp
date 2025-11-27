#include "Game.h"


Nivel::Nivel(int n)
{
    numero = n;
}

void Nivel::agregarDefensor(int npc){
    defensores.push(npc);
}

void Nivel::agregarAtacante(int npc){
    atacantes.push(npc);
}

void Nivel::agregarNPC(int npc){
    presentes.push(npc);
}

const Vec& Nivel::getDefensores() const {
    return defensores;
}
const Vec& Nivel::getAtacantes() const {
    return atacantes;
}
const Vec& Nivel::getPresentes() const {
    return presentes;
}

Nivel::~Nivel() {}



Mapa::Mapa(int alt,int anc)
{
    ALT=alt;
    ANC=anc;

    grid = new char*[ALT];
    for(int i=0;i<ALT;i++)
        grid[i]=new char[ANC];

    limpiar();
}

void Mapa::limpiar()
{
    for(int i=0;i<ALT;i++)
        for(int j=0;j<ANC;j++)
            grid[i][j] = '.';
}

void Mapa::dibujar() const
{
    cout<<endl<<endl;
    for(int i=0;i<ALT;i++)
    {
        for(int j=0;j<ANC;j++)
            cout << grid[i][j];
        cout <<endl;
    }
}

void Mapa::colocarJugador(int x, int y)
{
    if(x>=0 && x<ALT && y>=0 && y<ANC)
        grid[x][y] = 'J';
}

void Mapa::colocarNPC(int x, int y, char simbolo)
{
    if(x>=0 && x<ALT && y>=0 && y<ANC)
        grid[x][y] = simbolo;
}

void Mapa::colocarPuerta(int x, int y)
{
    if(x>=0 && x<ALT && y>=0 && y<ANC)
        grid[x][y] = '>';
}

bool Mapa::esPuerta(int x, int y) const
{
    if(x>=0 && x<ALT && y>=0 && y<ANC)
        return grid[x][y] == '>';
    return false;
}


int Mapa::getAltura() const {
    return ALT;
}

int Mapa::getAncho() const {
    return ANC;
}

Mapa::~Mapa()
{
    if(grid){
        for(int i=0; i<ALT; i++)
            delete[] grid[i];
        delete[] grid;
    }
}





Juego::Juego(int cantNPC, int cantNiveles): mapa(15,30)
{
    jugador.ini(cantNPC);
    totalNPC = cantNPC;
    totalNiveles = cantNiveles;
    nivelActual=0;
    npcs = new NPC*[totalNPC];
    for(int i=0; i<totalNPC; i++) npcs[i] = nullptr;

    niveles = new Nivel*[totalNiveles];
    for(int i=0;i<totalNiveles;i++) niveles[i] = new Nivel(i);

    inicializarNPCs();
    inicializarNiveles();

    jugador.guardarCheckpoint(nivelActual,cantNPC);
}

void Juego::inicializarNPCs()
{
    npcs[0] = new NPC(0, "Ana", 1,totalNiveles);
    npcs[1] = new NPC(1, "Luis", 0,totalNiveles);
    npcs[2] = new NPC(2, "Carlos", 0,totalNiveles);


    npcs[0]->setNivel(0,5,6);
    npcs[0]->setAparece(0);
    npcs[1]->setNivel(0,10,9);
    npcs[1]->setAparece(0);
    npcs[0]->setNivel(1,6,6);
    npcs[0]->setAparece(1);
    npcs[2]->setNivel(1,13,6);
    npcs[2]->setAparece(1);
}

void Juego::inicializarNiveles()
{
    niveles[1]->agregarDefensor(0);
    niveles[0]->agregarNPC(0);
    niveles[0]->agregarNPC(1);
    niveles[1]->agregarNPC(0);
    niveles[1]->agregarNPC(2);
}



void Juego::mostrarMapaNivel(int n)
{
    mapa.limpiar();

    mapa.colocarJugador(jugador.getX(), jugador.getY());

    colocarNPCsDelNivel(nivelActual);
    mapa.dibujar();
}

void Juego::colocarNPCsDelNivel(int n)
{
    const Vec& p = niveles[n]->getPresentes();
    for(int i = 0; i < p.size(); i++)
    {
        int id=p[i];
        int x=npcs[id]->getPosX(n),y=npcs[id]->getPosY(n);
        mapa.colocarNPC(x,y,'N');
    }
}

bool Juego::isCan(){
    int n=jugador.getLvl();
    for(int i=n;i<totalNiveles;i++){
        const Vec& p= niveles[i]->getDefensores();
        for(int j=0;j<p.size();i++) if(jugador.esEnemigo(p[j])) return false;
    }
    return true;
}

void Juego::juegar(){
    nivelActual=0;
    while(nivelActual<totalNiveles) jugarNivel(nivelActual);
}

void Juego::guardarCheckpoint()
{
    if(!isCan()){
        cout<<endl<<"Imposible, paradoja detectada"<<endl;
        return;
    }
    jugador.setPh(jugador.getPh() - 1);
    jugador.guardarCheckpoint(nivelActual,totalNPC);
    cout << "Checkpoint guardado.\n";
}

void Juego::jugarNivel(int n)
{
    const Vec& defenders = niveles[n]->getDefensores();
    for (int i = 0; i < defenders.size(); i++){
        int npc = defenders[i];
        if (!jugador.esAmigo(npc)){
            cout<<endl<<"..."<<endl;
            nivelActual = jugador.cargarCheckpoint(totalNPC);
            return;
        }
    }
    jugador.setPos(0, 0);
    cout << "Nivel " << n << " habilitado.\n";
    cout << "Explora el mapa y encuentra la puerta.\n\n";

    moverJugador();

    cout << "\nHas completado el nivel " << n << "!\n";

    nivelActual++;

    if(nivelActual < totalNiveles)
    {
        cout << "Presiona ENTER para continuar al siguiente nivel...";
        cin.ignore();
        cin.get();
        return;
    }
    else
    {
        cout << "\n¡Felicidades! Terminaste todos los niveles.\n";
        ScoreDB db("scores.txt");
        cout<<"pas1"<<endl;
        int p=jugador.getPh();

        db.guardarScore(p);
        cout<<"pas2"<<endl;
        db.mostrarRanking();
        return;
    }
}
int Juego::npcEn(int x, int y){

    for(int i=0;i<totalNPC;i++){
        if(npcs[i]->aparece(nivelActual)){
            if((npcs[i]->getPosX(nivelActual)==x)&&(npcs[i]->getPosY(nivelActual)==y)) return i;
        }
    }
    return -1;
}

void Juego::moverJugador()
{
    while (true)
    {
        mapa.limpiar();
        mapa.colocarJugador(jugador.getX(), jugador.getY());
        colocarNPCsDelNivel(nivelActual);
        mapa.colocarPuerta(mapa.getAltura() - 1, mapa.getAncho() - 1);

        mapa.dibujar();
        cout<<endl<<"NIVEL ACTUAL: "<<nivelActual<<endl;
        cout <<endl<<"PH ACTUAL:  "<<jugador.getPh()<<endl<<endl<< "Mover (w/a/s/d, p = pausa): ";
        char op;
        cin >> op;

        if(op == 'p')
        {
            MenuPausa pausa;
            pausa.mostrar();
            int po = pausa.leerOpcion();

            if(po == 1) continue;
            if(po == 2) guardarCheckpoint();
            if(po == 3) return;
            if(po == 4) exit(0);
        }

        int nx = jugador.getX();
        int ny = jugador.getY();

        if(op=='w') nx--;
        else if(op=='s') nx++;
        else if(op=='a') ny--;
        else if(op=='d') ny++;

        if(nx < 0 || nx >= mapa.getAltura() || ny < 0 || ny >= mapa.getAncho())
        {
            cout << "No puedes salir del mapa.\n\n";
            continue;
        }

        if(mapa.esPuerta(nx, ny))
        {
            jugador.setPos(nx, ny);
            cout << "\nHas encontrado la puerta del nivel!\n\n";
            return;
        }
        int npcID = npcEn(nx, ny);
        if(npcID != -1){
            cout << "\nHay un NPC aqui. Interactuar? (y/n): ";
            char c; cin >> c;

            if(c == 'y' || c == 'Y'){
                interactuarConNPC(npcID);
                continue;
            }else{
                cout << "Lo ignoras.\n";
                continue;
            }
}
        jugador.setPos(nx, ny);
    }
}

void Juego::interactuarConNPC(int id)
{
    NPC* npc = npcs[id];
    string nombre = npc->getNombre();

    cout << "\n=================================\n";
    cout << " Te encuentras con: " << nombre << "\n";
    cout << "=================================\n";

    if(jugador.esAmigo(id))
    {
        cout << npc->getNombre() << ": ¡Broooo que tal! :D\n";
        return;
    }

    if(jugador.esEnemigo(id) || npc->getRelacionNatural() == -1)
    {
        cout << npc->getNombre() << ": No quiero hablar contigo.\n";
        return;
    }

    int costo = 2;
    cout << npc->getNombre() << ": No te conozco, pero pareces buena persona.\n";
    cout << "¿Quieres hacerte amigo? (costo: " << costo << " PH)\n";
    cout << "1) Si\n2) No\n> ";

    int op; cin >> op;

    if(op == 1)
    {
        if(jugador.getPh() >= costo)
        {
            jugador.setPh(jugador.getPh() - costo);
            jugador.hacerAmigo(id);
            cout << "Ahora " << npc->getNombre() << " es tu amigo!\n";
        }
        else cout << "No tienes PH suficiente.\n";
    }
}

Juego::~Juego()
{

    for(int i=0;i<totalNiveles;i++) delete niveles[i];

    delete[] niveles;

    for(int i=0;i<totalNPC;i++) delete npcs[i];
    delete[] npcs;

}


ScoreDB::ScoreDB(const string& path) {
    archivo = path;
}

void ScoreDB::guardarScore(int puntos){
    ofstream out(archivo.c_str(), ios::app);

    if(!out){
        cout << "ERROR: No se pudo abrir archivo de puntajes.\n";
        return;
    }

    out << puntos << endl;
    out.close();
}

void ScoreDB::mostrarRanking(){
    ifstream in(archivo.c_str());

    if(!in){
        cout << "\nNo hay puntajes registrados.\n";
        return;
    }
    int puntos;

     int rank[100];
    int len=0;
    while(in >> puntos){
        rank[len]=puntos;
        len++;
    }
    in.close();

    if(len == 0){
        cout << "\nNo hay puntajes registrados.\n";
        return;
    }

    cout << "\n===== RANKING =====\n";
    for(int i=0;i<len;i++) cout<<rank[i]<<endl;
    cout << "===================\n";

}

ScoreDB::~ScoreDB(){
    //hot radaaaa
}
