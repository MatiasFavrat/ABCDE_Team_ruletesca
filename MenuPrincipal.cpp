#include <iostream>
#include "MenuPrincipal.h"
#include "jugador.h"
#include "ruleta.h"
#include "Sesion.h"
#include "AnimacionRuleta.h"
#include "numero.h"

#include <windows.h>

/**
 * ****************************************************************************************
 * Función: MostratHistorial
 *
 * Parámetros:
 * - Sesion &sesion : Referencia al objeto Sesion del cual se desea mostrar el historial de resultados.
 *
 * Retorna:
 * - void : No retorna ningún valor.
 *
 * Descripción:
 * Obtiene la cantidad de giros registrados en la sesión y recorre el arreglo de resultados para imprimir por consola cada número
 * histórico con su respectivo índice y formato de presentación.
 * ****************************************************************************************
 */

void MostratHistorial(Sesion &sesion)
{
	int cgiros = sesion.cantidadGiros;
	cout << "Historial de resultados:\n";
	for (int i = 0; i < cgiros; i++)
	{
		int n = obtenerValor(sesion.Resultados[i]);
		cout << "[" << i << "]:";
		imprimirNumero(n);
		cout << endl;
	}
}

/**
 * ****************************************************************************************
 * Función: MostrarEstadistaSesion
 *
 * Parámetros:
 * - Sesion &sesion : Referencia al objeto Sesion del cual se calcularán y mostrarán las estadísticas.
 *
 * Retorna:
 * - void : No retorna ningún valor.
 *
 * Descripción:
 * Recorre los resultados almacenados en la sesión para contar y acumular las estadísticas clave de los giros (números ceros,
 * cantidad de rojos, negros, pares e impares), calculando luego sus porcentajes y mostrando un reporte formateado y estilizado
 * con colores por la consola.
 * ****************************************************************************************
 */

void MostrarEstadistaSesion(Sesion &sesion)
{
	int cPares = 0, cImpares = 0, cRojos = 0, cNegros = 0, cZero = 0;

	int cgiros = sesion.cantidadGiros;
	for (int i = 0; i < cgiros; i++)
	{
		Numero resultado = sesion.Resultados[i];
		int valor = obtenerValor(sesion.Resultados[i]);
		if (valor == 0)
		{
			cZero++;
		}
		else
		{
			if (obtenerColor(resultado) == 'R')
			{
				cRojos++;
			}
			else
			{
				cNegros++;
			}
			if (obtenerParidad(resultado) == 1)
			{
				cPares++;
			}
			else
			{
				cImpares++;
			}
		}
	}
	cout << '\n';
	imprimirStringConColor("=========================================================", 4);
	cout << '\n';
	imprimirStringConColor("Estadisticas de la sesion", 4) << '\n';
	imprimirStringConColor("=========================================================", 4);
	cout << '\n';

	cout << "Cantidad de giros: " << cgiros << '\n';

	imprimirStringConColor("===========================Paridad=======================", 7);
	cout << '\n';

	cout << "\nPorcentaje de impares: " << (cImpares * 100.0) / cgiros;
	cout << "\nPorcentaje de pares: " << (cPares * 100.0) / cgiros << '\n';

	imprimirStringConColor("==============================COLOR======================", 7);
	cout << '\n';

	imprimirStringConColor("Rojos:", 1);
	cout << ' ' << cRojos << '\n';
	imprimirStringConColor("Negros:", 2);
	cout << ' ' << cNegros << '\n';
}

/**
 * ****************************************************************************************
 * Funci�n: MenuPrincioal
 *
 * Par�metros:
 * - bool &InicioSesion : Referencia a un valor booleano que indica si se ha iniciado sesi�n o el estado de la misma.
 * - Jugador jugadores[] : Arreglo de objetos de tipo Jugador que almacena la informaci�n de los participantes.
 * - int &cant : Referencia a una variable entera que representa la cantidad actual de jugadores.
 *
 * Retorna:
 * - void : No retorna ning�n valor.
 *
 * Descripci�n:
 * Despliega el men� principal de la aplicaci�n "La Ruletesca" en la consola, permitiendo
 * al usuario navegar entre distintas opciones (como iniciar una nueva sesi�n, consultar
 * el estado de los jugadores, ver historiales y estad�sticas, entre otras) mediante un bucle
 * que se repite hasta que se selecciona la opci�n de salida.
 * ****************************************************************************************
 */

void MenuPrincipal(Jugador jugadores[], int &cant)
{
	char op;

	bool isSessionPlayed = 0;

	int sesionActual = -1;
	int ultimaSesion = -1;
	Sesion sesionGuardada;

	Numero ruleta[37];
	inicializarRuleta(ruleta);
	int condicionDeCiclo = 1;

	do
	{
		system("cls");
		cout << "La Ruletesca\n==========================\n1.- Iniciar nueva sesion de ruleta\n2.- Consultar estado de jugadores\n3.- Mostrar historial de giros\n4.- Mostrar estadasticas de la sesion\n5.- Ordenar sesiones segun cantidad de giros (Funcionalidad en Desarrollo)\n6.- Analizar sesiones historicas (Funcionalidad en Desarrollo)\n7.- Carga de Archivo (Funcionalidad en Desarrollo)\nX.- Salir de la aplicacion\nIngrese una opcion: ";
		cin >> op;
		switch (op)
		{
		case '1':
			if (!isSessionPlayed)
			{
				condicionDeCiclo = 1;

				Sesion nuevaSesion;
				ultimaSesion++;
				sesionActual = ultimaSesion;
				inicializarSesion(nuevaSesion, jugadores, cant);

				cicloDeJuego(ruleta, jugadores, cant, nuevaSesion, condicionDeCiclo);

				sesionGuardada = nuevaSesion;
				isSessionPlayed = 1;
			}
			else
			{
				cout << "Ya hay una sesion en curso �Desea continuarla donde la dejo? \n(1) Continuar sesion.\n (2) Cancelar. \n(3) Finalizar sesion.\n";
				int opcion = -1;
				while (opcion < 1 or opcion > 3)
				{
					cin >> opcion;
					if (opcion == 1)
					{
						condicionDeCiclo = 1;
						cicloDeJuego(ruleta, jugadores, cant, sesionGuardada, condicionDeCiclo);
					}
					else if (opcion == 3)
					{
						isSessionPlayed = 1;
					}
				}
			}
			break;
		case '2':
			if (isSessionPlayed)
			{
				mostrarEstadoJugadores(sesionGuardada.jugadoresParticipantes, cant);
				cin.ignore();
				cin.get();
			}
			break;
		case '3':
			if (isSessionPlayed)
			{
				MostratHistorial(sesionGuardada);
				cin.ignore();
				cin.get();
			}
			break;

		case '4':
			if (isSessionPlayed)
			{
				MostrarEstadistaSesion(sesionGuardada);
				cin.ignore();
				cin.get();
			}
			break;
		case '5':
			cout << "Fucion en desarrollo...\n";
			// OrdSesionGiros();
			break;
		case '6':
			cout << "Fucion en desarrollo...\n";
			// AnalizarSesionHistoricas();
			break;
		case '7':
			cout << "Fucion en desarrollo...\n";
			// CargarArchivo();
			break;
		}
	} while (op != 'x' && op != 'X');
}
