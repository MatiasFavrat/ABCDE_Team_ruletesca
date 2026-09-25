#include <iostream>

#include "Sesion.h"
#include "jugador.h"
#include "numero.h"
#include "ruleta.h"

#include <windows.h>

using namespace std;

void inicializarSesion(Sesion &sesion,Jugador jugadores[], int &cantidadJugadores){
	cargarJugadores(jugadores,cantidadJugadores);
	for(int i=0;i<cantidadJugadores;i++) { 
		sesion.jugadoresParticipantes[i]=jugadores[i];	
	}
	sesion.cantidadGiros=0;
	
	
}
	
	
	
	
int cicloDeJuego(Numero ruleta[] ,Jugador jugadores[],int cantidadJugadores,Sesion &sesionActual,int &ciclo){
	while(ciclo==1){
		for(int i=0;i<cantidadJugadores;i++) { 
			string nombre = jugadores[i].nombre;
			cout << nombre << " inserte las fichas a apostar:" ;
			int cantFichas; cin >> cantFichas;
			
			int numero=0;
			char color='V';
			bool opcionCorrecta=false;
			while(!opcionCorrecta){
				cout << endl << " inserte el tipo de apuesta \n (1) Numero. \n(2) Color. \n(3) Paridad.\n";
				int tipo; cin >> tipo;	
				if(tipo==1){
					cout << endl << "Inserte el numero al que desee apostar (del 0 al 36): "; cin >> numero;
					registrarApuesta(jugadores[i],cantFichas,tipo,numero,color);
					opcionCorrecta=true;
				}else if(tipo==2){
					cout << endl << "Inserte el color al que desee apostar (R) Rojo (N) Negro: "; cin >> color;
					registrarApuesta(jugadores[i],cantFichas,tipo,numero,color);
					opcionCorrecta=true;
				}else if(tipo==3){
					int paridad;
					while (!opcionCorrecta){
						cout << endl << "Inserte si desea apostar por los (1) pares (2) impares: "; cin >> paridad;
						if (paridad == 1){
							registrarApuesta(jugadores[i],cantFichas,3,numero,color);
							opcionCorrecta=true;
						}else if (paridad == 2){
							registrarApuesta(jugadores[i],cantFichas,4,numero,color);
							opcionCorrecta=true;
						}
					}
				}
			}
		}	
		cout << "NO VA MAS!" << endl;
		Numero resultado = girarRuleta(ruleta);
		sesionActual.Resultados[sesionActual.cantidadGiros]=resultado;
		sesionActual.cantidadGiros++;
		liquidarApuestas(jugadores,cantidadJugadores,resultado);
		mostrarEstadoJugadores(jugadores,cantidadJugadores);
		if(hayJugadorEnQuiebra(jugadores,cantidadJugadores)){
			
		
			cout << "\n\n\nHay jugadores en quiebra!\nPresiona Enter para volver al menu principal.";
			cin.ignore();cin.get();
			ciclo=3;
		}else{
			cout << "Desean realizar el siguiente giro o finalizar la sesion.\n (1) Realizar el siguiente giro. \n (2) Pausar Sesion y volver al menu principal. \n(3) finaliz sesion.\n";
			cin >> ciclo;
		}
	}
	return ciclo;	
}
