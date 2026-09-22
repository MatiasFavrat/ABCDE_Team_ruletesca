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
	if (valor < 0 || valor > 36) { 
		valor = 0;
	}
	
	if (valor == 0) {
		color = 'V'; 
	} else if (color != 'R' && color != 'N') {
		color = 'N';
	};
	
	n.valor = valor;
	n.color = color;
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
		return n.valor; 
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
			return n.color; 
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
				int paridad;
				
				if (n.valor == 0) {
					paridad = 0;
				} else if (n.valor % 2 == 0) {
					paridad = 1;
				} else {
					paridad = 2;
				}
				
				return paridad; 
			}
				
