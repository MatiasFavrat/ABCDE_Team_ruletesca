#include <cstdlib>
#include <ctime>
#include "ruleta.h"
#include "AnimacionRuleta.h"

/*
Función: inicializarRuleta

Parámetros:
- Número ruleta[]: Arreglo con 37 posiciones que representa la ruleta a inicializar.

Retorna: 
- void: No retorna ningún valor.

Descripción:
Recorrelas 37 casillas de la ruleta emparejando cada índice con el color oficial
correspondiente (siguiendo el orden real de una ruleta europea) e inicializa cada
posición con inicializarNumero. Además inicializa la semilla del generador de
números aleatorios usando la hora actual.
*/

void inicializarRuleta(Numero ruleta[37]){
	char colores[37] = {'V','R','N','R','N','R','N','R','N','R','N','N','R','N','R','N','R','N','R','R','N','R','N','R','N','R','N','R','N','N','R','N','R','N','R','N','R'};
	
	for(int i = 0; i < 37; i++){
		inicializarNumero(ruleta[i], i, colores[i]);
	}
	
	srand(time(NULL));
}
	
/*
Función: girarRuleta

Parámetros:
- Numero ruleta[]:  Arreglo de 37 posiciones que representala ruleta ya inicializada.

Descripción:
Genera un índice al azar entre 0 y 36 y retorna una copia del Numero de la ruleta
que se encuentra en esa posición, simulando el resultado de un giro real.
*/
	
Numero girarRuleta(Numero ruleta[37]){
    int r = rand() % 37;
	girar(r);
    return ruleta[r];
}
