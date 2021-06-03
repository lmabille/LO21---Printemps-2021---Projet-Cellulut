# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = test_auto_celle_1

QT = core gui widgets

HEADERS = \
   $$PWD/chargerModele.h \
   $$PWD/configuration.h \
   $$PWD/etat.h \
   $$PWD/etat_reseau.h \
   $$PWD/Modele.h \
   $$PWD/outils.h \
   $$PWD/pugiconfig.hpp \
   $$PWD/pugixml.hpp \
   $$PWD/simulateur.h \
   $$PWD/voisinage.h \
   affichage_info.h

SOURCES = \
   $$PWD/chargerModele.cpp \
   $$PWD/configuration.cpp \
   $$PWD/etat.cpp \
   $$PWD/etat_reseau.cpp \
   $$PWD/main.cpp \
   $$PWD/Modele.cpp \
   $$PWD/pugixml.cpp \
   $$PWD/simulateur.cpp \
   $$PWD/voisinage.cpp \
   affichage_info.cpp

INCLUDEPATH = \
    $$PWD/.

#DEFINES = 

FORMS += \
    mainwindow.ui

