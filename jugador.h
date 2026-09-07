
#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>
using namespace std;

struct Jugador { 
	string nombre; 
	int fichas; 
	int apuestaNumero; 
	char apuestaColor; 
	int tipoApuesta; // Identificador del tipo de apuesta seleccionada
	int victorias;
	int derrotas;
};

void cargarJugadores(Jugador jugadores[], int &cant);

#endif
