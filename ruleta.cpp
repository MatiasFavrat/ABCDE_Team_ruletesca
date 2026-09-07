
#include <cstdlib>
#include <ctime>
#include "ruleta.h"

void inicializarRuleta(Numero ruleta[37]){
    char colores[37] = {'V','R','N','R','N','R','N','R','N','R','N','N','R','N','R','N','R','N','R','R','N','R','N','R','N','R','N','R','N','N','R','N','R','N','R','N','R'};

    for(int i=0;i<37;i++){
        inicializarNumero(ruleta[i], i, colores[i]);
    }

    srand(time(NULL));
}

Numero girarRuleta(Numero ruleta[37]){
    int r = rand() % 37;
    return ruleta[r];
}
