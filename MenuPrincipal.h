#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "numero.h"
#include "jugador.h"
#include "Sesion.h"

void MenuPrincipal(Jugador jugadores[], int &cant); //MP
bool IniciarNSesion(bool &InicioSesion, Jugador jugadores[], int &cant); //1
void MostratHistorial(Sesion &sesion); //3
void MostrarEstadistaSesion(Sesion &sesion); //4
void pedirApuestas(Jugador jugadores[], int cant);
void JugarSesion(Jugador jugadores[], int cant, Numero ruleta[37], Numero historial[], int &totalGiros);


// OrdSesionGiros()
// AnalizarSesionHistoricas();
// CargarArchivo();

#endif
