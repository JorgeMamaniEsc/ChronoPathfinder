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
    totalNPC = cantNPC;
    totalNiveles = cantNiveles;
    nivelActual=0;
    npcs = new NPC*[totalNPC];
    for(int i=0; i<totalNPC; i++) npcs[i] = nullptr;


    niveles = new Nivel*[totalNiveles];
    for(int i=0;i<totalNiveles;i++)
        niveles[i] = new Nivel(i);

    inicializarNPCs();
    inicializarNiveles();
    npcEnPos.resize(mapa.getAltura() * mapa.getAncho());

    jugador.guardarCheckpoint(nivelActual);
}

void Juego::inicializarNPCs()
{
    npcs[0] = new NPC(0, "Ana", 1);
    npcs[1] = new NPC(1, "Luis", 0);
    npcs[2] = new NPC(2, "Carlos", 2);

}

void Juego::inicializarNiveles()
{
    niveles[1]->agregarDefensor(0);
    niveles[0]->agregarNPC(0);
    niveles[0]->agregarNPC(1);
    niveles[1]->agregarNPC(0);
    niveles[1]->agregarNPC(1);
    niveles[1]->agregarNPC(2);
}


TwoSAT Juego::construirTwoSATActual()
{
    TwoSAT ts(totalNPC * 2);

    for(int i=0; i<totalNPC; i++)
    {
        int F = 2*i;
        int E = F + 1;

        ts.addOr( ts.var(F, false), ts.var(E, false) );


        int rel = npcs[i]->getRelacionNatural();

        if(rel == 1)
        {
            ts.setTrue(ts.var(F, true));
            ts.setTrue(ts.var(E, false));
        }

        if(rel == 2)
        {
            ts.setTrue(ts.var(E, true));
            ts.setTrue(ts.var(F, false));
        }

        if(jugador.esAmigo(i)){
            ts.setTrue(ts.var(F, true));
            ts.setTrue(ts.var(E, false));
        }

        if(jugador.esEnemigo(i)){
            ts.setTrue(ts.var(E, true));
            ts.setTrue(ts.var(F, false));
        }

    }

    return ts;
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
    posKeys.clear();
    const Vec& p = niveles[n]->getPresentes();
    for(int i = 0; i < p.size(); i++)
    {
        int id=p[i];
        int xx=3+2*i;
        int yy=10+2*i;
        mapa.colocarNPC(xx,yy,'N');
        int key = xx * mapa.getAncho() + yy;
        posKeys.insert(key);
        npcEnPos[key] = id;
    }
}


void Juego::guardarCheckpoint()
{
    TwoSAT ts = construirTwoSATActual();

    if(!ts.solve())
    {
        cout << "No puedes guardar: contradicción futura.\n";
        return;
    }

    jugador.setPh(jugador.getPh() - 1);
    jugador.guardarCheckpoint(nivelActual);
    cout << "Checkpoint guardado.\n";
}

void Juego::jugarNivel(int n)
{
    TwoSAT ts = construirTwoSATActual();

    const Vec& defenders = niveles[n]->getDefensores();
    for (int i = 0; i < defenders.size(); i++){
        int npc = defenders[i];
        if (!jugador.esAmigo(npc)){
            nivelActual = jugador.cargarCheckpoint();
            jugarNivel(nivelActual);
        }

        int F = 2*npc;
        int E = F + 1;
        ts.setTrue( ts.var(F, true) );
        ts.setTrue( ts.var(E, false) );
    }

    jugador.setPos(0, 0);
    if(!ts.solve())
    {
        nivelActual = jugador.cargarCheckpoint();
        jugarNivel(nivelActual);
    }

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
        jugarNivel(nivelActual);
    }
    else
    {
        cout << "\n¡Felicidades! Terminaste todos los niveles.\n";
    }
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

int Juego::npcEn(int x, int y){
    int key=x*mapa.getAncho()+y;
    if(!posKeys.find(key))    return -1;

    return npcEnPos[key];
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
        cout << npc->getNombre() << ": ¡Broooo qué tal! :D\n";
        return;
    }

    if(jugador.esEnemigo(id) || npc->getRelacionNatural() == 2)
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
