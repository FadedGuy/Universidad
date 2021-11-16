#!/bin/bash
echo "-- Affichage des droits de l'arborescence Arbo"
echo "-- Auteur(s) : Kevin Aceves"
echo "\n"

tree Arbo/ -p

getfacl Arbo/Binome/
getfacl Arbo/Binome/devoir.tex

