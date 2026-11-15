#ifndef SESION_H
#define SESION_H

#include "numero.h"
#include "jugador.h"

#include "ruleta.h" // para MAX_JUGADAS

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

void inicializarSesion(Sesion &sesion, Jugador jugadores[], int &cantidadJugadores);
int cicloDeJuego(Numero ruleta[], Jugador jugadores[], int cantidadJugadores, Sesion &sesionActual, int &ciclo);

// agrega la sesion al final de la lista
void agregarSesionAlFinal(ptrNodo &lista, const Sesion &sesion);
// cantidad de sesiones en la lista
int contarSesiones(ptrNodo lista);
// mayor idSesion de la lista (0 si esta vacia)
int maxIdSesion(ptrNodo lista);

#endif
