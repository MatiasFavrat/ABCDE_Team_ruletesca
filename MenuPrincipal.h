#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "numero.h"
#include "jugador.h"
#include "Sesion.h"

void MenuPrincipal(Jugador jugadores[], int &cant); //MP
void MostratHistorial(Sesion &sesion); //3
void MostrarEstadistaSesion(Sesion &sesion); //4
void OrdSesionGiros(ptrNodo lista); //5
void AnalizarSesionHistoricas(ptrNodo lista); //6
void CargarArchivo(ptrNodo &lista, char nombreArchivo[]); //7

#endif
