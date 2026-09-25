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

#endif
