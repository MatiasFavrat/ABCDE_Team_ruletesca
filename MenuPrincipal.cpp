#include <iostream>
#include "MenuPrincipal.h"
#include "jugador.h"
#include "ruleta.h"
#include "Sesion.h"
#include "AnimacionRuleta.h"
#include "numero.h"

#include "archivo.h"
#include <cstring>
#include <windows.h>

/******************************************************************************************
 * 
 * FunciÃ³n: MostratHistorial
 *
 * ParÃ¡metros:
 * - Sesion &sesion : Referencia al objeto Sesion del cual se desea mostrar el historial de resultados.
 *
 * Retorna:
 * - void : No retorna ningÃºn valor.
 *
 * DescripciÃ³n:
 * Obtiene la cantidad de giros registrados en la sesiÃ³n y recorre el arreglo de resultados para imprimir por consola cada nÃºmero
 * histÃ³rico con su respectivo Ã­ndice y formato de presentaciÃ³n.
 * 
 *****************************************************************************************/

void MostratHistorial(Sesion &sesion)
{
	int cgiros = sesion.totalGiros;
	cout << "Historial de resultados:\n";
	for (int i = 0; i < cgiros; i++)
	{
		int n = obtenerValor(sesion.historial[i]);
        int paridad = obtenerParidad(sesion.historial[i]);

		cout << "[" << i << "]:";
		imprimirNumero(n);

		if (n == 0)
		{
			cout << "Cero (Sin paridad)";
		}
		else if (paridad == 1)
        {
            cout << "Par";
        }
        else
        {
            cout << "Impar";
        }

		cout << endl;
	}
}

/**
 * ****************************************************************************************
 * FunciÃ³n: MostrarEstadistaSesion
 *
 * ParÃ¡metros:
 * - Sesion &sesion : Referencia al objeto Sesion del cual se calcularÃ¡n y mostrarÃ¡n las estadÃ­sticas.
 *
 * Retorna:
 * - void : No retorna ningÃºn valor.
 *
 * DescripciÃ³n:
 * Recorre los resultados almacenados en la sesiÃ³n para contar y acumular las estadÃ­sticas clave de los giros (nÃºmeros ceros,
 * cantidad de rojos, negros, pares e impares), calculando luego sus porcentajes y mostrando un reporte formateado y estilizado
 * con colores por la consola.
 * ****************************************************************************************
 */

void MostrarEstadistaSesion(Sesion &sesion)
{
	int cPares = 0, cImpares = 0, cRojos = 0, cNegros = 0, cZero = 0;

	int cgiros = sesion.totalGiros;
	for (int i = 0; i < cgiros; i++)
	{
		Numero resultado = sesion.historial[i];
		int valor = obtenerValor(sesion.historial[i]);
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
	imprimirStringConColor("Estadisticas de la sesion", 4) ;
	cout << '\n';
	imprimirStringConColor("=========================================================", 4);
	cout << '\n';

	cout << "Cantidad de giros: " << cgiros << '\n';


	if(cgiros>0){
		imprimirStringConColor("===========================Paridad=======================", 7);
		cout << '\n';
		cout << "\nPorcentaje de impares: " << (cImpares * 100.0) / cgiros;
		cout << "\nPorcentaje de pares: " << (cPares * 100.0) / cgiros ;
		cout << "\nPorcentaje de ceros (0): " << (cZero * 100.0) / cgiros << "%\n";

		imprimirStringConColor("==============================COLOR======================", 7);
		cout << '\n';
		imprimirStringConColor("Rojos:", 1);
		cout << ' ' << cRojos << '\n';
		imprimirStringConColor("Negros:", 2);
		cout << ' ' << cNegros << '\n';
		imprimirStringConColor("Verdes:", 3);
		cout << ' ' << cZero << '\n';
	}else{
		cout << "Aun no se han realizado giros en esta sesion.\n";
	}

	
}

/**
Funcion: OrdSesionGiros (opcion 5)

Parametros:
- ptrNodo lista: Lista con las sesiones guardadas.

Descripcion:
Ordena las sesiones de menor a mayor segun totalGiros y las muestra con su
numero de sesion. Se ordena un arreglo de punteros a los nodos, asi no hay que
mover las sesiones (son muy pesadas) ni se altera el orden de la lista.
*/
void OrdSesionGiros(ptrNodo lista)
{
	int n = contarSesiones(lista);

	if (n == 0)
	{
		cout << "\nNo hay sesiones cargadas.\n";
	}
	else
	{
		ptrNodo *v = new ptrNodo[n];
		ptrNodo aux = lista;
		for (int i = 0; i < n; i++)
		{
			v[i] = aux;
			aux = aux->sig;
		}

		// insercion
		for (int i = 1; i < n; i++)
		{
			ptrNodo x = v[i];
			int j = i - 1;
			while (j >= 0 && v[j]->info.totalGiros > x->info.totalGiros)
			{
				v[j + 1] = v[j];
				j--;
			}
			v[j + 1] = x;
		}

		cout << "\nSesion\tTotal de giros\n";
		for (int i = 0; i < n; i++)
		{
			cout << v[i]->info.idSesion << "\t" << v[i]->info.totalGiros << endl;
		}
		delete[] v;
	}
}

/****************************************************
- Función: totalFichasApostadas
- Parámetros:
- - Jugador j : Estructura con los datos y el historial de apuestas del jugador
- Retorna:
- - int : Cantidad total de fichas apostadas por el jugador
- Descripción:
- Recorre secuencialmente todas las apuestas realizadas por el jugador mediante su
tamaño lógico y acumula el valor de fichas jugadas en cada una.
****************************************************/
int totalFichasApostadas(Jugador j)
{
	int total = 0;
	for (int i = 0; i < getTlApuestas(j); i++)
	{
		total += getFichasJugadas(getApuestaEnPosicion(j, i));
	}
	return total;
}

/****************************************************
- Función: jugadorMasVictorias
- Parámetros:
- - ptrNodo lista : Puntero al inicio de la lista enlazada de sesiones
- Retorna:
- - void : No devuelve valor (imprime los resultados por consola)
- Descripción:
- Recorre la lista enlazada de sesiones. En cada sesión realiza una búsqueda del
máximo sobre el arreglo de jugadores comparando sus victorias para identificar y
mostrar al ganador.
****************************************************/
void jugadorMasVictorias(ptrNodo lista)
{
	cout << "\nJugador con mas victorias por sesion\n";
	while (lista != NULL)
	{
		Sesion *s = &lista->info;
		int mejor = 0;
		for (int i = 1; i < s->jugadoresSesion; i++)
		{
			if (s->jugadores[i].victorias > s->jugadores[mejor].victorias)
			{
				mejor = i;
			}
		}
		cout << "Sesion " << s->idSesion << ": " << s->jugadores[mejor].nombre
			<< " (" << s->jugadores[mejor].victorias << " victorias)" << endl;
		lista = lista->sig;
	}
}

/****************************************************
- Función: jugadorMasApostador
- Parámetros:
- - ptrNodo lista : Puntero al inicio de la lista enlazada de sesiones
- Retorna:
- - void : No devuelve valor (imprime los resultados por consola)
- Descripción:
- Recorre cada nodo de la lista de sesiones y aplica una búsqueda del máximo calculando el total de fichas apostadas
por cada jugador (mediante totalFichasApostadas) para mostrar quién apostó más en cada sesión.
****************************************************/
void jugadorMasApostador(ptrNodo lista)
{
	cout << "\nJugador que mas fichas aposto por sesion\n";
	while (lista != NULL)
	{
		Sesion *s = &lista->info;
		int mejor = 0;
		int maxFichas = totalFichasApostadas(s->jugadores[0]);
		for (int i = 1; i < s->jugadoresSesion; i++)
		{
			int fichas = totalFichasApostadas(s->jugadores[i]);
			if (fichas > maxFichas)
			{
				maxFichas = fichas;
				mejor = i;
			}
		}
		cout << "Sesion " << s->idSesion << ": " << s->jugadores[mejor].nombre
			<< " (" << maxFichas << " fichas)" << endl;
		lista = lista->sig;
	}
}

/****************************************************
- Función: desgloseApuestas
- Parámetros:
- - ptrNodo lista : Puntero al inicio de la lista enlazada de sesiones
- Retorna:
- - void : No devuelve valor (imprime los resultados por consola)
- Descripción:
- Recorre cada sesión e inicializa un arreglo de contadores por categoría (1 a 4).
Luego itera sobre todos los jugadores y sus apuestas incrementando el contador
correspondiente a cada tipo de apuesta y muestra el resumen de la sesión.
****************************************************/
void desgloseApuestas(ptrNodo lista)
{
	cout << "\nTipos de apuestas por sesion\n";
	while (lista != NULL)
	{
		Sesion *s = &lista->info;
		int cant[5] = {0, 0, 0, 0, 0}; // indices 1 a 4, igual que tipoApuesta
		for (int i = 0; i < s->jugadoresSesion; i++)
		{
			for (int k = 0; k < s->jugadores[i].tlApuestas; k++)
			{
				int tipo = s->jugadores[i].apuestas[k].tipoApuesta;
				if (tipo >= 1 && tipo <= 4)
				{
					cant[tipo]++;
				}
			}
		}
		cout << "Sesion " << s->idSesion << ": Numero " << cant[1] << " | Color " << cant[2]
			<< " | Par " << cant[3] << " | Impar " << cant[4] << endl;
		lista = lista->sig;
	}
}

/****************************************************
- Función: rendimientoJugadores
- Parámetros:
- - ptrNodo lista : Puntero al inicio de la lista enlazada de sesiones
- Retorna:
- - void : No devuelve valor (imprime una tabla comparativa por consola)
- Descripción:
- Reserva arreglos dinámicos paralelos para agrupar jugadores únicos por nombre. 
Recorre todas las sesiones calculando el porcentaje de victorias por sesión de cada jugador,
acumula sus resultados, imprime la efectividad promedio global y libera la memoria dinámica al finalizar.
****************************************************/
void rendimientoJugadores(ptrNodo lista)
{
	// como mucho hay MAX_JUGADORES nombres por cada sesion
	int total = contarSesiones(lista) * MAX_JUGADORES;
	string *nombres = new string[total];
	double *acum = new double[total];
	int *cantSesiones = new int[total];
	int cant = 0;
	
	while (lista != NULL)
	{
		for (int i = 0; i < lista->info.jugadoresSesion; i++)
		{
			Jugador j = lista->info.jugadores[i];
			int partidas = j.victorias + j.derrotas;
			double porcentaje = 0;
			if (partidas > 0)
			{
				porcentaje = j.victorias * 100.0 / partidas;
			}
			
			int pos = 0;
			while (pos < cant && nombres[pos] != j.nombre)
			{
				pos++;
			}
			if (pos == cant)
			{
				nombres[pos] = j.nombre;
				acum[pos] = 0;
				cantSesiones[pos] = 0;
				cant++;
			}
			acum[pos] += porcentaje;
			cantSesiones[pos]++;
		}
		lista = lista->sig;
	}
	
	cout << "\nJugador\t\tSesiones\tEfectividad promedio\n";
	for (int i = 0; i < cant; i++)
	{
		cout << nombres[i] << "\t\t" << cantSesiones[i] << "\t\t" << acum[i] / cantSesiones[i] << "%" << endl;
	}
	
	delete[] nombres;
	delete[] acum;
	delete[] cantSesiones;
}

/**
Funcion: AnalizarSesionHistoricas (opcion 6)

Parametros:
- ptrNodo lista: Lista con las sesiones guardadas.

Descripcion:
Muestra el submenu de analisis y llama a la funcion que corresponde.
*/
void AnalizarSesionHistoricas(ptrNodo lista)
{
	char op;
	do
	{
		cout << "\nAnalisis de sesiones historicas\n1.- Jugador con mas victorias por sesion\n2.- Jugador que mas fichas aposto por sesion\n3.- Desglose de tipos de apuestas por sesion\n4.- Rendimiento general de los jugadores\n0.- Volver\nIngrese una opcion: ";
		cin >> op;

		if (op >= '1' && op <= '4' && lista == NULL)
		{
			cout << "No hay sesiones cargadas.\n";
		}
		else
		{
			switch (op)
			{
			case '1':
				jugadorMasVictorias(lista);
				break;
			case '2':
				jugadorMasApostador(lista);
				break;
			case '3':
				desgloseApuestas(lista);
				break;
			case '4':
				rendimientoJugadores(lista);
				break;
			case '0':
				break;
			default:
				cout << "Error: Opcion no valida.\n";
				break;
			}
		}
	} while (op != '0');
}

/**
Funcion: CargarArchivo (opcion 7)

Parametros:
- ptrNodo &lista: Lista donde se cargan las sesiones.
- char nombreArchivo[]: Archivo donde se va a guardar al salir.

Descripcion:
Pide el nombre del archivo binario y carga sus sesiones en la lista. Si ya habia
sesiones en memoria las reemplaza (pide confirmacion). Si se pudo cargar, ese
archivo pasa a ser el que se usa para guardar al cerrar el programa.
*/
void CargarArchivo(ptrNodo &lista, char nombreArchivo[])
{
	char ruta[100];
	char conf = 's';

	cout << "Ingrese el nombre del archivo a cargar: ";
	cin >> ruta;

	if (lista != NULL)
	{
		cout << "Se van a reemplazar las sesiones que hay en memoria, continuar? s/n: ";
		cin >> conf;
	}

	if (conf == 's' || conf == 'S')
	{
		ptrNodo nueva = NULL;
		if (cargarSesiones(nueva, ruta))
		{
			liberarLista(lista);
			lista = nueva;
			strcpy(nombreArchivo, ruta);
			cout << "Se cargaron " << contarSesiones(lista) << " sesiones.\n";
		}
		else
		{
			liberarLista(nueva);
			cout << "Error: no se pudo leer el archivo.\n";
		}
	}
}

/*
Funcion: MenuPrincipal

Parametros:
- Jugador jugadores[]: Jugadores de la sesion en curso.
- int &cant: Cantidad de jugadores.

Descripcion:
Muestra el menu principal de La Ruletesca hasta que se elige salir. Las sesiones
terminadas se guardan en una lista enlazada y al salir se vuelcan al archivo
binario (el que se cargo, o uno nuevo con la fecha y hora si no se cargo ninguno).
*/

void MenuPrincipal(Jugador jugadores[], int &cant)
{
	char op;
	char conf;

	bool isSessionPlayed = false;
	bool sesionTerminada = false; // la sesion actual ya esta en la lista

	ptrNodo lista = NULL;
	char nombreArchivo[100];
	generarNombreArchivo(nombreArchivo, 100);

	// Sesion es muy grande para tenerla en el stack
	Sesion *sesionGuardada = new Sesion;
	sesionGuardada->totalGiros = 0;
	sesionGuardada->jugadoresSesion = 0;

	Numero ruleta[37];
	inicializarRuleta(ruleta);
	int condicionDeCiclo = 1;

	do
	{
		system("cls");
		cout << "La Ruletesca\n==========================\n1.- Iniciar nueva sesion de ruleta\n2.- Consultar estado de jugadores\n3.- Mostrar historial de giros\n4.- Mostrar estadasticas de la sesion\n5.- Ordenar sesiones segun cantidad de giros\n6.- Analizar sesiones historicas\n7.- Carga de Archivo\nX.- Salir de la aplicacion\nIngrese una opcion: ";
		cin >> op;
		switch (op)
		{
		case '1':
		{
			bool jugar = false;
			if (!isSessionPlayed || sesionTerminada)
			{
				delete sesionGuardada;
				sesionGuardada = new Sesion;
				inicializarSesion(*sesionGuardada, jugadores, cant);
				sesionGuardada->idSesion = maxIdSesion(lista) + 1;
				isSessionPlayed = true;
				sesionTerminada = false;
				jugar = true;
			}
			else
			{
				cout << "Ya hay una sesion en curso, desea continuarla donde la dejo? \n(1) Continuar sesion.\n(2) Cancelar.\n(3) Finalizar sesion.\n";
				int opcion = -1;
				while (opcion < 1 or opcion > 3)
				{
					cin >> opcion;
					if (opcion == 1)
					{
						jugar = true;
					}
					else if (opcion == 3)
					{
						agregarSesionAlFinal(lista, *sesionGuardada);
						sesionTerminada = true;
					}
				}
			}

			if (jugar)
			{
				condicionDeCiclo = 1;
				cicloDeJuego(ruleta, jugadores, cant, *sesionGuardada, condicionDeCiclo);
				if (condicionDeCiclo == 3)
				{
					agregarSesionAlFinal(lista, *sesionGuardada);
					sesionTerminada = true;
				}
			}
			break;
		}
		case '2':
			if (isSessionPlayed)
			{
				mostrarEstadoJugadores(sesionGuardada->jugadores, sesionGuardada->jugadoresSesion);
				cin.ignore();
				cin.get();
			}
			break;
		case '3':
			if (isSessionPlayed)
			{
				MostratHistorial(*sesionGuardada);
				cin.ignore();
				cin.get();
			}
			break;

		case '4':
			if (isSessionPlayed)
			{
				MostrarEstadistaSesion(*sesionGuardada);
				cin.ignore();
				cin.get();
			}
			break;
		case '5':
			OrdSesionGiros(lista);
			cin.ignore();
			cin.get();
			break;
		case '6':
			AnalizarSesionHistoricas(lista);
			break;
		case '7':
			CargarArchivo(lista, nombreArchivo);
			cin.ignore();
			cin.get();
			break;
		case 'x': case 'X':
			cout << "seguro? s/n : "; cin >> conf;
			if(conf=='n' || conf=='N'){
				op='o';
			}
			break;
		default:
			cout << "Error: Opcion no valida. Por favor, seleccione una opcion correcta." << endl;
    		break;
		}

	} while (op != 'x' && op != 'X');

	// si quedo una sesion pausada, tambien se guarda
	if (isSessionPlayed && !sesionTerminada && sesionGuardada->totalGiros > 0)
	{
		agregarSesionAlFinal(lista, *sesionGuardada);
	}

	if (guardarSesiones(lista, nombreArchivo))
	{
		cout << "Sesiones guardadas en " << nombreArchivo << endl;
	}
	else
	{
		cout << "Error: no se pudo guardar el archivo " << nombreArchivo << endl;
	}

	liberarLista(lista);
	delete sesionGuardada;
}
