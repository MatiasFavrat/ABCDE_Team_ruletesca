#include "numero.h"

/**
* ****************************************************************************************
* Funci�n: inicializarNumero
*
* Par�metros:
* - Numero &n : Referencia al objeto Numero que ser� inicializado.
* - int valor : Valor num�rico que se asignar� al objeto.
* - char color : Car�cter que representa el color del n�mero.
*
* Retorna:
* - void : No retorna ning�n valor.
*
* Descripci�n:
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
	* Funci�n: obtenerValor
	*
	* Par�metros:
	* - Numero n : Objeto Numero del cual se desea obtener el valor num�rico.
	*
	* Retorna:
	* - int : Valor num�rico almacenado en el objeto Numero.
	*
	* Descripci�n:
	* Accede al atributo que contiene el valor num�rico del objeto y lo retorna.
	* ****************************************************************************************
	*/
	
	int obtenerValor(Numero n){ 
		return n.valor; 
	}
		
		/**
		* ****************************************************************************************
		* Funci�n: obtenerColor
		*
		* Par�metros:
		* - Numero n : Objeto Numero del cual se desea obtener el color.
		*
		* Retorna:
		* - char : Car�cter que representa el color almacenado en el objeto Numero.
		*
		* Descripci�n:
		* Accede al atributo que contiene el color del objeto y lo retorna.
		* ****************************************************************************************
		*/
		char obtenerColor(Numero n){ 
			return n.color; 
		}
			/**
			* ****************************************************************************************
			* Funci�n: obtenerParidad
			*
			* Par�metros:
			* - Numero n : Objeto Numero cuyo valor num�rico ser� analizado.
			*
			* Retorna:
			* - int : 0 si el valor no es par ni impar, 1 si es par y 2 si es impar.
			*
			* Descripci�n:
			* Analiza el valor num�rico almacenado en el objeto y determina su paridad,
			* retornando 1 para valores pares, 2 para valores impares y 0 cuando el valor
			* no corresponde a una de estas categor�as.
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
				
