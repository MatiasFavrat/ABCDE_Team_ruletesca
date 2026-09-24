#include <iostream>
#include "numero.h"
#include "ruleta.h"
#include "jugador.h"
//#include "MenuJuego.h"

using namespace std;

void IniciarNSesion(){
	cargarJugadores(jugadores[],cant);
}

void MenuPrincioal(){
	char op;
	do{
		cout << "La Ruletesca\n==========================\n1.- Iniciar nueva sesión de ruleta\n2.- Consultar estado de jugadores\n3.- Mostrar historial de giros\n4.- Mostrar estadísticas de la sesión\n5.- Ordenar sesiones según cantidad de giros (Funcionalidad en Desarrollo)\n6.- Analizar sesiones históricas (Funcionalidad en Desarrollo)\n7.- Carga de Archivo (Funcionalidad en Desarrollo)\nX.- Salir de la aplicación\nIngrese una opción: "
		cin >> op;
		swicht(op){
			case '1':
				IniciarNSesion();
				break;
			case '2':
				ConsultarEstado();
				break;
			case '3':
				MostratHistorial();
				break;
			case '4':
				MostrarEstadistaSesion();
				break;
			case '5':
				//OrdSesionGiros();
				break;
			case '6':
				//AnalizarSesionHistoricas();
				break;
			case '7':
				//CargarArchivo();
				break;
		}
	}while(op=='x')
}


int main() {
	
	
	Numero nums[37];
	inicializarRuleta(nums);
	bool i=1;
	while(i){
		
		cin >> i;
		girarRuleta(nums);	
	}
    return 0;
}
