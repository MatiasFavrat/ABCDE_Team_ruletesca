#include <iostream>
#include "MenuPrincipal.h"
#include "jugador.h"


bool IniciarNSesion(bool &InicioSesion, Jugador jugadores[], int &cant){
    if(InicioSesion==false){
        cargarJugadores(jugadores,cant);
        InicioSesion=true;
    }else{
        cout << "¡ Ya iniciaste sesion !";
    }
    return InicioSesion;
}

void MostratHistorial(){

}

void MostrarEstadistaSesion(){
    
}

void MenuPrincioal(bool &InicioSesion, Jugador jugadores[], int &cant){
	char op;
	do{
		cout << "La Ruletesca\n==========================\n1.- Iniciar nueva sesión de ruleta\n2.- Consultar estado de jugadores\n3.- Mostrar historial de giros\n4.- Mostrar estadísticas de la sesión\n5.- Ordenar sesiones según cantidad de giros (Funcionalidad en Desarrollo)\n6.- Analizar sesiones históricas (Funcionalidad en Desarrollo)\n7.- Carga de Archivo (Funcionalidad en Desarrollo)\nX.- Salir de la aplicación\nIngrese una opción: ";
		cin >> op;
		switch(op){
			case '1':
				IniciarNSesion(InicioSesion,jugadores,cant);
				break;
			case '2':
				mostrarEstadoJugadores(jugadores,cant);
				break;
			case '3':
				MostratHistorial();
				break;
			case '4':
				MostrarEstadistaSesion();
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
	}while(op!='x');
}
