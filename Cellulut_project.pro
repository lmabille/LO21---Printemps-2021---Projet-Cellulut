# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = Cellulut_project

QT = core gui widgets

HEADERS = \
   $$PWD/configuration.h \
   $$PWD/etat.h \
   $$PWD/etat_reseau.h \
   $$PWD/Modele.h \
   $$PWD/outils.h \
   $$PWD/simulateur.h \
   $$PWD/voisinage.h \
   chargerModele.h \
   choix_modele.h \
   config.h \
   creaconfig.h \
   fenetreconfiguration.h \
   informations.h \
   menu_config.h \
   menuprincipale_2.h \
   pugiconfig.hpp \
   pugixml.hpp \
   qSimulateur.h \
   qVoisinage.h \
   simu.h \
   taille_reseau.h\
   loadConfig.h

SOURCES = \
   $$PWD/configuration.cpp \
   $$PWD/etat.cpp \
   $$PWD/etat_reseau.cpp \
   $$PWD/main.cpp \
   $$PWD/Modele.cpp \
   $$PWD/simulateur.cpp \
   $$PWD/voisinage.cpp \
   chargerModele.cpp \
   choix_modele.cpp \
   config.cpp \
   creaconfig.cpp \
   fenetreconfiguration.cpp \
   informations.cpp \
   menu_config.cpp \
   menuprincipale_2.cpp \
   pugixml.cpp \
   qSimulateur.cpp \
   qVoisinage.cpp \
   simu.cpp \
   taille_reseau.cpp\
   loadConfig.cpp

INCLUDEPATH = \
    $$PWD/.

#DEFINES = 

FORMS += \
    MenuModele.ui \
    choix_modele.ui \
    config.ui \
    creaconfig.ui \
    fenetreconfiguration.ui \
    informations.ui \
    menu_config.ui \
    menuprincipale_2.ui \
    simu.ui \
    taille_reseau.ui

