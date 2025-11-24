#include "Game.h"

//
// ----------- NIVEL -----------
//
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

const Vec& Nivel::getDefensores() const { return defensores; }
const Vec& Nivel::getAtacantes() const { return atacantes; }
const Vec& Nivel::getPresentes() const { return presentes; }

Nivel::~Nivel() {}


//
// ----------- MAPA -----------
//

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
}

void Juego::inicializarNPCs()
{
    npcs[0] = new NPC(0, "Ana", 1);
    npcs[1] = new NPC(1, "Luis", 0);
    npcs[2] = new NPC(2, "Carlos", 2);

}

void Juego::inicializarNiveles()
{
    niveles[0]->agregarDefensor(0);
    niveles[1]->agregarDefensor(1);
}


TwoSAT Juego::construirTwoSATActual()
{
    TwoSAT ts(totalNPC * 2);

    for(int i=0; i<totalNPC; i++)
    {
        int F=2*i;
        int E=2*i+1;

        ts.addOr( ts.var(F,false), ts.var(E,false) );

        if(jugador.esAmigo(i))
            ts.setTrue( ts.var(F,true) );

        if(jugador.esEnemigo(i))
            ts.setTrue( ts.var(E,true) );
    }

    int npc = 2;
    int F2 = 2*npc;

    ts.setTrue( ts.var(F2, false) );

    return ts;
}

void Juego::mostrarMapaNivel(int n)
{
    mapa.limpiar();

    mapa.colocarJugador(jugador.getX(), jugador.getY());

    const Vec& p = niveles[n]->getPresentes();
    for(int i = 0; i < p.size(); i++)
    {
        int npc = p[i];
        mapa.colocarNPC(3+i, 10+i, 'N');
    }

    mapa.dibujar();
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
    jugador.guardarCheckpoint();
    cout << "Checkpoint guardado.\n";
}

void Juego::jugarNivel(int n)
{
    TwoSAT ts = construirTwoSATActual();

    const Vec& defenders = niveles[n]->getDefensores();
    for(int i = 0; i < defenders.size(); i++)
    {
        int npc = defenders[i];
        int F = 2*npc;
        int E = F + 1;

        ts.setTrue( ts.var(F, true) );
        ts.setTrue( ts.var(E, false) );
    }

    if(!ts.solve())
    {
        cout << "Paradoja. Volviendo al checkpoint...\n";
        jugador.cargarCheckpoint();
        return;
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

        mapa.colocarPuerta(mapa.getAltura() - 1, mapa.getAncho() - 1);

        mapa.dibujar();

        cout <<endl<< "Mover (w/a/s/d, p = pausa): ";
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

        jugador.setPos(nx, ny);
    }
}


Juego::~Juego()
{

    for(int i=0;i<totalNiveles;i++) delete niveles[i];

    delete[] niveles;

    for(int i=0;i<totalNPC;i++) delete npcs[i];
    delete[] npcs;

}
