INSERT INTO MUSEE VALUES ('FR001', 'Louvre', 'Rue de Paris 75001');

INSERT INTO ARTISTE VALUES ('IT001', 'da Vinci', 'Leo', date '1452-04-14', date '1519-05-02', 'Italie');
INSERT INTO ARTISTE VALUES ('NL001', 'van Gogh', 'Vincent', date '1853-03-30', date '1890-07-29', 'Pays-Bas');
INSERT INTO ARTISTE VALUES ('ES001', 'Dali', 'Salvador', date '1904-05-11', date '1989-01-23', 'Espagne');
INSERT INTO ARTISTE VALUES ('IT002', 'Michelangelo', 'di Lodovico', date '1475-03-06', date '1564-02-18', 'Italie');

INSERT INTO EMPLOYES VALUES ('AC001', '5 Boulevard des Pyrénées, 64000', 'Avag', 'Alassane', date '1980-08-19', '1350', 'FR001');
INSERT INTO EMPLOYES VALUES ('AC002', 'Place de l etoile, 75014', 'Gilles', 'Lili', date '1970-02-20', '1420', 'FR001');

INSERT INTO AGENT_D_ACCUEIL VALUES ('AC001');
INSERT INTO AGENT_D_ACCUEIL VALUES ('AC002');

INSERT INTO EMPLOYES VALUES ('AS001', '26 rue des hortensias, 75006', 'Muirenn', 'Euclides', date '2003-02-20', '1650', 'FR001');

INSERT INTO AGENT_DE_SECURITE VALUES ('AS001');

INSERT INTO EMPLOYES VALUES ('RO001', '12 rue de la Sourdière, 75001', 'Carlos', 'Sevilla', date '1968-05-08', '2200', 'FR001');

INSERT INTO Restaurateur_d_oeuvre VALUES ('RO001');

INSERT INTO VISITEUR VALUES ('V0001', 'Jean', 'Martin', date '1990-11-08', 'Paris', 'France', 1, 'AC002', 'FR001');

INSERT INTO OEUVRES VALUES ('PT001', 'Peinture de Salvador Dali', 'La persistance de la mémoire', date '1931-01-01', 'FR001', 'ES001');
INSERT INTO OEUVRES VALUES ('SC001', 'Sculpture de Michel-Ange', 'David', date '1504-01-01', 'FR001', 'IT002');

INSERT INTO PEINTURES VALUES ('PT001');
INSERT INTO Sculptures VALUES ('SC001');

INSERT INTO Salle_du_Musee VALUES ('FR001', 'Salle d exposition 1');
INSERT INTO RESERVES VALUES('FR001', 40);

INSERT INTO Tache VALUES ('TA001', 'Reparation', 'Reparer cadre', date '2023-01-22', date '2023-03-25', 'PT001', 'RO001');