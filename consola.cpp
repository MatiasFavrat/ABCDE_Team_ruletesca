#include <iostream>
#include <iomanip>

#include "consola.h"

using namespace std;

#ifdef _WIN32
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00 // Windows 10 o superior
#endif
#include <windows.h>
#endif

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

/**
 * ****************************************************************************************
 * Función: inicializarConsola
 *
 * Parámetros:
 * - Ninguno.
 *
 * Retorna:
 * - void : No retorna ningún valor.
 *
 * Descripción:
 * Configura el flujo de salida estándar con formato decimal fijo y de precisión, y si se ejecuta en un entorno Windows, habilita el procesamiento de códigos de escape ANSI y maximiza la ventana de la consola. Finalmente, envía secuencias de escape para establecer el color de fondo inicial y limpiar la pantalla posicionando el cursor en el origen.
 * ****************************************************************************************
 */

void inicializarConsola()
{

	cout << fixed << setprecision(2);
#ifdef _WIN32
	// Activa la interpretacion de codigos ANSI
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	if (GetConsoleMode(hOut, &dwMode))
	{
		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(hOut, dwMode);
	}

	// Maximiza la ventana de la consola
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL)
	{
		ShowWindow(hwnd, SW_MAXIMIZE);
	}
#endif
	cout << "\033[48;5;22m" << "\033[2J\033[H";
}
