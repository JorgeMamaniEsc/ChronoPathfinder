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





Juego::Juego(int cantNPC, int cantNiveles): mapa(25,40)
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
    npcs[0] = new NPC(0, "Ana",1, totalNiveles);
    npcs[1] = new NPC(1, "Mateo",0, totalNiveles);
    npcs[2] = new NPC(2, "Bruno",1, totalNiveles);
    npcs[3] = new NPC(3, "Valeria",0, totalNiveles);
    npcs[4] = new NPC(4, "Lucia",1, totalNiveles);
    npcs[5] = new NPC(5, "Diego",0, totalNiveles);
    npcs[6] = new NPC(6, "Sofía",1, totalNiveles);
    npcs[7] = new NPC(7, "Marco",0, totalNiveles);
    npcs[8] = new NPC(8, "Elena",1, totalNiveles);
    npcs[9] = new NPC(9, "Tadeo",0, totalNiveles);


    npcs[3]->setNivel(0, 8, 8);
    npcs[3]->setAparece(0);
    npcs[0]->setNivel(0, 5, 6);
    npcs[0]->setAparece(0);
    npcs[1]->setNivel(0, 10, 9);
    npcs[1]->setAparece(0);
    npcs[4]->setNivel(0, 22, 14);
    npcs[4]->setAparece(0);
    npcs[7]->setNivel(0, 9, 3);
    npcs[7]->setAparece(0);

    npcs[0]->setNivel(1, 6, 6);
    npcs[0]->setAparece(1);
    npcs[2]->setNivel(1, 13, 6);
    npcs[2]->setAparece(1);
    npcs[5]->setNivel(1, 20, 9);
    npcs[5]->setAparece(1);
    npcs[1]->setNivel(1, 10, 12);
    npcs[1]->setAparece(1);
    npcs[8]->setNivel(1, 3, 14);
    npcs[8]->setAparece(1);
    npcs[3]->setNivel(1, 18, 5);
    npcs[3]->setAparece(1);

    npcs[4]->setNivel(2, 23, 5);
    npcs[4]->setAparece(2);
    npcs[2]->setNivel(2, 8, 11);
    npcs[2]->setAparece(2);
    npcs[6]->setNivel(2, 15, 7);
    npcs[6]->setAparece(2);
    npcs[5]->setNivel(2, 19, 14);
    npcs[5]->setAparece(2);


    npcs[3]->setNivel(3, 7, 9);
    npcs[3]->setAparece(3);
    npcs[6]->setNivel(3, 14, 6);
    npcs[6]->setAparece(3);
    npcs[8]->setNivel(3, 24, 12);
    npcs[8]->setAparece(3);
    npcs[9]->setNivel(3, 17, 8);
    npcs[9]->setAparece(3);
    npcs[5]->setNivel(3, 10, 4);
    npcs[5]->setAparece(3);


    npcs[2]->setNivel(4, 9, 4);
    npcs[2]->setAparece(4);
    npcs[7]->setNivel(4, 16, 7);
    npcs[7]->setAparece(4);
    npcs[8]->setNivel(4, 21, 10);
    npcs[8]->setAparece(4);
    npcs[9]->setNivel(4, 12, 15);
    npcs[9]->setAparece(4);
    npcs[6]->setNivel(4, 4, 13);
    npcs[6]->setAparece(4);

    npcs[0]->setDialogo("La proxima vez estare donde x + y = 12.", 0);
    npcs[0]->setDialogo("Tal vez este sea nuestro ultimo cruce de caminos.", 1);
    npcs[1]->setDialogo("Si sumas mis proximas coordenadas tendras 22.", 0);
    npcs[1]->setDialogo("Si nos volvemos a ver, sera por pura suerte.", 1);
    npcs[2]->setDialogo("La proxima vez, x + y seguira siendo 19.", 1);
    npcs[2]->setDialogo("Cuando vuelvas a verme, x + y sera igual a 13.", 2);
    npcs[2]->setDialogo("Aqui se acaba mi ruta… pero la tuya sigue.", 4);
    npcs[3]->setDialogo("La proxima vez estare donde x + y = 23.", 0);
    npcs[3]->setDialogo("Cuando me busques otra vez, x + y valdra 16.", 1);
    npcs[3]->setDialogo("Si desaparezco, escucha bien: el mapa nunca esta quieto.", 3);
    npcs[4]->setDialogo("La proxima vez estare donde x + y = 28.", 0);
    npcs[4]->setDialogo("Despues de esto, me perdere entre las sombras del mapa.", 2);
    npcs[5]->setDialogo("Mi siguiente parada tiene x + y igual a 33.", 1);
    npcs[5]->setDialogo("Luego, búscame donde x + y = 14.", 2);
    npcs[5]->setDialogo("Si no vuelvo, al menos corre más rapido que yo.", 3);
    npcs[6]->setDialogo("La proxima vez, x + y sera igual a 20.", 2);
    npcs[6]->setDialogo("Cuando regreses, estare donde x + y = 17.", 3);
    npcs[6]->setDialogo("Este es mi ultimo nivel… que el tuyo llegue mas lejos.", 4);
    npcs[7]->setDialogo("Si me buscas de nuevo, x + y sera 23.", 0);
    npcs[7]->setDialogo("No planeo seguirte despues de aquí.", 4);
    npcs[8]->setDialogo("Algun dia me veras donde x + y = 36.", 1);
    npcs[8]->setDialogo("Y luego, en un lugar donde x + y = 31.", 3);
    npcs[8]->setDialogo("Si llegaste hasta aqui, ya no necesitas mis pistas.", 4);
    npcs[9]->setDialogo("La proxima vez, x + y sumara 27.", 3);
    npcs[9]->setDialogo("Despues de esto, solo quedaran tus pasos.", 4);
}

void Juego::inicializarNiveles()
{
    niveles[0]->agregarNPC(0);
    niveles[0]->agregarNPC(1);
    niveles[0]->agregarNPC(3);
    niveles[0]->agregarNPC(4);
    niveles[0]->agregarNPC(7);

    niveles[1]->agregarDefensor(0);
    niveles[1]->agregarDefensor(3);
    niveles[1]->agregarNPC(0);
    niveles[1]->agregarNPC(2);
    niveles[1]->agregarNPC(1);
    niveles[1]->agregarNPC(5);
    niveles[1]->agregarNPC(8);
    niveles[1]->agregarNPC(3);

    niveles[2]->agregarDefensor(4);
    niveles[2]->agregarDefensor(2);
    niveles[2]->agregarNPC(4);
    niveles[2]->agregarNPC(2);
    niveles[2]->agregarNPC(6);
    niveles[2]->agregarNPC(5);

    niveles[3]->agregarDefensor(6);
    niveles[3]->agregarDefensor(3);
    niveles[3]->agregarDefensor(5);
    niveles[3]->agregarNPC(3);
    niveles[3]->agregarNPC(6);
    niveles[3]->agregarNPC(8);
    niveles[3]->agregarNPC(9);
    niveles[3]->agregarNPC(5);

    niveles[4]->agregarDefensor(2);
    niveles[4]->agregarDefensor(6);
    niveles[4]->agregarDefensor(7);
    niveles[4]->agregarNPC(2);
    niveles[4]->agregarNPC(7);
    niveles[4]->agregarNPC(8);
    niveles[4]->agregarNPC(9);
    niveles[4]->agregarNPC(6);
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
            cout<< "             _____________"           <<endl;
            cout<< "          .-'  _____   ____'-."       <<endl;
            cout<< "        .'   .´     `.'     `.  ."    <<endl;
            cout<< "       /    /  _   _  _   _   \\  \\" <<endl;
            cout<< "      |    |  ( ) ( )( ) ( )   |  |"  <<endl;
            cout<< "      |    |   ___     ___     |  |"  <<endl;
            cout<< "      |    |  (___)   (___)    |  |"  <<endl;
            cout<< "       \\    \\    .:::::.      /  /" <<endl;
            cout<< "        `.    `-. '–––'  .-' .'"      <<endl;
            cout<< "          `-.     `-----´   .-´"      <<endl;
            cout<< "             `----._____.---´"        <<endl;
            cout<< "              /    /   \\    \\"      <<endl;
            cout<< "             /____/     \\____\\"     <<endl;
            cout<<endl;
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
        cout << "\nFelicidades! Terminaste todos los niveles.\n";
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
    cout << endl<<npc->getDialogo(nivelActual) <<endl<<endl;
    if(jugador.esAmigo(id))
    {
        cout << npc->getNombre() << ": Broooo que tal! :D\n";
        return;
    }

    if(jugador.esEnemigo(id) || npc->getRelacionNatural() == -1)
    {
        cout << npc->getNombre() << ": No quiero hablar contigo.\n";
        return;
    }

    int costo = 2;
    cout << npc->getNombre() << ": No te conozco, pero pareces buena persona.\n";

    cout << "Quieres hacerte amigo? (costo: " << costo << " PH)\n";
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
