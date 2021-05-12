#include "proj.h"

//Surcharge de l'état pour l'opérateur !=
bool operator!=(const Etat& e1, const Etat& e2){
    return e1.getLabel()!=e2.getLabel();
}


bool Modele::verificationEtat(){
    bool same=1;
    int i;
    Etat ** const e=fonction->getEtat();
    while(e[i]!=nullptr && ensembleEtat[i]!=nullptr){
        if (*e[i]!=*ensembleEtat[i])same=0;
    }
    if(e[i]!=nullptr && ensembleEtat[i]==nullptr)same=0;
    if(e[i]==nullptr && ensembleEtat[i]!=nullptr)same=0;

    return same;


}
