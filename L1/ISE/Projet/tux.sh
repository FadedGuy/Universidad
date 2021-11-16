#!/bin/bash

#-----------------------------------------------------
# Projet L1 - Introduction aux Systèmes d'Exploitation
#-----------------------------------------------------

# Remplacer les noms par les vôtres
auteurs="K. Aceves"

# Les fichiers générés par le script
fichier_rst="tux.rst"
fichier_html="tux.html"
fichier_pdf="tux.pdf"

echo "Génération de ${fichier_rst}"

# Insertion d'un bloc de texte dans fichier_rst.
# Le texte concerné est compris entre les deux mots BLOC.
cat > ${fichier_rst}  << BLOC
==============
TUX le Manchot
==============
---------------------------------------------------
Projet d\'Introduction aux Systèmes d\'Exploitation
---------------------------------------------------

:Auteurs: *${auteurs}*
:Généré par: *$(whoami)*

Ce document a été généré  à partir du fichier \`\`tux.rst\`\` au
format \`reStructuredText\`_ lui-même créé par le script
\`\`tux.sh\`\`. Ce fichier  rst a  ensuite  été  converti en
HTML  et  PDF avec  les commandes \`\`rst2html\`\` et \`\`rst2pdf\`\`.



.. _reStructuredText: https://aful.org/wikis/interop/ReStructuredText

.. sidebar:: Références

   Les directives du format RST sont disponibles \`ici\`_.

.. _ici: http://docutils.sourceforge.net/docs/ref/rst/directives.html

L\'objectif est de compléter le script \`\`tux.sh\`\` afin que les
documents générés ressemblent le plus fidèlement possible au modèle fourni.

L'histoire de TUX
=================

Quelques années après le lancement du noyau Linux en 1991, le besoin d'un logo se fit sentir. De nombreuses propositions furent soumises, mais **Linus Torvalds**, le créateur de Linux, suggéra de styliser un manchot !

À ceux qui rétorquèrent qu'un tel animal ne mettrait pas en valeur la puissance de ce nouveau système d'exploitation, Linus répondit qu'ils ne connaissaient visiblement pas *sa vitesse à la course* et la *dureté de son bec* ! Celui-ci s'était en effet fait courser et pincer dans un zoo. C'est **Larry Ewing** qui emporta le concours de logo.

Le nom du manchot, **TUX**, peut-être compris comme le rétro-acronyme composé à partir des mots "**T**\ orvalds" et "**U**\ ni\ **X**".
	
.. figure:: http://bit.ly/Logo_TUX2
	:align: center
	:alt: Tux
	:scale: 450%
	
	**Figure :** TUX, la mascotte de Linux.

Manchot ou pingouin ?
---------------------
+---------------------------------------+--------------------------------------------+
| **Noms et liens vers site web**       | **Images**                                 |
+=======================================+============================================+
| Pingouin_ se dit *auk* en anglais     | .. image:: http://bit.ly/I_Pingouin2       | 
|                                       |     :scale: 60%                            |
+---------------------------------------+--------------------------------------------+
| Alors que manchot_ se traduit         | .. image:: http://bit.ly/I_Manchot2        |
| par *penguin* !                       |     :scale: 450%                           |
|                                       |                                            |
+---------------------------------------+--------------------------------------------+
|                                                                                    |
|::                                                                                  |
|                                                                                    |
|		    (-_                                         _o)                  |
|	Pingouin ?  //\                   TUX                   /\\\  Manchot !       |
|		    V_/_                                       _\_V                  |
|	                                                                             |
+------------------------------------------------------------------------------------+

.. _Pingouin: http://bit.ly/W_Pingouin
.. _manchot: http://bit.ly/W_Manchot

BLOC

(echo -e "\nLes manchots sont des geeks ! \n=========================================\nLa commande \`\`screenfetch\`\` affiche le logo et des informations en temps réel sur la distribution Linux. \n::\n"; screenfetch -N | boxes -d netdata) >> tux.rst

(echo -e "\nIci, la sortie de \`\`screenfetch\`\` est filtrée pour extraire des informations qui sont stockées dans des variables et insérées dans cette petite bande-dessinée générée par un enchaînement de commandes : ") >> tux.rst


os=$(screenfetch -N | grep "OS" | awk -F":" '{print $2}')
ramUtil=$(screenfetch -N | grep "RAM" | awk -F"RAM:" '{print $2}' | awk -F"/" '{print $1}')
ramDispo=$(screenfetch -N | grep "RAM" | awk -F"RAM:" '{print $2}' | awk -F"/" '{print $2}')
heures=$(screenfetch -N | grep "Uptime" | awk -F"Uptime:" '{print $2}' | awk -F"h" '{print $1}')
minutes=$(screenfetch -N | grep "Uptime" | awk -F"Uptime:" '{print $2}' | awk -F"m" '{print $1}' | awk -F" " '{print $2}')
penguin=" \\ \n   (o<   _-)\n   //\\   /\\\\\ \n   V_/_ _\_V"
penguinG=" \\ \n   \\ \n    (o<   _-)\n    //\\   /\\\\\ \n    V_/_ _\_V"
penguin1=" / \n  (*_   >-)\n  //\\   /\\\\\ \n  V_/_ _\_V"

(echo -e "\n::\n" ; (paste -d ' ' <((echo -e " Mon ordi tourne sous\n$os\n $penguin") | boxes -d stone) <((echo -e " Il utilise $ramUtil\n sur les $ramDispo dispo.\n $penguin") | boxes -d stone) ; paste -d ' ' <((echo -e " Et il est en marche depuis\n$heures heures, $minutes minutes ! \n $penguinG") | boxes -d stone) <((echo -e " Fais gaffe ! \n tu deviens \n un vrai geek...\n $penguin1") | boxes -d stone -a r -s21)) | boxes -d mouse -p h3 | boxes -d peek -p h8) >> tux.rst

(echo -e "\n\n::\n" ; (echo -e "                          \n  Laisse tomber Charlie, \n  tu n'es qu'un veau ! \n     \\ \n      (o<   ~x) \n      //\   /\\\\\ \n      V_/_ _\_V \n" | cowthink -e oO -n | sed 's.\\/\\.---.g' | sed 's.o   ^__^.o   ^~~^.g' | sed 's.w ./°.g')| boxes -d simple -s 80x19 -p t2b1h24) >> tux.rst



echo -e "\nASCII Art \n----------------\nLe tableau ci-dessous a été généré à l'aide de commandes. Les images sont tirées directement du web, sans sauvegarde locale. La plus grande image fait exactement 78 caractères de large. Les deux autres images font la même hauteur.\n" >> tux.rst

(paste -d "" <((echo -e "::\n\n$(wget -qO - https://imgur.com/5pfElEi.jpg | jp2a - -i --width=78)") | boxes -d stone | sed '$d'); paste -d "" <((echo -e "::\n\n$(wget -qO - https://i.imgur.com/bdqwtzl.jpg | jp2a - -i --height=20)") | boxes -d stone | sed 's/.$//') <((echo -e "::\n\n$(wget -qO - https://imgur.com/uAWxbao.jpg | jp2a - -i --height=20)") | boxes -d stone -s 44)) >> tux.rst


# Génération des formats HTML et PDF

echo "Génération de ${fichier_html}"
rst2html -d -t -s ${fichier_rst} ${fichier_html}
echo "Génération de ${fichier_pdf}"
rst2pdf           ${fichier_rst} ${fichier_pdf}

