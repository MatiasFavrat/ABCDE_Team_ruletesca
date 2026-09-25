
#include <iostream>
#include "jugador.h"
using namespace std;

/*
Funci�n: cargarJugadores

Par�metros:
- Jugador jugadores[]: Arreglo donde se van a guardar los datos de los participantes.
- int &cant: Referenciadonde seguarda la cantidad de jugadores cargados.

Retorna:
- void: No retorna ning�n valor.

Descripci�n:
Pide por teclado la cantidad de jugadore (validando que este entre 2 y 6) y
despu�s el nombre de cada uno. A todos se les asigna el pozo inicial de 2000
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
Funci�n: registrarApuesta

Par�metros:
- Jugador &j: Referencia al jugador que realiza la apuesta.
- int fichas: Cantidad de fichas que arriesga en la jugada.
- int tipo: Tipo de apuestas (1- Numero, 2- Color, 3- Par, 4- Impar).
- int numero: Numero apostado, solo se usa si tipo == 1.
- char color: Color apostado, solo se usa si tipo == 2.

Retorna:
- void: No retorna ning�n valor.

Descripci�n:
Carga una nueva apuesta en el arreglo del jugador y descuenta
de forma inmediatalas fichas arriesgadas de su saldo, ya que se recuperan (o no)
reci�n en el momento de la liquidaci�n del giro.
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
Funci�n: calcularPago

Par�metros:
- Apuesta a: Apuesta a evaluar contra el resultado del giro.
- Numero resultado: N�mero que sali� en el giro de la ruleta.

Retorna:
- int: Cantidad de fichas que corresponde devolver al jugador (0 si perdi�).

Descripci�n:
Compara la apuesta contra el resultado obtenido y calcula el pago seg�n las
tasas indicadas por la c�tedra: n�mero exacto paga36 a 1, color o paridad
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
Funci�n: liquidarApuestas

Par�metros:
- Jugador jugadores[]: Arreglo con los jugadores de la sesi�n.
- int cant: Cantidad de jugadores activos.
- Numero resultado: N�mero obtenido en el giro que se est� liquidando.

Retorna:
- void: No retorna ning�n valor.

Descripci�n:
Recorre la �ltima apuesta cargada de cada jugador, calcula el pago que le
corresponde contra el resultado del giro, acreita las fichas ganadas y
actualiza los contadores de victorias y derrotas seg�n corresponda.
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
Funci�n: mostrarEstadoJugadores

Par�metros:
- Jugador jugadores[]: Arreglo con los jugadores de la sesi�n.
- int cant: Cantidad de jugadores activos.

Retorna:
- void: No retorna ning�n valor.

Descripci�n:
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
Funci�n: hayJugadorEnQuiebra

Par�metros:
- Jugador jugadores[]: Arreglo con los jugadores de la sesi�n.
- int cant: Cantidad de jugadores activos.

Retorna:
- bool: true si alg�n jugador se qued� con 0 fichas; false en caso contrario.

Descripci�n:
Recorre el arreglo de jugadores buscando si alguno agoto por completo su
saldo de fichas, condici�n que obliga a finalizar la sesi�n en curso.
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
