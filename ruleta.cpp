#include <cstdlib>
#include <ctime>
#include "ruleta.h"
#include "AnimacionRuleta.h"

/*
* Funcion: inicializarRuleta
* 
* Parametros:
* - Numero ruleta[]: Arreglo con 37 posiciones que representa la ruleta a inicializar.
* 
* Retorna: 
* - void: No retorna ningun valor.
* 
* Descripcion:
* Recorre las 37 casillas de la ruleta emparejando cada indice con el color oficial
* correspondiente e inicializa cada posicion con inicializarNumero.
*/
void inicializarRuleta(Numero ruleta[37]){
	char colores[37] = {'V','R','N','R','N','R','N','R','N','R','N','N','R','N','R','N','R','N','R','R','N','R','N','R','N','R','N','R','N','N','R','N','R','N','R','N','R'};
	
	for(int i = 0; i < 37; i++){
		inicializarNumero(ruleta[i], i, colores[i]);
	}
	
	srand(time(NULL));
}
	
/*
* Funcion: girarRuleta
* 
* Parametros:
* - Numero ruleta[]: Arreglo de 37 posiciones que representa la ruleta ya inicializada.
* 
* Descripcion:
* Genera un indice al azar entre 0 y 36 y retorna una copia del Numero de la ruleta.
*/

Numero girarRuleta(Numero ruleta[37]){
	int r = rand() % 37;
	girar(r);
	return ruleta[r];
}
