#!/bin/bash
echo "| Script de creation arbo ACL"
echo "|   Auteur(s) : Kevin Aceves"
echo ""
echo "-- Nettoyage du dossier courant"
rm -fr ./Arbo

echo "-- Creation du repertoire arbo ACL"
mkdir ./Arbo
cd Arbo/
mkdir Binome Connaisseurs Depot Public Public/images Public/medias Secret
touch Binome/devoir.tex Connaisseurs/reponse746.txt Public/wikipedia.html Secret/jornal.doc

echo "-- Change de permissions"
chmod a-rwx,u+rwx Binome
chmod a-rwx,u+rw Binome/devoir.tex
chmod g-wx,o-wx Connaisseurs
chmod g-w Connaisseurs/reponse746.txt
chmod g-r,o-r+w Depot
chmod g-w Public
chmod g-w Public/images Public/medias Public/wikipedia.html
chmod g-rwx,o-rx Secret
chmod g-rw,o-r Secret/jornal.doc

echo "-- Change de permissions ACL"
setfacl -m u:faded:rwx Binome
setfacl -m u:faded:rw Binome/devoir.tex

