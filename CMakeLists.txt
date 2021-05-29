cmake_minimum_required(VERSION 3.17)
project(LO21---Printemps-2021---Projet-Cellulut)

set(CMAKE_CXX_STANDARD 14)

add_executable(LO21---Printemps-2021---Projet-Cellulut main.cpp etat.cpp configuration.h etat.h voisinage.cpp voisinage.h chargerModele.cpp test.xml chargerModele.h configuration.cpp chargerModele.h etat_reseau.cpp etat_reseau.h Modele.h Modele.cpp outils.h pugixml.hpp pugixml.cpp pugiconfig.hpp simulateur.cpp simulateur.h )