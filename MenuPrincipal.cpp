#include <iostream>
#include "MenuPrincipal.h"
#include "jugador.h"
#include "ruleta.h"

/**
* ****************************************************************************************
* Función: IniciarNSesion
*
* Parámetros:
* - bool &InicioSesion : Referencia a un valor booleano que indica si ya se ha iniciado sesión previamente.
* - Jugador jugadores[] : Arreglo de objetos de tipo Jugador donde se cargarán los datos de los participantes.
* - int &cant : Referencia a una variable entera que representa la cantidad de jugadores cargados.
*
* Retorna:
* - bool : Retorna el estado actualizado del indicador de inicio de sesión.
*
* Descripción:
* Verifica si la sesión no ha sido iniciada previamente; en caso afirmativo, procede a cargar los jugadores 
* y marca la sesión como activa, de lo contrario muestra un mensaje de advertencia indicando que la sesión ya fue iniciada.
* ****************************************************************************************
*/

bool IniciarNSesion(bool &InicioSesion, Jugador jugadores[], int &cant){
	bool sesionNueva = false;
	if(InicioSesion == false){
		cargarJugadores(jugadores, cant);
		InicioSesion = true;
		sesionNueva = true;
	} else {
		cout << "¡Ya iniciaste sesion!" << endl;
	}
	return sesionNueva;
}
	
	void pedirApuestas(Jugador jugadores[], int cant){
		for(int i = 0; i < cant; i++){
			cout << "\n--- Turno de " << jugadores[i].nombre 
				<< " (fichas: " << jugadores[i].fichas << ") ---" << endl;
			
			int fichas;
			do {
				cout << "Fichas a apostar: ";
				cin >> fichas;
			} while(fichas <= 0 || fichas > jugadores[i].fichas);
			
			int tipo;
			do {
				cout << "Tipo de apuesta (1-Numero, 2-Color, 3-Par, 4-Impar): ";
				cin >> tipo;
			} while(tipo < 1 || tipo > 4);
			
			int numero = -1;
			char color = ' ';
			
			if(tipo == 1){
				do {
					cout << "Numero apostado (0-36): ";
					cin >> numero;
				} while(numero < 0 || numero > 36);
			} else if(tipo == 2){
				do {
					cout << "Color apostado (R-Rojo, N-Negro): ";
					cin >> color;
				} while(color != 'R' && color != 'N');
			}
			
			registrarApuesta(jugadores[i], fichas, tipo, numero, color);
		}
	}	
	
/*		void JugarSesion(Jugador jugadores[], int cant, Numero ruleta[37], 
						 Numero historial[], int &totalGiros){
			
			bool seguir = true;
			
			while(seguir && !hayJugadorEnQuiebra(jugadores, cant) && totalGiros < MAX_JUGADAS){
				
				pedirApuestas(jugadores, cant);
				// PENDIENTE Paso 3: "No va más!" + girar + guardar en historial
				// PENDIENTE Paso 4: liquidar + mostrar estado
				// PENDIENTE Paso 5: preguntar si seguir -> actualizar 'seguir'
			}
			// PENDIENTE: mensaje de cierre según por qué terminó
		}*/

void MostratHistorial(){
	//Funcion con el flujo del juego(creo...)
}

void MostrarEstadistaSesion(){
    
}

/**
* ****************************************************************************************
* Función: MenuPrincioal
*
* Parámetros:
* - bool &InicioSesion : Referencia a un valor booleano que indica si se ha iniciado sesión o el estado de la misma.
* - Jugador jugadores[] : Arreglo de objetos de tipo Jugador que almacena la información de los participantes.
* - int &cant : Referencia a una variable entera que representa la cantidad actual de jugadores.
*
* Retorna:
* - void : No retorna ningún valor.
*
* Descripción:
* Despliega el menú principal de la aplicación "La Ruletesca" en la consola, permitiendo 
* al usuario navegar entre distintas opciones (como iniciar una nueva sesión, consultar 
* el estado de los jugadores, ver historiales y estadísticas, entre otras) mediante un bucle 
* que se repite hasta que se selecciona la opción de salida.
* ****************************************************************************************
*/


void MenuPrincipal(bool &InicioSesion, Jugador jugadores[], int &cant){
	char op;
	do{
		cout << "La Ruletesca\n==========================\n1.- Iniciar nueva sesion de ruleta\n2.- Consultar estado de jugadores\n3.- Mostrar historial de giros\n4.- Mostrar estadasticas de la sesion\n5.- Ordenar sesiones segun cantidad de giros (Funcionalidad en Desarrollo)\n6.- Analizar sesiones historicas (Funcionalidad en Desarrollo)\n7.- Carga de Archivo (Funcionalidad en Desarrollo)\nX.- Salir de la aplicacion\nIngrese una opcion: ";
		cin >> op;
		switch(op){
			case '1':
				if(!InicioSesion){
					IniciarNSesion(InicioSesion, jugadores, cant);
					//JugarSesion(jugadores, cant, ruleta, historial, totalGiros);
				} else {
					cout << "Ya iniciaste sesion." << endl;
				}
				break;
			case '2':
				if(InicioSesion){
					mostrarEstadoJugadores(jugadores,cant);
				}
				break;
			case '3':
				if(InicioSesion){
					MostratHistorial();
				}
				break;
				
			case '4':
				if(InicioSesion){
					MostrarEstadistaSesion();
				}
				break;
			case '5':
                cout << "Fucion en desarrollo...\n"; 
				//OrdSesionGiros();
				break;
			case '6':
                cout << "Fucion en desarrollo...\n";
				//AnalizarSesionHistoricas();
				break;
			case '7':
                cout << "Fucion en desarrollo...\n";
				//CargarArchivo();
				break;
		}
	}while(op!='x' && op != 'X');
}
