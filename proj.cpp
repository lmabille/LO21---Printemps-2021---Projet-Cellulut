#include <proj.h>

bool Modele::verificationEtat(){
    bool same=1;
    int i;
    const Etat **e=fonction->getEtat();
    while(e[i]!=nullptr && ensembleEtat[i]!=nullptr){
        if (*e[i]!=*ensembleEtat[i])same=0;
    }
    if(e[i]!=nullptr && ensembleEtat[i]==nullptr)same=0;
    if(e[i]==nullptr && ensembleEtat[i]!=nullptr)same=0;

    return same;


}
