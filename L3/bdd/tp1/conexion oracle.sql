create table Ouvrages as 
select codOuv, titOuv, langue
from TPBD.l2ouvrages; 

alter table Ouvrages add constraint PK_OUVRAGES primary key(codouv);


create table livres as
select o2.codouv, o2.titouv, o2.langue
from TPBD.l2ouvrages o2;

alter table livres add constraint PK_LIVRES primary key(codouv);
alter table livres add constraint FK_LIVRES_OUVRAGES foreign key(codouv) references ouvrages;


create table revues (
    codouv char(4),
    titouv varchar2(110),
    langue varchar2(10),
    anEditPN number,
    periodicite varchar(15),
    
    constraint PK_REVUES primary key(codouv),
    constraint FK_REVUES_OUVRAGES foreign key(codouv) references ouvrages
);


create table numeros(
    codouv char(4),
    numParu number,
    titnum varchar(110),
    dateParu date,
    nbOccur number,
    
    constraint PK_NUMEROS primary key(codouv, numParu),
    constraint FK_NUMEROS_REVUES foreign key(codouv) references revues
);


create table bibliotheques as 
select *
from TPBD.l2bibliotheques;

alter table bibliotheques add constraint PK_BIBLIOTHEQUES primary key(codbib);


create table exemplaires as
select e.codex, e.codouv, e.dateentbib, o.nomedit, o.nbpag
from TPBD.L2EXEMPLAIRES e, TPBD.L2OUVRAGES o
where e.codouv = o.codouv;

alter table exemplaires add (codbib CHAR(4));
alter table exemplaires add constraint PK_EXEMPLAIRES primary key(codex);
alter table exemplaires add constraint FK_EXEMPLAIRES_LIVRES foreign key(codouv) references livres;
alter table exemplaires add constraint FK_EXEMPLAIRES_BIBLIOTHEQUES foreign key(codbib) references bibliotheques;

update exemplaires e
set e.codbib = (
select e2.codbib
from TPBD.L2EXEMPLAIRES_BIBLIO e2
where e2.codex = e.codex);
  
alter table exemplaires add constraint CK_EXEMPLAIRES_CODOUV check(codouv is not null);
alter table exemplaires add constraint CK_EXEMPLAIRES_CODBIB check(codbib is not null);







