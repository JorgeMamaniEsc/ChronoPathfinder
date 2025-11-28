#include "Menu.h"

MenuPrincipal::MenuPrincipal()
{
    // nada
}

void MenuPrincipal::mostrar() const
{
    cout << "==============================\n";
    cout << "      CHRONOPATHFINDER        \n";
    cout << "==============================\n\n";

    cout << "  [1] Iniciar Juego\n";
    cout << "  [2] Puntajes\n";
    cout << "  [3] Salir\n";
    cout << "\nOpcion: ";
}

int MenuPrincipal::leerOpcion() const
{
    int op;
    cin >> op;
    return op;
}

MenuPrincipal::~MenuPrincipal()
{
    // nada
}


MenuPausa::MenuPausa()
{
    // nada
}

void MenuPausa::mostrar() const
{
    cout << "\n===== PAUSA =====\n";
    cout << " [1] Continuar\n";
    cout << " [2] Guardar Checkpoint\n";
    cout << " [3] Salir del Juego\n";
    cout << "Opcion: ";
}

int MenuPausa::leerOpcion() const
{
    int op;
    cin >> op;
    return op;
}

MenuPausa::~MenuPausa()
{
    // nada
}
