
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


/*

Las siguentes funciones se encontraban en el jugador.h proporcionado por
los profesores, creo que hay que codear solo 2...


int getFichasJugadas(Apuesta a);
int getNumeroApostado(Apuesta a);
char getColorApostado(Apuesta a);
int getTipoApuesta(Apuesta a);

string getNombre(Jugador j);
int getFichas(Jugador j);
Apuesta getApuestaEnPosicion(Jugador j, int pos);
int getTlApuestas(Jugador j);
int getVictorias(Jugador j);
int getDerrotas(Jugador j);


void setFichasJugadas(Apuesta& a, int fichas);
void setNumeroApostado(Apuesta& a, int numero);
void setColorApostado(Apuesta& a, char color);
void setTipoApuesta(Apuesta& a, int tipo);

void setNombre(Jugador& j, string nombre);
void setFichas(Jugador& j, int fichas);
void setApuestaEnPosicion(Jugador& j, Apuesta ap, int pos);
void setTlApuestas(Jugador& j, int tl);
void setVictorias(Jugador& j, int victorias);
void setDerrotas(Jugador& j, int derrotas);

void agregarApuesta(Jugador& j, Apuesta ap);

void cargarJugadores(Jugador jugadores[], int &cant);

*/



#endif
