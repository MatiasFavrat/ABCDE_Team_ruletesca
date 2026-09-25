#include <iostream>
#include "numero.h"
#include "ruleta.h"
#include "jugador.h"
#include "MenuPrincipal.h"
#include "consola.h"
using namespace std;

bool InicioSesion=false;

int main() {
	inicializarConsola();
	Jugador jugadores[10];
	int cj = 2;
	MenuPrincipal(jugadores,cj);
	
    return 0;
}
