#include "AnimacionRuleta.h"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

void pausarMs(int ms) { Sleep(ms); }

const double PI     = 3.1415;
const double ASPECT = 2.0;   // una celda de consola es ~2 veces mas alta que ancha

const string CODIGO[] = {
	"\033[48;5;22m",              // FONDO
		"\033[48;5;160;38;5;231m",    // ROJO
		"\033[48;5;16;38;5;231m",     // NEGRO
		"\033[48;5;34;38;5;231m",     // VERDE (el cero)
		"\033[48;5;220;38;5;16m",     // ORO   (aro exterior)
		"\033[48;5;94;38;5;230m",     // MADERA
		"\033[48;5;137;38;5;16m",     // CONO  (centro)
		"\033[48;5;231;38;5;16m"      // BOLA
};

// ---------- Geometria (en unidades de fila) ----------
const double R_CONO    =  10;   // cono central
const double R_CASILLA = 15.0;   // fin de la corona de numeros
const double R_ORO     = 19.0;   // fin del aro dorado
const double R_MADERA  = 20.0;   // borde exterior
const double R_TEXTO   = 12.0;   // radio donde se escriben los numeros
const double R_BOLA    = 17.0;   // pista por donde corre la bola

const int ALTO  = int(2 * R_MADERA) + 1;
const int ANCHO = int(2 * R_MADERA * ASPECT) + 1;

const int RUEDA[] {
	0, 32, 15, 19,  4, 21,  2, 25, 17, 34,  6, 27, 13,
		36, 11, 30,  8, 23, 10,  5, 24, 16, 33,  1, 20, 14,
		31,  9, 22, 18, 29,  7, 28, 12, 35,  3, 26
};

const int cantCasillas = 37;
const double PASO = 2 * PI / cantCasillas; 

bool esRojo(int n) {
	bool b = false;
	if (n == 0) b = false;
	else if (n <= 10 || (n >= 19 && n <= 28)) b = (n % 2 == 1);
	else b = (n % 2 == 0);
	return b;
}

int tintaDe(int n) {
	int c;
	if (n == 0) c = 3;
	else if (esRojo(n)) {
		c = 1;
	} else {
		c = 2;
	}
	return c;
}

char glifo[ALTO][ANCHO];
int tinta[ALTO][ANCHO];

void limpiarLienzo() {
	for (int y = 0; y < ALTO; ++y)
		for (int x = 0; x < ANCHO; ++x) { glifo[y][x] = ' '; tinta[y][x] = 0; }
}

// Convierte (radio, angulo) a coordenadas de la matriz. Angulo 0 = arriba,
// creciendo en sentido horario, igual que la numeracion de la rueda real.
void aCelda(double r, double ang, int &x, int &y) {
	double cx = ANCHO / 2.0, cy = ALTO / 2.0;
	x = int(lround(cx + r * ASPECT * sin(ang)));
	y = int(lround(cy - r * cos(ang)));
}

void pintar(int x, int y, char c, int t) {
	if (x >= 0 && x < ANCHO && y >= 0 && y < ALTO) { glifo[y][x] = c; tinta[y][x] = t; }
}

// Escribe un texto centrado en (radio, angulo)
void escribir(double r, double ang, const string &txt, int t) {
	int x, y; aCelda(r, ang, x, y);
	int ini = x - int(txt.size()) / 2;
	for (size_t i = 0; i < txt.size(); ++i) pintar(ini + int(i), y, txt[i], t);
}

// ---------- Dibujo de la rueda (Estructurado) ----------
void dibujarRueda(double angBola, bool mostrarBola) {
	limpiarLienzo();
	double cx = ANCHO / 2.0;
	double cy = ALTO / 2.0;
	
	// 1) Se recorre toda la matriz y se decide el color de cada celda
	for (int y = 0; y < ALTO; ++y) {
		for (int x = 0; x < ANCHO; ++x) {
			double dx = (x - cx) / ASPECT;
			double dy = y - cy;
			double r  = sqrt(dx * dx + dy * dy);
			
			// Se reemplaza el 'continue' por una estructura condicional principal
			if (r <= R_MADERA) {
				double ang = atan2(dx, -dy);
				if (ang < 0) {
					ang += 2 * PI;
				}
				
				if (r <= R_CONO) {
					// Cono central con los brazos dorados
					bool enBrazo = false;
					for (int b = 0; b < 4; ++b) {
						if (!enBrazo) {
							double th = b * PI / 4;
							double d  = fabs(dx * (-cos(th)) - dy * sin(th));
							if (d < 0.45) {
								enBrazo = true;
							}
						}
					}
					
					if (r < 1.8) {
						pintar(x, y, ' ', 4);
					} else if (enBrazo && r > 2.6) {
						pintar(x, y, ' ', 4);
					} else {
						pintar(x, y, ' ', 6);
					}
				}
				else if (r <= R_CASILLA) {
					// Corona de casillas
					int k = int(floor(fmod(ang + PASO / 2, 2 * PI) / PASO)) % cantCasillas;
					pintar(x, y, ' ', tintaDe(RUEDA[k]));
				}
				else if (r <= R_ORO) {
					pintar(x, y, ' ', 4);
				}
				else {
					pintar(x, y, ' ', 5);
				}
			}
		}
	}
	
	// 2) Los numeros, cada uno en el centro angular de su casilla
	for (int k = 0; k < cantCasillas; ++k) {
		int n = RUEDA[k];
		escribir(R_TEXTO, k * PASO, to_string(n), tintaDe(n));
	}
	
	// 3) La bola sobre la pista dorada
	if (mostrarBola) {
		int x, y; 
		aCelda(R_BOLA, angBola, x, y);
		pintar(x, y, 'O', 7);
	}
}

void imprimirLienzo() {
	string salida;
	for (int y = 0; y < ALTO; ++y) {
		int actual = -1;
		for (int x = 0; x < ANCHO; ++x) {
			if (tinta[y][x] != actual) { 
				actual = tinta[y][x]; 
				salida += CODIGO[actual]; 
			}
			salida += glifo[y][x];
		}
		salida += CODIGO[0];
		salida += '\n';
	}
	cout << salida;
}


// ---------- Giro con animacion ----------
void girar(int target) {
	
	limpiarLienzo();
	int k = 0;  // casilla ganadora
	for(int i=0;i<37;i++) { 
		if(RUEDA[i]==target){
			k=i;
		}
	}
	
	
	double angFinal = k * PASO;
	
	const int FRAMES = 60;
	const double VUELTAS = 6.0;
	
	for (int f = 0; f <= FRAMES; ++f) {
		double t = double(f) / FRAMES;
		double falta = (1 - t) * (1 - t); // frenado suave
		
		double ang = angFinal - VUELTAS * 2 * PI * falta;
		
		dibujarRueda(ang, true);
		
		cout << "\033[H"; // cursor arriba
		imprimirLienzo();
		
		cout << "\n  girando...\n" << flush;
		pausarMs(40);
	}
	
	int n = RUEDA[k];
	
	cout << "\n  Resultado: "
		<< CODIGO[tintaDe(n)] << " "
		<< n << " "
		<< CODIGO[0] << "    ";
	
	if (n == 0) {
		cout << "verde, sin docena ni paridad\n\n";
		return;
	}
	
	cout << (esRojo(n) ? "rojo" : "negro")
		<< " | " << (n % 2 == 0 ? "par" : "impar")
		<< "\n\n";
}
