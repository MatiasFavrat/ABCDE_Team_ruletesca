#include "archivo.h"
#include "Sesion.h"
#include "jugador.h"
#include "numero.h"
#include <fstream>
#include <cstring>
#include <ctime>
	
#include <iostream>
using namespace std;

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


void convertirApuestaArchivo(Apuesta origen, ApuestaArchivo &destino) {
	destino.fichasJugadas = getFichasJugadas(origen);
	destino.numeroApostado = getNumeroApostado(origen);
	destino.colorApostado = getColorApostado(origen);
	destino.tipoApuesta = getTipoApuesta(origen);
}

void convertirApuesta(ApuestaArchivo origen, Apuesta &destino) {
	setFichasJugadas(destino, origen.fichasJugadas);
	setNumeroApostado(destino, origen.numeroApostado);
	setColorApostado(destino, origen.colorApostado);
	setTipoApuesta(destino, origen.tipoApuesta);
}

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
void convertirNumeroArchivo(Numero origen, NumeroArchivo &destino) {
	destino.valor = obtenerValor(origen);
	destino.color = obtenerColor(origen);
}
  
void convertirNumero(NumeroArchivo origen,Numero &destino) {
  inicializarNumero(destino, origen.valor,origen.color);
}

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

void liberarLista(ptrNodo &lista) {
	while (lista != NULL) {
		ptrNodo aux = lista;
		lista = lista->sig;
		delete aux;
	}
}

/*
Guarda todas las sesiones de la lista en el archivo binario
(un registro por sesion). Devuelve false si no se pudo escribir.
*/
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

/*
Lee el archivo binario registro por registro y agrega cada sesion al final de la
lista. Devuelve false si no se pudo abrir o si el contenido no es valido.
*/
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

/*
Arma el nombre AAAA-MM-DD-HH-MM-SS.bin con la fecha y hora actual.
*/
void generarNombreArchivo(char *destino, int tam) {
	time_t ahora = time(NULL);
	struct tm *t = localtime(&ahora);
	strftime(destino, tam, "%Y-%m-%d-%H-%M-%S.bin", t);
}
