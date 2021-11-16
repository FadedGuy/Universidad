#!/bin/bash
echo "| Script de copie du site SiteSmileys"
echo "|   Auteur(s) : Kevin Aceves"
echo ""
echo "-- Nettoyage du dossier courant"
rm -fr ./SiteSmileysScripté

echo "-- Création du répertoire SiteSmileysScripté"
mkdir ./SiteSmileysScripté

echo "-- Création de l'arborescence"
cd ./SiteSmileysScripté
mkdir ./image ./une_autre_image ./des_images
cd ./des_images
mkdir encore_des_images et_encore
cd ../

echo "Debug: dossier courant : "$(pwd)

#- Décommenter la ligne suivante si vous voulez afficher l'arborescence créée
#tree ../SiteSmileysScripté

echo "-- Copie des fichiers dans l'arborescence"
cp ~/Documents/SiteSmileys/page1.html ./
cp ~/Documents/SiteSmileys/smileyA.png ./
cp ~/Documents/SiteSmileys/une_autre_image/smileyC.png ./une_autre_image/
cp ~/Documents/SiteSmileys/image/smileyB.png ./image/
cp ~/Documents/SiteSmileys/des_images/smileyD.png ./des_images/
cp ~/Documents/SiteSmileys/des_images/smileyE.png ./des_images/
cp ~/Documents/SiteSmileys/des_images/encore_des_images/smileyF.png ./des_images/encore_des_images/
cp ~/Documents/SiteSmileys/des_images/encore_des_images/smileyG.png ./des_images/encore_des_images/
cp ~/Documents/SiteSmileys/des_images/et_encore/smileyH.png ./des_images/et_encore/
cp ~/Documents/SiteSmileys/des_images/et_encore/smileyI.png ./des_images/et_encore/

#- Décommenter la ligne suivante si vous voulez afficher l'arborescence créée
tree ../SiteSmileysScripté
