CREATE TABLE Artiste(
   IDartiste CHAR(5),
   nomArt VARCHAR(20),
   prenomArt VARCHAR(20),
   dateNaissArt DATE,
   dateDecesArt DATE,
   paysArt VARCHAR(50),
   PRIMARY KEY(IDartiste)
);

CREATE TABLE Musee(
   IDmusee CHAR(5),
   nomMusee VARCHAR(50),
   adresseMusee VARCHAR(50),
   PRIMARY KEY(IDmusee)
);

CREATE TABLE Employes(
   IDemployee CHAR(5),
   adresseEmploye VARCHAR(50),
   nomEmploye VARCHAR(50),
   prenomEmploye VARCHAR(50),
   dateNaissEmploye DATE,
   salaireEmploye INTEGER,
   IDmusee CHAR(5) NOT NULL,
   PRIMARY KEY(IDemployee),
   FOREIGN KEY(IDmusee) REFERENCES Musee(IDmusee)
);

CREATE TABLE Agent_d_accueil(
   IDemployee CHAR(5),
   PRIMARY KEY(IDemployee),
   FOREIGN KEY(IDemployee) REFERENCES Employes(IDemployee)
);

CREATE TABLE Agent_de_securite(
   IDemployee CHAR(5),
   PRIMARY KEY(IDemployee),
   FOREIGN KEY(IDemployee) REFERENCES Employes(IDemployee)
);

CREATE TABLE Restaurateur_d_oeuvre(
   IDemployee CHAR(5),
   PRIMARY KEY(IDemployee),
   FOREIGN KEY(IDemployee) REFERENCES Employes(IDemployee)
);

CREATE TABLE Visiteur(
   IDvisiteur CHAR(5),
   nomVisit VARCHAR(20),
   prenomVisit VARCHAR(50),
   dateNaissVisit DATE,
   villeVisit VARCHAR(50),
   paysVisit VARCHAR(50),
   nbVisites INTEGER NOT NULL,
   IDemployee CHAR(5) NOT NULL,
   IDmusee CHAR(5) NOT NULL,
   PRIMARY KEY(IDvisiteur),
   FOREIGN KEY(IDemployee) REFERENCES Agent_d_accueil(IDemployee),
   FOREIGN KEY(IDmusee) REFERENCES Musee(IDmusee)
);

CREATE TABLE Oeuvres(
   IDoeuvre CHAR(5),
   descriptionOeuvre VARCHAR(50),
   nomOeuvre VARCHAR(50),
   dateCreation DATE,
   IDmusee CHAR(5) NOT NULL,
   IDartiste CHAR(5) NOT NULL,
   PRIMARY KEY(IDoeuvre),
   FOREIGN KEY(IDmusee) REFERENCES Musee(IDmusee),
   FOREIGN KEY(IDartiste) REFERENCES Artiste(IDartiste)
);

CREATE TABLE Peintures(
   IDoeuvre CHAR(5),
   PRIMARY KEY(IDoeuvre),
   FOREIGN KEY(IDoeuvre) REFERENCES Oeuvres(IDoeuvre)
);

CREATE TABLE Sculptures(
   IDoeuvre CHAR(5),
   PRIMARY KEY(IDoeuvre),
   FOREIGN KEY(IDoeuvre) REFERENCES Oeuvres(IDoeuvre)
);

CREATE TABLE Salle_du_Musee(
   IDmusee CHAR(5),
   nomSalle VARCHAR(50),
   PRIMARY KEY(IDmusee),
   FOREIGN KEY(IDmusee) REFERENCES Musee(IDmusee)
);

CREATE TABLE Reserves(
   IDmusee CHAR(5),
   capaciteReserve INT,
   PRIMARY KEY(IDmusee),
   FOREIGN KEY(IDmusee) REFERENCES Musee(IDmusee)
);

CREATE TABLE Tache(
   IDtache CHAR(5),
   labelTache VARCHAR(50),
   descriptionTache VARCHAR(50),
   dateDeb DATE,
   dateFin DATE,
   IDoeuvre CHAR(5) NOT NULL,
   IDemployee CHAR(5) NOT NULL,
   PRIMARY KEY(IDtache),
   FOREIGN KEY(IDoeuvre) REFERENCES Oeuvres(IDoeuvre),
   FOREIGN KEY(IDemployee) REFERENCES Restaurateur_d_oeuvre(IDemployee)
);