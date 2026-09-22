
#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>
#include "numero.h"
using namespace std;

const int MAX_JUGADORES = 6;
const int MIN_JUGADORES = 2;
const int MAX_APUESTAS = 1200;
const int FICHAS_INICIALES = 2000;

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
void registrarApuesta(Jugador &j, int fichas, int tipo, int numero, char color);
int calcularPago(Apuesta a, Numero resultado);
void liquidarApuestas(Jugador jugadores[], int cant, Numero resultado);
void mostrarEstadoJugadores(Jugador jugadores[], int cant);
bool hayJugadorEnQuiebra(Jugador jugadores[], int cant);

#endif
