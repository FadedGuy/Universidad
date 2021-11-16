==============
TUX le Manchot
==============
---------------------------------------------------
Projet d\'Introduction aux Systèmes d\'Exploitation
---------------------------------------------------

:Auteurs: *K. Aceves*
:Généré par: *faded*

Ce document a été généré  à partir du fichier ``tux.rst`` au
format `reStructuredText`_ lui-même créé par le script
``tux.sh``. Ce fichier  rst a  ensuite  été  converti en
HTML  et  PDF avec  les commandes ``rst2html`` et ``rst2pdf``.



.. _reStructuredText: https://aful.org/wikis/interop/ReStructuredText

.. sidebar:: Références

   Les directives du format RST sont disponibles `ici`_.

.. _ici: http://docutils.sourceforge.net/docs/ref/rst/directives.html

L\'objectif est de compléter le script ``tux.sh`` afin que les
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
|	Pingouin ?  //\                   TUX                   /\\  Manchot !       |
|		    V_/_                                       _\_V                  |
|	                                                                             |
+------------------------------------------------------------------------------------+

.. _Pingouin: http://bit.ly/W_Pingouin
.. _manchot: http://bit.ly/W_Manchot


Les manchots sont des geeks ! 
=========================================
La commande ``screenfetch`` affiche le logo et des informations en temps réel sur la distribution Linux. 
::

 %{-------------------------------------------------------------------------------+
  |                          ./+o+-       faded@ubuntu                            |
  |                  yyyyy- -yyyyyy+      OS: Ubuntu 20.04 focal                  |
  |               ://+//////-yyyyyyo      Kernel: x86_64 Linux 5.4.0-58-generic   |
  |           .++ .:/++++++/-.+sss/`      Uptime: 1h 26m                          |
  |         .:++o:  /++++++++/:--:/-      Packages: 1711                          |
  |        o:+o+:++.`..```.-/oo+++++/     Shell: bash 5.0.17                      |
  |       .:+o:+o/.          `+sssoo+/    Resolution: 1920x1007                   |
  |  .++/+:+oo+o:`             /sssooo.   DE: GNOME 3.36.4                        |
  | /+++//+:`oo+o               /::--:.   WM: Mutter                              |
  | \+/+o+++`o++o               ++////.   WM Theme: Adwaita                       |
  |  .++.o+++oo+:`             /dddhhh.   GTK Theme: Yaru-dark [GTK2/3]           |
  |       .+.o+oo:.          `oddhhhh+    Icon Theme: Yaru                        |
  |        \+.++o+o``-````.:ohdhhhhh+     Font: Ubuntu 11                         |
  |         `:o+++ `ohhhhhhhhyo++os:      Disk: 9.4G / 23G (44%)                  |
  |           .o:`.syhhhhhhh/.oo++o`      CPU: Intel Core i7-10750H @ 2x 2.592GHz |
  |               /osyyyyyyo++ooo+++/     GPU: VMware SVGA II Adapter             |
  |                   ````` +oo+++o\:     RAM: 2187MiB / 3908MiB                  |
  |                          `oo++.                                               |
  +-------------------------------------------------------------------------------%}

Ici, la sortie de ``screenfetch`` est filtrée pour extraire des informations qui sont stockées dans des variables et insérées dans cette petite bande-dessinée générée par un enchaînement de commandes : 

::

 /*       _\|/_
          (o o)
  +----oOO-{_}-OOo--------------------------------------------------------------+
  |                               .--,       .--,                               |
  |                              ( (  \.---./  ) )                              |
  |                               '.__/o   o\__.'                               |
  |                                  {=  ^  =}                                  |
  |                                   >  -  <                                   |
  |         ______________________.""`-------`"".______________________         |
  |        /                                                           \        |
  |        \   +----------------------+  +-------------------------+   /        |
  |        /   | Mon ordi tourne sous |  | Il utilise  2187MiB     |   \        |
  |        \   | Ubuntu 20.04 focal   |  | sur les  3908MiB dispo. |   /        |
  |        /   |  \                   |  |  \                      |   \        |
  |        \   |   (o<   _-)          |  |   (o<   _-)             |   /        |
  |        /   |   //\   /\\          |  |   //\   /\\             |   \        |
  |        \   |   V_/_ _\_V          |  |   V_/_ _\_V             |   /        |
  |        /   +----------------------+  +-------------------------+   \        |
  |        \   +----------------------------+  +-------------------+   /        |
  |        /   | Et il est en marche depuis |  |      Fais gaffe ! |   \        |
  |        \   | 1 heures, 26 minutes !     |  |        tu deviens |   /        |
  |        /   |  \                         |  |   un vrai geek... |   \        |
  |        \   |   \                        |  |                 / |   /        |
  |        /   |    (o<   _-)               |  |         (*_   >-) |   \        |
  |        \   |    //\   /\\               |  |         //\   /\\ |   /        |
  |        /   |    V_/_ _\_V               |  |         V_/_ _\_V |   \        |
  |        \   +----------------------------+  +-------------------+   /        |
  |        /                                                           \        |
  |        \___________________________________________________________/        |
  |                                 ___)( )(___                                 |
  |                                (((__) (__)))                                |
  +----------------------------------------------------------------------------*/


::

********************************************************************************
*                                                                              *
*                         ____________________________                         *
*                        (                            )                        *
*                        (   Laisse tomber Charlie,   )                        *
*                        (   tu n'es qu'un veau !     )                        *
*                        (      \                     )                        *
*                        (       (o<   ~x)            )                        *
*                        (       //\   /\\            )                        *
*                        (       V_/_ _\_V            )                        *
*                        (                            )                        *
*                         ----------------------------                         *
*                                o   ^~~^                                      *
*                                 o  (oO)\_______                              *
*                                    (__)\       )---                          *
*                                        ||----/°|                            *
*                                        ||     ||                             *
*                                                                              *
********************************************************************************

ASCII Art 
----------------
Le tableau ci-dessous a été généré à l'aide de commandes. Les images sont tirées directement du web, sans sauvegarde locale. La plus grande image fait exactement 78 caractères de large. Les deux autres images font la même hauteur.

+------------------------------------------------------------------------------+
| ::                                                                           |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|               ;l.                                         .oKWMMOd'          |
|  .lXWNl.      0No                                         OMMMMMKWM:         |
|    0MK         ..    ..  .'.     ..    ..  ..... .......  Kl:NOc,0MX         |
|    0MK      .lWMl .lWM0ldkMMc  cNMk  :KM0  ;OMW; :Wo'     Od:;'oldMW         |
|    0MK        WMl   XMx   xM0   KMk   xM0    cWWdO.       d;.....dNN;        |
|    0MK    ..  WMl   XMx   dM0   KMk   xM0     xNM0.      .K.....  0XW:       |
|    0MK    X0  WMl   XMx   dM0   OMN'..OM0   'Kl :WN;    lX.       .NMMk.     |
|  .lxxxooodxl.lxxd: cxxd; ,dxxc  .oOOd;cxxc.lxd, .dxxl. kW;         ,NNMN.    |
|                                        .............. oW:           ,NNWX    |
|                  ..........'''''',,,,,,,,;;;;;;;,,'..lMk             WNWMo   |
|      ...................''''''''''.........          kkc             NXNXo   |
|   .......................                           ....           ..ONXl.   |
|   ............                                   ........          '......   |
|   ......                                         ...........    'oXl........ |
|    .                                              ........,xK00000K:'....    |
|                                                        ....        ....      |
|                                                                              |
|                                                                              |
+-----------------------------------+------------------------------------------+
| ::                                | ::                                       |
|                                   |                                          |
|                  .''''.           |            .:cool;.                      |
|                :kKNWWNKk:         |        .'.'....,cxXKo.                   |
|               oWMWMMMMWMWo        |       ,.  ...',;cldKWM0,                 |
|              .0WWWWWWWWWW0.       |     '; ....,;:oxl:;cxNMM0;               |
|              ,KWWWWWWWWWWK,       |    .d..,:oxxxOO;.....lMMMMNd,......      |
|              ;XN0oxNXxo0NX;       |    od'lkc'..:kOoc...'oMMMMMMWNK00OOOko;  |
|             .xNK:  ,,  :KNx.      |    dNo0o....,O0NK;..,,...;lxXMMMM0:,..   |
|            .xXNx.      .xNXx.     |    ,MWNx'....'c;.   .        'dXNX:      |
|           :OXXk.        .kXXO:    |     lMMWk;....'....''       ....lO0'     |
|          oKXXO'          'OXXKo   |      :WMMWKkc,,'.....    ........,od     |
|         ;KKKk,            ,kKKK;  |       ;WMMMM,         ..........'',d.    |
|         dKKx.              .xKKd  |        oXMMM.      ..........'''',,:     |
|        'OK0;                ;0KO' |        ;kMMMc   ..........'''',,,,,.     |
|        .kk:,cl;;;,.  .,;;;lc,:kk. |        cOMMMK..........'''',,,,,,,'      |
|         ;;cx00000O:  :O00000xc;;  |       'cNWNWNO'.....''''',,,,,,,''       |
|         .dO0000000d..d0000000Od.  |       ;xWl ,OKk;..'''',,,,,,,'''.        |
|          .oOOOOOOOd..dOOOOOOOo.   |       :ko....:dxo:,,,,,,,,',,'..         |
|            'cdOOOk:,':kOOOdc'     |      .,:;;;:::::cll:;;;;;;::;;,'..       |
|               ,cc,.,'.,cc,        |            ................              |
|                                   |                                          |
+-----------------------------------+------------------------------------------+
