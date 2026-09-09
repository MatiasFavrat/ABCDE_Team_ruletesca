#include "numero.h"


/**
* ****************************************************************************************
* Función: inicializarNumero
*
* Parámetros:
* - Numero &n : Referencia al objeto Numero que será inicializado.
* - int valor : Valor numérico que se asignará al objeto.
* - char color : Carácter que representa el color del número.
*
* Retorna:
* - void : No retorna ningún valor.
*
* Descripción:
* Inicializa los atributos del parameto Numero con los valores recibidos y valida
* la consistencia de los datos ingresados.
* ****************************************************************************************
*/

void inicializarNumero(Numero &n, int valor, char color){
	return 0;
}

/**
* ****************************************************************************************
* Función: obtenerValor
*
* Parámetros:
* - Numero n : Objeto Numero del cual se desea obtener el valor numérico.
*
* Retorna:
* - int : Valor numérico almacenado en el objeto Numero.
*
* Descripción:
* Accede al atributo que contiene el valor numérico del objeto y lo retorna.
* ****************************************************************************************
*/

int obtenerValor(Numero n){ 
	return 0; 
}
	
/**
* ****************************************************************************************
* Función: obtenerColor
*
* Parámetros:
* - Numero n : Objeto Numero del cual se desea obtener el color.
*
* Retorna:
* - char : Carácter que representa el color almacenado en el objeto Numero.
*
* Descripción:
* Accede al atributo que contiene el color del objeto y lo retorna.
* ****************************************************************************************
*/
char obtenerColor(Numero n){
	char ColorObtenido;
	
	switch (n.color) {
	case 'N':
		ColorObtenido='N';
	case 'R':
		ColorObtenido='R';
	default:
		ColorObtenido='V'; 
	}
	
	return ColorObtenido; 
}
/**
* ****************************************************************************************
* Función: obtenerParidad
*
* Parámetros:
* - Numero n : Objeto Numero cuyo valor numérico será analizado.
*
* Retorna:
* - int : 0 si el valor no es par ni impar, 1 si es par y 2 si es impar.
*
* Descripción:
* Analiza el valor numérico almacenado en el objeto y determina su paridad,
* retornando 1 para valores pares, 2 para valores impares y 0 cuando el valor
* no corresponde a una de estas categorías.
* ****************************************************************************************
*/
int obtenerParidad(Numero n){
	int ValorParidad=0;
	
	if(n.valor%2==0){
		ValorParidad=1;	
	}else if(n.valor%3==0){
		ValorParidad=2;
	}
	
	return ValorParidad; 
}
