
#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>
using namespace std;

struct Apuesta{ 
	int fichasJugadas; 
	int numeroApostado; 
	char colorApostado; 
	int tipoApuesta; // Identificador del tipo de apuesta seleccionada 1-Numero, 2-Color, 3-Par, 4-Impar
	
};
struct Jugador { 
	string nombre; 
	int fichas; 
	Apuesta apuestas[MAX_APUESTAS]; 
	int tlApuestas; 
	int victorias;
	int derrotas;
};



void cargarJugadores(Jugador jugadores[], int &cant);

#endif
