#include <iostream>
#include "numero.h"
#include "ruleta.h"
#include "jugador.h"
using namespace std;

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
