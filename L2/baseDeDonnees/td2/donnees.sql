insert into REALISATEURS
  values ('CAM01', 'Cameron', 'canadienne', '16/08/1954', null);

insert into FILMS
  values ('F011', 'Avatar', '16/12/2009', 162, 500000000, 'CAM01');

insert into ACTEURS
  values ('SAM01', 'Worthington', 'Sam', 'australienne', 'H', '02/08/1976', null);

insert into ACTEURS
  values ('SAL01', 'Saldana', 'Zoe', 'américaine', 'F', '19/06/1978', null);

insert into ACTEURS
  values ('SIG01', 'Weaver', 'Sigourney', 'américaine', 'F', '08/10/1949', null);

insert into ACTEURS
  values ('LAN01', 'Lang', 'Stephen', 'américaine', 'H', '11/07/1952', null);

insert into JOUENT
  values ('F011', 'SAM01', 'Jack Sully');

insert into JOUENT
  values ('F011', 'SAL01', 'Neytiri');

insert into JOUENT
  values ('F011', 'SIG01', 'Grace Augustine');

insert into JOUENT
  values ('F011', 'LAN01', 'Le colonel Miles Quaritch');



insert into FILMS
  values ('F012', 'Aliens, le retour', '08/10/1986', 137, 50000000, 'CAM01');

insert into ACTEURS
  values ('BIE01', 'Biehn', 'Michael', 'américaine', 'H', '31/07/1956', null);

insert into ACTEURS
  values ('HEN01', 'Henriksen', 'Lance', 'américaine', 'H', '05/05/1940', null);

insert into JOUENT
  values ('F012', 'SIG01', 'Lieutenant Ellen Ripley');

insert into JOUENT
  values ('F012', 'BIE01', 'Caporal Dwayne Hicks');

insert into JOUENT
  values ('F012', 'HEN01', 'Evêque');




insert into REALISATEURS
  values ('SCO01', 'Scott', 'anglaise', '30/11/1937', null);

insert into FILMS
  values ('F013', 'Aliens, le huitième passager', '12/09/1979', 116, 25000000, 'SCO01');

insert into ACTEURS
  values ('SKE01', 'Skerritt', 'Tom', 'américaine', 'H', '25/08/1933', null);

insert into JOUENT
  values ('F013', 'SIG01', 'Lieutenant Ellen Ripley');

insert into JOUENT
  values ('F013', 'SKE01', 'Capitaine A.J. Dallas');




insert into FILMS
  values ('F014', 'Titanic', '07/07/1998', 194, 30000000, 'CAM01');

insert into ACTEURS
  values ('DIC01', 'Di Caprio', 'Leonardo', 'américaine', 'H', '11/11/1974', null);

insert into ACTEURS
  values ('WIN01', 'Winslet', 'Kate', 'anglaise', 'F', '05/10/1975', null);

insert into JOUENT
  values ('F014', 'DIC01', 'Jack Dawson');

insert into JOUENT
  values ('F014', 'WIN01', 'Rose DeWitt Butaker');



insert into REALISATEURS
  values ('MEN01', 'Mendes', 'anglaise', '01/08/1965', null);

insert into FILMS
  values ('F015', 'Les noces rebelles', '21/01/2009', 125, 100000000, 'MEN01');

insert into JOUENT
  values ('F015', 'DIC01', 'Franck Wheeler');

insert into JOUENT
  values ('F015', 'WIN01', 'April Wheeler');



insert into REALISATEURS
  values ('NEG01', 'Negulesco', 'américaine', '26/02/1900', '18/07/1993');

insert into FILMS
  values ('F016', 'Titanic', null, 98, null, 'NEG01');

insert into ACTEURS
  values ('WEB01', 'Webb', 'Clifton', 'américaine', 'H', '11/11/1889', '13/10/1966');

insert into ACTEURS
  values ('STA01', 'Stanwyck', 'Barbara', 'américaine', 'F', '16/07/1907', '20/01/1990');

insert into ACTEURS
  values ('DAL01', 'Dalton', 'Audrey', 'américaine', 'F', '21/01/1934', null);

insert into ACTEURS
  values ('WAG01', 'Wagner', 'Robert', 'américaine', 'H', '10/02/1930', null);

insert into JOUENT
  values ('F016', 'WEB01', 'Richard Ward Sturges');

insert into JOUENT
  values ('F016', 'STA01', 'Julia Sturges');

insert into JOUENT
  values ('F016', 'DAL01', 'Anette Sturges');

insert into JOUENT
  values ('F016', 'WAG01', 'Gifford Roger');



insert into REALISATEURS
  values ('CAN01', 'Canet', 'française', '10/04/1973', null);

insert into FILMS
  values ('F017', 'Les petits mouchoirs', '20/10/2010', 154, 30000000, 'CAN01');

insert into ACTEURS
  values ('CLU01', 'Cluzet', 'François', 'française', 'H', '21/09/1955', null);

insert into ACTEURS
  values ('COT01', 'Cotillard', 'Marion', 'française', 'F', '30/09/1975', null);

insert into ACTEURS
  values ('DUJ01', 'Dujardin', 'Jean', 'française', 'H', '16/06/1972', null);

insert into ACTEURS
  values ('LEL01', 'Lellouche', 'Gilles', 'française', 'H', '05/07/1972', null);

insert into ACTEURS
  values ('MAG01', 'Magimel', 'Benoît', 'française', 'H', '11/05/1974', null);

insert into JOUENT
  values ('F017', 'CLU01', 'Max Cantara');

insert into JOUENT
  values ('F017', 'COT01', 'Marie');

insert into JOUENT
  values ('F017', 'DUJ01', 'Ludo');

insert into JOUENT
  values ('F017', 'LEL01', 'Eric');

insert into JOUENT
  values ('F017', 'MAG01', 'Vincent Ribaud');




insert into REALISATEURS
  values ('BER01', 'Berry', 'française', '01/07/1934', '12/01/2009');

insert into FILMS
  values ('F018', 'Ensemble c''est tout', '21/03/2007', 97, 60000000, 'BER01');

insert into ACTEURS
  values ('CAN01', 'Canet', 'Guillaume', 'française', 'H', '10/04/1973', null);

insert into ACTEURS
  values ('TAU01', 'TAUTOU', 'Audrey', 'française', 'F', '09/08/1976', null);

insert into JOUENT
  values ('F018', 'CAN01', 'Franck');

insert into JOUENT
  values ('F018', 'TAU01', 'Camille');



insert into REALISATEURS
  values ('BOY01', 'Boyle', 'anglaise', '20/10/1956', null);

insert into FILMS
  values ('F019', 'La plage', '16/02/2000', 119, 45000000, 'BOY01');

insert into ACTEURS
  values ('LED01', 'Ledoyen', 'Virginie', 'française', 'F', '15/11/1975', null);

insert into JOUENT
  values ('F019', 'DIC01', 'Richard');

insert into JOUENT
  values ('F019', 'CAN01', 'Etienne');

insert into JOUENT
  values ('F019', 'LED01', 'Françoise');



insert into REALISATEURS
  values ('LEL01', 'Lellouche', 'française', '05/07/1972', null);

insert into FILMS
  values ('F020', 'Narco', '01/12/2004', 105, 70000000, 'LEL01');

insert into ACTEURS
  values ('POE01', 'Poelvoorde', 'Benoît', 'belge', 'H', '22/09/1964', null);

insert into JOUENT
  values ('F020', 'CAN01', 'Gustave Klopp');

insert into JOUENT
  values ('F020', 'POE01', 'Lenny Bar');

insert into JOUENT
  values ('F020', 'LEL01', 'Le jumeau patineur');
