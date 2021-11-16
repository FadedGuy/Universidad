#!/bin/bash
echo "| Script de copie du Propriete"
echo "|   Auteur(s) : Kevin Aceves"
echo ""
echo "-- Nettoyage du dossier courant"
rm -fr ./ProprieteScriptee

echo "-- Création du répertoire ProprieteScriptee"
mkdir ./ProprieteScriptee

echo "-- Création de la Propriete"
cd ./ProprieteScriptee
mkdir Jardin Allee Terrasse
cd ./Jardin
mkdir Salon-Sejour
cd ./Salon-Sejour
mkdir Cuisine Degagement WC
mkdir Cuisine/"Arriere cuisine"
cd ../../Terrasse
mkdir Local_piscine
cd ../

echo "-- Creation de raccourcis entre pieces"
cd ./Allee
ln -s ../Jardin/Salon-Sejour/Cuisine/"Arriere cuisine"
cd ../Jardin/Salon-Sejour/Cuisine/"Arriere cuisine"
ln -s ../../../../Terrasse/

echo "-- Amenagement de la propriete"
cd ../../../../ 
cp ~/Documents/Centre_commercial/arbres.png Jardin/
cp ~/Documents/Centre_commercial/piscine.png Terrasse/
cp ~/Documents/Centre_commercial/voiture.png Allee/

echo "-- Demenagement du mobilier"
cd Allee/
wget http://bjobard.perso.univ-pau.fr/Cours/ISE/Assets/TP2/Camion_d%C3%A9m%C3%A9nagement.tgz
tar xvfz Camion_déménagement.tgz
rm -fr Camion_déménagement.tgz
cd Camion_déménagement/
mv canapé.png ../../Jardin/Salon-Sejour/Cuisine/"Arriere cuisine"/
mv litA.png ../../Jardin/Salon-Sejour/Cuisine/"Arriere cuisine"/
mv litB.png ../../Jardin/Salon-Sejour/Cuisine/"Arriere cuisine"/
mv litC.png ../../Jardin/Salon-Sejour/Cuisine/"Arriere cuisine"/
mv litD.png ../../Jardin/Salon-Sejour/Cuisine/"Arriere cuisine"/
mv WC.png ../../Jardin/Salon-Sejour/Cuisine/
mv fauteuils.png ../../Jardin/Salon-Sejour/Degagement/
mv table1.png ../../Jardin/Salon-Sejour/WC/
mv "double lavabo".png ../../Terrasse/Local_piscine/
mv table2.png ../../Terrasse/

echo "-- Extension de la maison"
cd ../../Jardin/Salon-Sejour/Degagement/
mkdir Chambre1 Chambre2 Chambre3 Chambre4 Chambre1/Douche Chambre2/Douche Chambre3/"Salle de Bain"
cd ../../../
mv Jardin/Salon-Sejour/Cuisine/"Arriere cuisine"/canapé.png Jardin/Salon-Sejour/
mv Jardin/Salon-Sejour/Cuisine/"Arriere cuisine"/litA.png Jardin/Salon-Sejour/Degagement/Chambre4/
mv Jardin/Salon-Sejour/Cuisine/"Arriere cuisine"/litB.png Jardin/Salon-Sejour/Degagement/Chambre3/
mv Jardin/Salon-Sejour/Cuisine/"Arriere cuisine"/litC.png Jardin/Salon-Sejour/Degagement/Chambre2/
mv Jardin/Salon-Sejour/Cuisine/"Arriere cuisine"/litD.png Jardin/Salon-Sejour/Degagement/Chambre1/
mv Jardin/Salon-Sejour/Cuisine/WC.png Jardin/Salon-Sejour/WC
mv Jardin/Salon-Sejour/Degagement/fauteuils.png Terrasse/
mv Jardin/Salon-Sejour/WC/table1.png Jardin/Salon-Sejour/Cuisine/
mv Terrasse/Local_piscine/"double lavabo".png Jardin/Salon-Sejour/Degagement/Chambre3/"Salle de Bain"
mv Terrasse/table2.png Jardin/Salon-Sejour/
cd Jardin/Salon-Sejour/Degagement/Chambre3/
ln -s ../../../../Jardin
cd ../Chambre4/
ln -s ../Chambre3/"Salle de Bain"/
cd ../../../../
rm -fr Allee/Camion_déménagement


echo "-- Resultat"
tree 
