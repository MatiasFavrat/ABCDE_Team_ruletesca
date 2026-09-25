#include <cstdlib>
#include <ctime>
#include "ruleta.h"
#include "AnimacionRuleta.h"

/*
* Funci�n: inicializarRuleta
* 
* Par�metros:
* - N�mero ruleta[]: Arreglo con 37 posiciones que representa la ruleta a inicializar.
* 
* Retorna: 
* - void: No retorna ning�n valor.
* 
* Descripci�n:
* Recorrelas 37 casillas de la ruleta emparejando cada �ndice con el color oficial
* correspondiente (siguiendo el orden real de una ruleta europea) e inicializa cada
* posici�n con inicializarNumero. Adem�s inicializa la semilla del generador de
* n�meros aleatorios usando la hora actual.
*/

void inicializarRuleta(Numero ruleta[37]){
	char colores[37] = {'V','R','N','R','N','R','N','R','N','R','N','N','R','N','R','N','R','N','R','R','N','R','N','R','N','R','N','R','N','N','R','N','R','N','R','N','R'};
	
	for(int i = 0; i < 37; i++){
		inicializarNumero(ruleta[i], i, colores[i]);
	}
	
	srand(time(NULL));
}
	
/*
* Funci�n: girarRuleta
* 
* Par�metros:
* - Numero ruleta[]:  Arreglo de 37 posiciones que representala ruleta ya inicializada.
* 
* Descripci�n:
* Genera un �ndice al azar entre 0 y 36 y retorna una copia del Numero de la ruleta
* que se encuentra en esa posici�n, simulando el resultado de un giro real.
*/
	
Numero girarRuleta(Numero ruleta[37]){
    int r = rand() % 37;
	girar(r);
    return ruleta[r];
}
