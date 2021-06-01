#include "affichage_info.h"
#include <iostream>
#include <QLabel>


information:: information(QWidget* parent): QWidget(parent){

        num = new QSpinBox();
        num->setRange(0,255);
        num->setValue(0);

        for (size_t i=0;i<8 ;i++ ) {
            numeroBit[i]= new QLineEdit();
        }

        numl= new QLabel("Numéro");

        numeroBitl[0]= new QLabel("111");
        numeroBitl[1]= new QLabel("110");
        numeroBitl[2]= new QLabel("101");
        numeroBitl[3]= new QLabel("100");
        numeroBitl[4]= new QLabel("011");
        numeroBitl[5]= new QLabel("010");
        numeroBitl[6]= new QLabel("001");
        numeroBitl[7]= new QLabel("000");

        numc = new QVBoxLayout;
        numc->addWidget(numl);
        numc->addWidget(num);

        numeroc = new QHBoxLayout();
        numeroc->addLayout(numc);

        for (size_t i=0;i<8 ;i++ ) {
            bitc[i] = new QVBoxLayout();
            bitc[i]->addWidget(numeroBitl[i]);
            bitc[i]->addWidget(numeroBit[i]);
            numeroc->addLayout(bitc[i]);
        };



        zeroOneValidator = new QIntValidator();
        zeroOneValidator->setRange(0,1);
    this->setLayout(numeroc);


    }
