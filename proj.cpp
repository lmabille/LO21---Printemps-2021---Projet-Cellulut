#include "proj.h"

//Surcharge de l'état pour l'opérateur !=
bool operator!=(const Etat& e1, const Etat& e2){
    return e1.getLabel()!=e2.getLabel();
}
