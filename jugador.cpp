
#include <iostream>
#include "jugador.h"
using namespace std;

/*
Funciï¿½n: cargarJugadores

Parï¿½metros:
- Jugador jugadores[]: Arreglo donde se van a guardar los datos de los participantes.
- int &cant: Referenciadonde seguarda la cantidad de jugadores cargados.

Retorna:
- void: No retorna ningï¿½n valor.

Descripciï¿½n:
Pide por teclado la cantidad de jugadore (validando que este entre 2 y 6) y
despuï¿½s el nombre de cada uno. A todos se les asigna el pozo inicial de 2000
fichas y se reseteansus contadores de apuestas, victorias y derrotas.
*/

void cargarJugadores(Jugador jugadores[], int &cant)
{
	do
	{
		cout << "Cantidad de jugadores: " << endl;
		cin >> cant;
	} while (cant < MIN_JUGADORES || cant > MAX_JUGADORES);

	for (int i = 0; i < cant; i++)
	{
		cout << "Nombre jugador " << i + 1 << ": ";
		cin >> jugadores[i].nombre;

		jugadores[i].fichas = FICHAS_INICIALES;
		jugadores[i].tlApuestas = 0;
		jugadores[i].victorias = 0;
		jugadores[i].derrotas = 0;
	}
}

/*
Funciï¿½n: registrarApuesta

Parï¿½metros:
- Jugador &j: Referencia al jugador que realiza la apuesta.
- int fichas: Cantidad de fichas que arriesga en la jugada.
- int tipo: Tipo de apuestas (1- Numero, 2- Color, 3- Par, 4- Impar).
- int numero: Numero apostado, solo se usa si tipo == 1.
- char color: Color apostado, solo se usa si tipo == 2.

Retorna:
- void: No retorna ningï¿½n valor.

Descripciï¿½n:
Carga una nueva apuesta en el arreglo del jugador y descuenta
de forma inmediatalas fichas arriesgadas de su saldo, ya que se recuperan (o no)
reciï¿½n en el momento de la liquidaciï¿½n del giro.
*/

void registrarApuesta(Jugador &j, int fichas, int tipo, int numero, char color)
{
	Apuesta a;
	a.fichasJugadas = fichas;
	a.tipoApuesta = tipo;
	a.numeroApostado = numero;
	a.colorApostado = color;

	j.apuestas[j.tlApuestas] = a;
	j.tlApuestas++;

	j.fichas = j.fichas - fichas;
}

/*
Funciï¿½n: calcularPago

Parï¿½metros:
- Apuesta a: Apuesta a evaluar contra el resultado del giro.
- Numero resultado: Nï¿½mero que saliï¿½ en el giro de la ruleta.

Retorna:
- int: Cantidad de fichas que corresponde devolver al jugador (0 si perdiï¿½).

Descripciï¿½n:
Compara la apuesta contra el resultado obtenido y calcula el pago segï¿½n las
tasas indicadas por la cï¿½tedra: nï¿½mero exacto paga36 a 1, color o paridad
pagan 2 a 1. Si la apuestano acierta, retorna 0.
*/

int calcularPago(Apuesta a, Numero resultado)
{
	int pago = 0;

	switch (a.tipoApuesta)
	{
	case 1:
		if (a.numeroApostado == obtenerValor(resultado))
		{
			pago = a.fichasJugadas * 36;
		}
		break;
	case 2:
		if (a.colorApostado == obtenerColor(resultado))
		{
			pago = a.fichasJugadas * 2;
		}
		break;
	case 3:
		if (obtenerParidad(resultado) == 1)
		{
			pago = a.fichasJugadas * 2;
		}
		break;
	case 4:
		if (obtenerParidad(resultado) == 2)
		{
			pago = a.fichasJugadas * 2;
		}
		break;
	}

	return pago;
}

/*
Funciï¿½n: liquidarApuestas

Parï¿½metros:
- Jugador jugadores[]: Arreglo con los jugadores de la sesiï¿½n.
- int cant: Cantidad de jugadores activos.
- Numero resultado: Nï¿½mero obtenido en el giro que se estï¿½ liquidando.

Retorna:
- void: No retorna ningï¿½n valor.

Descripciï¿½n:
Recorre la ï¿½ltima apuesta cargada de cada jugador, calcula el pago que le
corresponde contra el resultado del giro, acreita las fichas ganadas y
actualiza los contadores de victorias y derrotas segï¿½n corresponda.
*/

void liquidarApuestas(Jugador jugadores[], int cant, Numero resultado)
{
	for (int i = 0; i < cant; i++)
	{
		int ultima = jugadores[i].tlApuestas - 1;
		Apuesta a = jugadores[i].apuestas[ultima];
		int pago = calcularPago(a, resultado);

		if (pago > 0)
		{
			jugadores[i].fichas = jugadores[i].fichas + pago;
			jugadores[i].victorias++;
		}
		else
		{
			jugadores[i].derrotas++;
		}
	}
}

/*
Funciï¿½n: mostrarEstadoJugadores

Parï¿½metros:
- Jugador jugadores[]: Arreglo con los jugadores de la sesiï¿½n.
- int cant: Cantidad de jugadores activos.

Retorna:
- void: No retorna ningï¿½n valor.

Descripciï¿½n:
Imprime en formato tabular el nombre, la cantidad de fichas actuales, las
victorias y las derrotas de cada uno de los jugadores recibidos.
*/

void mostrarEstadoJugadores(Jugador jugadores[], int cant)
{
	cout << endl;
	cout << "Nombre\t\tFichas\tDerrotas" << endl;

	for (int i = 0; i < cant; i++)
	{
		cout << jugadores[i].nombre << "\t\t"
			 << jugadores[i].fichas << "\t"
			 << jugadores[i].victorias << "\t\t"
			 << jugadores[i].derrotas << endl;
	}

	cout << endl;
}

/*
Funciï¿½n: hayJugadorEnQuiebra

Parï¿½metros:
- Jugador jugadores[]: Arreglo con los jugadores de la sesiï¿½n.
- int cant: Cantidad de jugadores activos.

Retorna:
- bool: true si algï¿½n jugador se quedï¿½ con 0 fichas; false en caso contrario.

Descripciï¿½n:
Recorre el arreglo de jugadores buscando si alguno agoto por completo su
saldo de fichas, condiciï¿½n que obliga a finalizar la sesiï¿½n en curso.
*/

bool hayJugadorEnQuiebra(Jugador jugadores[], int cant)
{
	bool quiebra = false;
	int i = 0;

	while (i < cant && !quiebra)
	{
		if (jugadores[i].fichas <= 0)
		{
			quiebra = true;
		}
		i++;
	}

	return quiebra;
}

/****************************************************
- Función: getNombre
- Parámetros:
- - Jugador j : Estructura con los datos del jugador
- Retorna:
- - string : Nombre del jugador
- Descripción:
- Accede directamente al campo nombre de la estructura Jugador y devuelve su valor.
****************************************************/
string getNombre(Jugador j){
	return j.nombre;
}

/****************************************************
- Función: getFichas
- Parámetros:
- - Jugador j : Estructura con los datos del jugador
- Retorna:
- - int : Cantidad actual de fichas disponibles del jugador
- Descripción:
- Accede directamente al campo fichas de la estructura Jugador y devuelve su valor.
****************************************************/
int getFichas(Jugador j){
	return j.fichas;
}

/****************************************************
- Función: getFichasJugadas
- Parámetros:
- - Apuesta a : Estructura con los datos de la apuesta
- Retorna:
- - int : Cantidad de fichas apostadas en esa jugada
- Descripción:
- Accede directamente al campo fichasJugadas de la estructura Apuesta y devuelve su valor.
****************************************************/
int getFichasJugadas(Apuesta a){
	return a.fichasJugadas;
}

/****************************************************
- Función: getNumeroApostado
- Parámetros:
- - Apuesta a : Estructura con los datos de la apuesta
- Retorna:
- - int : Número seleccionado en la apuesta
- Descripción:
- Accede directamente al campo numeroApostado de la estructura Apuesta y devuelve su valor.
****************************************************/
int getNumeroApostado(Apuesta a){
	return a.numeroApostado;
}

/****************************************************
- Función: getColorApostado
- Parámetros:
- - Apuesta a : Estructura con los datos de la apuesta
- Retorna:
- - char : Carácter que representa el color elegido en la apuesta
- Descripción:
- Accede directamente al campo colorApostado de la estructura Apuesta y devuelve su valor.
****************************************************/
char getColorApostado(Apuesta a){
	return a.colorApostado;
}

/****************************************************
- Función: getTipoApuesta
- Parámetros:
- - Apuesta a : Estructura con los datos de la apuesta
- Retorna:
- - int : Código numérico que identifica el tipo de apuesta realizada
- Descripción:
- Accede directamente al campo tipoApuesta de la estructura Apuesta y devuelve su valor.
****************************************************/
int getTipoApuesta(Apuesta a){
	return a.tipoApuesta;
}

/****************************************************
- Función: getApuestaEnPosicion
- Parámetros:
- - Jugador j : Estructura con los datos del jugador
- - int pos : Índice dentro del arreglo de apuestas del jugador
- Retorna:
- - Apuesta : Estructura de la apuesta ubicada en la posición indicada
- Descripción:
- Indexa directamente el arreglo interno apuestas del jugador en la posición pos y retorna una copia del elemento.
****************************************************/
Apuesta getApuestaEnPosicion(Jugador j, int pos){
	return j.apuestas[pos];
}

/****************************************************
- Función: getTlApuestas
- Parámetros:
- - Jugador j : Estructura con los datos del jugador
- Retorna:
- - int : Tamaño lógico (cantidad actual) de apuestas registradas del jugador
- Descripción:
- Accede directamente al campo tlApuestas de la estructura Jugador y devuelve su valor.
****************************************************/
int getTlApuestas(Jugador j){
	return j.tlApuestas;
}

/****************************************************
- Función: getVictorias
- Parámetros:
- - Jugador j : Estructura con los datos del jugador
- Retorna:
- - int : Cantidad total de victorias acumuladas por el jugador
- Descripción:
- Accede directamente al campo victorias de la estructura Jugador y devuelve su valor.
****************************************************/
int getVictorias(Jugador j){
	return j.victorias;
}

/****************************************************
- Función: getDerrotas
- Parámetros:
- - Jugador j : Estructura con los datos del jugador
- Retorna:
- - int : Cantidad total de derrotas acumuladas por el jugador
- Descripción:
- Accede directamente al campo derrotas de la estructura Jugador y devuelve su valor.
****************************************************/
int getDerrotas(Jugador j){
	return j.derrotas;
}

/****************************************************
- Función: setFichasJugadas
- Parámetros:
- - Apuesta& a : Referencia a la estructura Apuesta a modificar
- - int fichas : Nueva cantidad de fichas jugadas a asignar
- Retorna:
- - void : No devuelve valor (modifica la estructura por referencia)
- Descripción:
- Asigna directamente el valor recibido al campo fichasJugadas de la apuesta.
****************************************************/
void setFichasJugadas(Apuesta& a, int fichas){
	a.fichasJugadas = fichas;
}

/****************************************************
- Función: setNumeroApostado
- Parámetros:
- - Apuesta& a : Referencia a la estructura Apuesta a modificar
- - int numero : Nuevo número apostado a asignar
- Retorna:
- - void : No devuelve valor (modifica la estructura por referencia)
- Descripción:
- Asigna directamente el valor recibido al campo numeroApostado de la apuesta.
****************************************************/
void setNumeroApostado(Apuesta& a, int numero){
	a.numeroApostado = numero;
}

/****************************************************
- Función: setColorApostado
- Parámetros:
- - Apuesta& a : Referencia a la estructura Apuesta a modificar
- - char color : Nuevo carácter de color a asignar
- Retorna:
- - void : No devuelve valor (modifica la estructura por referencia)
- Descripción:
- Asigna directamente el valor recibido al campo colorApostado de la apuesta.
****************************************************/
void setColorApostado(Apuesta& a, char color){
	a.colorApostado = color;
}

/****************************************************
- Función: setTipoApuesta
- Parámetros:
- - Apuesta& a : Referencia a la estructura Apuesta a modificar
- - int tipo : Nuevo código de tipo de apuesta a asignar
- Retorna:
- - void : No devuelve valor (modifica la estructura por referencia)
- Descripción:
- Asigna directamente el valor recibido al campo tipoApuesta de la apuesta.
****************************************************/
void setTipoApuesta(Apuesta& a, int tipo){
	a.tipoApuesta = tipo;
}

/****************************************************
- Función: setNombre
- Parámetros:
- - Jugador& j : Referencia a la estructura Jugador a modificar
- - string nombre : Nuevo nombre a asignar al jugador
- Retorna:
- - void : No devuelve valor (modifica la estructura por referencia)
- Descripción:
- Asigna directamente la cadena recibida al campo nombre del jugador.
****************************************************/
void setNombre(Jugador& j, string nombre){
	j.nombre = nombre;
}

/****************************************************
- Función: setFichas
- Parámetros:
- - Jugador& j : Referencia a la estructura Jugador a modificar
- - int fichas : Nueva cantidad de fichas a asignar al jugador
- Retorna:
- - void : No devuelve valor (modifica la estructura por referencia)
- Descripción:
- Asigna directamente el valor recibido al campo fichas del jugador.
****************************************************/
void setFichas(Jugador& j, int fichas){
	j.fichas = fichas;
}

/****************************************************
- Función: setApuestaEnPosicion
- Parámetros:
- - Jugador& j : Referencia a la estructura Jugador a modificar
- - Apuesta ap : Estructura de apuesta que se desea guardar
- - int pos : Índice del arreglo donde se almacenará la apuesta
- Retorna:
- - void : No devuelve valor (modifica el arreglo interno por referencia)
- Descripción:
- Sobrescribe la posición pos del arreglo apuestas del jugador con la estructura ap recibida.
****************************************************/
void setApuestaEnPosicion(Jugador& j, Apuesta ap, int pos){
	j.apuestas[pos] = ap;
}

/****************************************************
- Función: setTlApuestas
- Parámetros:
- - Jugador& j : Referencia a la estructura Jugador a modificar
- - int tl : Nuevo tamaño lógico de apuestas a asignar
- Retorna:
- - void : No devuelve valor (modifica la estructura por referencia)
- Descripción:
- Asigna directamente el valor recibido al campo tlApuestas del jugador.
****************************************************/
void setTlApuestas(Jugador& j, int tl){
	j.tlApuestas = tl;
}

/****************************************************
- Función: setVictorias
- Parámetros:
- - Jugador& j : Referencia a la estructura Jugador a modificar
- - int victorias : Nueva cantidad de victorias a asignar
- Retorna:
- - void : No devuelve valor (modifica la estructura por referencia)
- Descripción:
- Asigna directamente el valor recibido al campo victorias del jugador.
****************************************************/
void setVictorias(Jugador& j, int victorias){
	j.victorias = victorias;
}

/****************************************************
- Función: setDerrotas
- Parámetros:
- - Jugador& j : Referencia a la estructura Jugador a modificar
- - int derrotas : Nueva cantidad de derrotas a asignar
- Retorna:
- - void : No devuelve valor (modifica la estructura por referencia)
- Descripción:
- Asigna directamente el valor recibido al campo derrotas del jugador.
****************************************************/
void setDerrotas(Jugador& j, int derrotas){
	j.derrotas = derrotas;
}

/****************************************************
- Función: agregarApuesta
- Parámetros:
- - Jugador& j : Referencia a la estructura Jugador a la que se agregará la apuesta
- - Apuesta ap : Estructura con los datos de la nueva apuesta a insertar
- Retorna:
- - void : No devuelve valor (modifica el arreglo de apuestas y su tamaño lógico)
- Descripción:
- Verifica que el tamaño lógico de apuestas sea menor al límite máximo (MAX_APUESTAS). Si hay espacio disponible, inserta la apuesta al final del arreglo e incrementa tlApuestas en una unidad.
****************************************************/
void agregarApuesta(Jugador& j, Apuesta ap){
	if (j.tlApuestas < MAX_APUESTAS){
		j.apuestas[j.tlApuestas] = ap;
		j.tlApuestas++;
	}
}
