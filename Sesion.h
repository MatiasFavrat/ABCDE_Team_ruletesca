#ifndef SESION_H
#define SESION_H


#include "numero.h"
#include "jugador.h"
const int maxGiros = 1200;

struct Sesion{
	int cantidadGiros;
	Jugador jugadoresParticipantes[6];
	Numero Resultados[maxGiros];
};

void inicializarSesion(Sesion &sesion,Jugador jugadores[],int &cantidadJugadores);
int cicloDeJuego(Numero ruleta[] ,Jugador jugadores[],int cantidadJugadores,Sesion &sesionActual,int &ciclo);
void MostrarEstadistaSesion();

/*

Las siguentes funciones se encontraban en el sesion.h proporcionado por
los profesores, lo paja es que hay que manejar punteros xd


struct Sesion {
	int idSesion;
	Numero historial[MAX_JUGADAS];
	int totalGiros; 
	Jugador jugadores[MAX_JUGADORES];
	int jugadoresSesion;   
};

struct Nodo { 
	Sesion info; 
	struct Nodo *sig; 
};

typedef Nodo *ptrNodo;

*/



#endif
