#include "archivo.h"
#include "Sesion.h"
#include "jugador.h"
#include "numero.h"
#include <fstream>
#include <cstring>
#include <ctime>
	
#include <iostream>
using namespace std;
/****************************************************
- Función: sesionValida
- Parámetros:
- - Sesion s : Estructura de sesión en memoria a validar
- Retorna:
- - bool : true si todos los límites de la sesión son válidos, false en caso contrario
- Descripción:
- Comprueba que la cantidad de giros y de jugadores esté dentro de los rangos máximos permitidos, y luego recorre los jugadores verificando que el tamaño lógico de sus apuestas no exceda MAX_APUESTAS.
****************************************************/
bool sesionValida(Sesion s) {
	bool valida = true;
	
	if (s.totalGiros < 0 || s.totalGiros > MAX_JUGADAS) {
		valida = false;
	}
	
	if (s.jugadoresSesion < 0 ||
		s.jugadoresSesion > MAX_JUGADORES) {
		valida = false;
	}
	
	for (int i = 0; valida && i < s.jugadoresSesion; i++) {
		int tl = getTlApuestas(s.jugadores[i]);
		
		if (tl < 0 || tl > MAX_APUESTAS) {
			valida = false;
		}
	}
	
	return valida;
}

/****************************************************
- Función: sesionArchivoValida
- Parámetros:
- - SesionArchivo s : Estructura de sesión leída desde archivo binario a validar
- Retorna:
- - bool : true si los datos y tamaños lógicos del registro son coherentes, false si están corruptos o fuera de rango
- Descripción:
- Verifica que totalGiros, jugadoresSesion y la cantidad de apuestas de cada jugador registrado en la estructura de archivo se encuentren dentro de los límites establecidos.
****************************************************/
bool sesionArchivoValida(SesionArchivo s) {
	bool valida = true;
	
	if (s.totalGiros < 0 || s.totalGiros > MAX_JUGADAS) {
		valida = false;
	}
	
	if (s.jugadoresSesion < 0 ||
		s.jugadoresSesion > MAX_JUGADORES) {
		valida = false;
	}
	
	for (int i = 0; valida && i < s.jugadoresSesion; i++) {
		if (s.jugadores[i].tlApuestas < 0 ||
			s.jugadores[i].tlApuestas > MAX_APUESTAS) {
			valida = false;
		}
	}
	
	return valida;
}

/****************************************************
- Función: convertirApuestaArchivo
- Parámetros:
- - Apuesta origen : Estructura de apuesta en memoria
- - ApuestaArchivo &destino : Referencia a la estructura de apuesta serializable para archivo
- Retorna:
- - void : No devuelve valor (modifica destino por referencia)
- Descripción:
- Extrae los campos de la apuesta en memoria mediante sus funciones getter y los copia directamente en los atributos correspondientes de ApuestaArchivo.
****************************************************/
void convertirApuestaArchivo(Apuesta origen, ApuestaArchivo &destino) {
	destino.fichasJugadas = getFichasJugadas(origen);
	destino.numeroApostado = getNumeroApostado(origen);
	destino.colorApostado = getColorApostado(origen);
	destino.tipoApuesta = getTipoApuesta(origen);
}

/****************************************************
- Función: convertirApuesta
- Parámetros:
- - ApuestaArchivo origen : Estructura de apuesta proveniente de archivo
- - Apuesta &destino : Referencia a la estructura de apuesta en memoria a rellenar
- Retorna:
- - void : No devuelve valor (modifica destino por referencia)
- Descripción:
- Toma los valores almacenados en ApuestaArchivo y los carga en la estructura Apuesta utilizando sus funciones setter.
****************************************************/
void convertirApuesta(ApuestaArchivo origen, Apuesta &destino) {
	setFichasJugadas(destino, origen.fichasJugadas);
	setNumeroApostado(destino, origen.numeroApostado);
	setColorApostado(destino, origen.colorApostado);
	setTipoApuesta(destino, origen.tipoApuesta);
}

/****************************************************
- Función: convertirJugadorArchivo
- Parámetros:
- - Jugador origen : Estructura de jugador en memoria
- - JugadorArchivo &destino : Referencia a la estructura de jugador para almacenamiento binario
- Retorna:
- - void : No devuelve valor (modifica destino por referencia)
- Descripción:
- Convierte el nombre de std::string a arreglo de caracteres de tamaño fijo asegurando el carácter nulo final, copia las estadísticas numéricas y transforma cada apuesta activa mediante convertirApuestaArchivo.
****************************************************/
void convertirJugadorArchivo(Jugador origen, JugadorArchivo &destino) {
   JugadorArchivo aux = {};
   
   string nombre = getNombre(origen);
   
   strncpy(aux.nombre, nombre.c_str(), MAX_NOMBRE_ARCHIVO - 1);
   aux.nombre[MAX_NOMBRE_ARCHIVO - 1] = '\0';
   aux.fichas = getFichas(origen);
   aux.tlApuestas = getTlApuestas(origen);
   aux.victorias = getVictorias(origen);
   aux.derrotas = getDerrotas(origen);
   
   for (int i = 0; i < aux.tlApuestas; i++) {
	   Apuesta ap = getApuestaEnPosicion(origen, i);
	   convertirApuestaArchivo(ap, aux.apuestas[i]);
   }
   
   destino = aux;
}

/****************************************************
- Función: convertirJugador
- Parámetros:
- - JugadorArchivo origen : Estructura de jugador leída desde archivo
- - Jugador &destino : Referencia a la estructura de jugador en memoria a construir
- Retorna:
- - void : No devuelve valor (modifica destino por referencia)
- Descripción:
- Asigna los atributos básicos y convierte el arreglo char de nombre a std::string mediante setters. Luego recorre y transforma cada apuesta del registro guardándola en el arreglo del jugador.
****************************************************/
void convertirJugador(JugadorArchivo origen, Jugador &destino) {
	setNombre(destino, string(origen.nombre));
	setFichas(destino, origen.fichas);
	setVictorias(destino, origen.victorias);
	setDerrotas(destino, origen.derrotas);
	setTlApuestas(destino, origen.tlApuestas);
	
	for (int i = 0; i < origen.tlApuestas; i++) {
		Apuesta ap = {};
		
		convertirApuesta(origen.apuestas[i], ap);
		
		setApuestaEnPosicion(destino, ap, i);
	}
}

/****************************************************
- Función: convertirNumeroArchivo
- Parámetros:
- - Numero origen : Estructura de número de ruleta en memoria
- - NumeroArchivo &destino : Referencia a la estructura de número para archivo
- Retorna:
- - void : No devuelve valor (modifica destino por referencia)
- Descripción:
- Obtiene el valor y el color del número en memoria y los asigna a los campos de la estructura NumeroArchivo.
****************************************************/
void convertirNumeroArchivo(Numero origen, NumeroArchivo &destino) {
	destino.valor = obtenerValor(origen);
	destino.color = obtenerColor(origen);
}

/****************************************************
- Función: convertirNumero
- Parámetros:
- - NumeroArchivo origen : Estructura de número leída desde archivo
- - Numero &destino : Referencia a la estructura de número en memoria a inicializar
- Retorna:
- - void : No devuelve valor (modifica destino por referencia)
- Descripción:
- Inicializa la estructura Numero en memoria a partir del valor y color almacenados en NumeroArchivo.
****************************************************/
void convertirNumero(NumeroArchivo origen,Numero &destino) {
  inicializarNumero(destino, origen.valor,origen.color);
}

/****************************************************
- Función: convertirSesionArchivo
- Parámetros:
- - Sesion origen : Estructura de sesión en memoria
- - SesionArchivo &destino : Referencia a la estructura de sesión serializable para archivo
- Retorna:
- - void : No devuelve valor (modifica destino por referencia)
- Descripción:
- Copia los metadatos de la sesión en una estructura auxiliar limpia, convierte todo el historial de números tirados y transforma cada jugador activo a su formato de archivo antes de asignarlo a destino.
****************************************************/
void convertirSesionArchivo(Sesion origen, SesionArchivo &destino) {
   SesionArchivo aux = {};
   
   aux.idSesion = origen.idSesion;
   aux.totalGiros = origen.totalGiros;
   aux.jugadoresSesion = origen.jugadoresSesion;
   
   for (int i = 0; i < aux.totalGiros; i++) {
	   convertirNumeroArchivo(origen.historial[i], aux.historial[i]);
   }
   
   for (int i = 0; i < aux.jugadoresSesion; i++) {
	   convertirJugadorArchivo(origen.jugadores[i], aux.jugadores[i]);
   }
   
   destino = aux;
}

/****************************************************
- Función: convertirSesion
- Parámetros:
- - SesionArchivo origen : Estructura de sesión leída desde archivo
- - Sesion &destino : Referencia a la estructura de sesión en memoria a reconstruir
- Retorna:
- - void : No devuelve valor (modifica destino por referencia)
- Descripción:
- Restaura el identificador y contadores de la sesión, y reconstruye secuencialmente los arreglos de historial de números y jugadores en memoria mediante sus respectivas funciones de conversión.
****************************************************/
void convertirSesion(SesionArchivo origen, Sesion &destino) {
   destino.idSesion = origen.idSesion;
   destino.totalGiros = origen.totalGiros;
   destino.jugadoresSesion = origen.jugadoresSesion;
   
   for (int i = 0; i < origen.totalGiros; i++) {
	   convertirNumero(origen.historial[i], destino.historial[i]);
   }
   
   for (int i = 0; i < origen.jugadoresSesion; i++) {
	   convertirJugador(origen.jugadores[i],destino.jugadores[i]);
   }
}

/****************************************************
- Función: liberarLista
- Parámetros:
- - ptrNodo &lista : Referencia al puntero inicial de la lista enlazada de sesiones
- Retorna:
- - void : No devuelve valor (deja el puntero lista en NULL)
- Descripción:
- Recorre toda la lista enlazada nodo por nodo guardando una referencia auxiliar al nodo actual,
avanzando el puntero principal y liberando la memoria dinámica de cada nodo con delete.
****************************************************/
void liberarLista(ptrNodo &lista) {
	while (lista != NULL) {
		ptrNodo aux = lista;
		lista = lista->sig;
		delete aux;
	}
}

/****************************************************
- Función: guardarSesiones
- Parámetros:
- - ptrNodo lista : Puntero al inicio de la lista enlazada de sesiones
- - const char *nombreArchivo : Ruta o nombre del archivo binario de destino
- Retorna:
- - bool : true si el archivo se abrió y todas las sesiones válidas se escribieron correctamente, false ante algún error
- Descripción:
- Abre el archivo binario en modo truncado y reserva un buffer dinámico de SesionArchivo.
Recorre la lista validando cada sesión, convirtiéndola al formato de archivo y escribiendo el bloque de bytes en disco.
****************************************************/
bool guardarSesiones(ptrNodo lista, const char *nombreArchivo) {
	bool ok = true;
	ofstream archivo(nombreArchivo, ios::binary | ios::trunc);
	
	if (!archivo) {
		ok = false;
	} else {
		SesionArchivo *buffer = new SesionArchivo;
		
		while (ok && lista != NULL) {
			if (sesionValida(lista->info)) {
				convertirSesionArchivo(lista->info, *buffer);
				archivo.write(reinterpret_cast<const char *>(buffer), sizeof(SesionArchivo));
				if (!archivo) {
					ok = false;
				}
			}
			lista = lista->sig;
		}
		
		delete buffer;
		archivo.close();
	}
	
	return ok;
}

/****************************************************
- Función: cargarSesiones
- Parámetros:
- - ptrNodo &lista : Referencia al puntero inicial de la lista donde se cargarán las sesiones
- - const char *nombreArchivo : Ruta o nombre del archivo binario de origen
- Retorna:
- - bool : true si la lectura completa y validación de todos los registros fue exitosa, false si falló la apertura, hubo datos corruptos o bytes residuales
- Descripción:
- Abre el archivo binario en modo lectura y lee bloques del tamaño de SesionArchivo.
Valida cada registro, lo convierte a estructura Sesion y lo inserta al final de la lista.
Al terminar verifica que no hayan quedado bytes incompletos sin leer.
****************************************************/
bool cargarSesiones(ptrNodo &lista, const char *nombreArchivo) {
	bool ok = true;
	ifstream archivo(nombreArchivo, ios::binary);
	
	if (!archivo) {
		ok = false;
	} else {
		SesionArchivo *buffer = new SesionArchivo;
		Sesion *sesion = new Sesion;
		
		while (ok && archivo.read(reinterpret_cast<char *>(buffer), sizeof(SesionArchivo))) {
			if (sesionArchivoValida(*buffer)) {
				convertirSesion(*buffer, *sesion);
				agregarSesionAlFinal(lista, *sesion);
			} else {
				ok = false;
			}
		}
		
		// si sobraron bytes el archivo esta incompleto
		if (ok && archivo.gcount() > 0) {
			ok = false;
		}
		
		delete sesion;
		delete buffer;
		archivo.close();
	}
	
	return ok;
}

/****************************************************
- Función: generarNombreArchivo
- Parámetros:
- - char *destino : Arreglo de caracteres donde se almacenará el nombre generado
- - int tam : Tamaño máximo del arreglo destino
- Retorna:
- - void : No devuelve valor (escribe la cadena formateada en destino)
- Descripción:
- Obtiene la marca de tiempo actual del sistema, la descompone en hora local y formatea una cadena con el patrón AAAA-MM-DD-HH-MM-SS.bin dentro del buffer recibido.
****************************************************/
void generarNombreArchivo(char *destino, int tam) {
	time_t ahora = time(NULL);
	struct tm *t = localtime(&ahora);
	strftime(destino, tam, "%Y-%m-%d-%H-%M-%S.bin", t);
}
