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
   informations.h \
   menu_config.h \
   menuprincipale_2.h \
   pugiconfig.hpp \
   pugixml.hpp \
   qSimulateur.h \
   taille_reseau.h

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
   informations.cpp \
   menu_config.cpp \
   menuprincipale_2.cpp \
   pugixml.cpp \
   qSimulateur.cpp \
   taille_reseau.cpp

INCLUDEPATH = \
    $$PWD/.

#DEFINES = 

FORMS += \
    MenuModele.ui \
    choix_modele.ui \
    config.ui \
    informations.ui \
    menu_config.ui \
    menuprincipale_2.ui \
    taille_reseau.ui

