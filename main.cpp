#include <iostream>
#include "numero.h"
#include "ruleta.h"
#include "jugador.h"
#include "MenuPrincipal.h"

using namespace std;

const bool InicioSesion=false;

int main() {
	
	Numero nums[37];
	inicializarRuleta(nums);
	bool i=1;
	while(i){
		
		cin >> i;
		girarRuleta(nums);	
	}
	
    return 0;
}
