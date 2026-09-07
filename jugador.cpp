
#include <iostream>
#include "jugador.h"
using namespace std;

void cargarJugadores(Jugador jugadores[], int &cant){
    cout << "Cantidad de jugadores: ";
    cin >> cant;

    for(int i=0;i<cant;i++){
        cout << "Nombre jugador " << i+1 << ": ";
        cin >> jugadores[i].nombre;
        jugadores[i].fichas = 2000;
    }
}
