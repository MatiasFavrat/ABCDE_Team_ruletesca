#include <iostream>
#include "MenuPrincipal.h"
#include "jugador.h"
#include "ruleta.h"
#include "Sesion.h"

#include <windows.h>

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




void MenuPrincipal(Jugador jugadores[], int &cant){
	char op;
	int sesionActual=-1;
	int ultimaSesion=-1;
	Sesion sesiones[5];
	
	Numero ruleta[37];
	inicializarRuleta(ruleta);
	int condicionDeCiclo=1;
	
	do{
		system("cls");
		cout << "La Ruletesca\n==========================\n1.- Iniciar nueva sesion de ruleta\n2.- Consultar estado de jugadores\n3.- Mostrar historial de giros\n4.- Mostrar estadasticas de la sesion\n5.- Ordenar sesiones segun cantidad de giros (Funcionalidad en Desarrollo)\n6.- Analizar sesiones historicas (Funcionalidad en Desarrollo)\n7.- Carga de Archivo (Funcionalidad en Desarrollo)\nX.- Salir de la aplicacion\nIngrese una opcion: ";
		cin >> op;
		switch(op){
			case '1':
				if(sesionActual==-1){
					condicionDeCiclo=1;
					
					Sesion nuevaSesion;
					ultimaSesion++;
					sesionActual=ultimaSesion;
					inicializarSesion(nuevaSesion,jugadores,cant);
					
					
					
					cicloDeJuego(ruleta,jugadores,cant,nuevaSesion,condicionDeCiclo);
					if(condicionDeCiclo==3){
						sesiones[sesionActual]=nuevaSesion;
						sesionActual=-1;
					}
					
				} else {
					cout << "Ya hay una sesion en curso ¿Desea continuarla donde la dejo? \n(1) Continuar sesion.\n (2) Cancelar. \n(3) Finalizar sesion.\n";
					int opcion=-1;
					while(opcion<1 or opcion>3){
						cin >> opcion;
						if(opcion==1){
							condicionDeCiclo=1;
							cicloDeJuego(ruleta,jugadores,cant,sesiones[sesionActual],condicionDeCiclo);
						}else if(opcion==3){
							sesionActual=-1;
						}
					}
				}
				break;
			case '2':
				if(sesionActual!=-1){
					mostrarEstadoJugadores(jugadores,cant);
				}
				break;
			case '3':
				if(sesionActual!=-1){
					MostratHistorial();
				}
				break;
				
			case '4':
				if(sesionActual!=-1){
					//MostrarEstadistaSesion();
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
