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


create table personnes as 
select *
from TPBD.L2PERSONNES;

alter table personnes add constraint PK_PERSONNES primary key(codpers);
alter table personnes add constraint FK_PERSONNES_BIBLIOTHEQUES foreign key(codbib) references bibliotheques;
alter table personnes add constraint CK_PERSONNES_CODBIB check(codbib is not null);


create table pret as
select *
from TPBD.l2pret;

alter table pret add constraint PK_PRET primary key(codex);
alter table pret add constraint FK_PRET_EXEMPLAIRES foreign key(codex) references exemplaires;
alter table pret add constraint FK_PRET_PERSONNES foreign key(codpers) references personnes;
alter table pret add constraint CK_PRET_CODPERS check(codpers is not null);


create table histopret (
    codex char(5),
    datepret date,
    codpers char(4),
    dateret date,
    
    constraint PK_HISTOPRET primary key(codex, datepret),
    constraint FK_HISTOPRET_EXEMPLAIRES foreign key(codex) references exemplaires,
    constraint FK_HISTOPRET_PERSONNES foreign key(codpers) references personnes,
    constraint CK_HISTOPRET_CODPERS check(codpers is not null)
);


create table auteurs(
    codaut number,
    nomaut varchar(20),
    prenomaut varchar(20),
    
    constraint PK_AUTEURS primary key(codaut)
);

create sequence seqcodaut;

create view auteursAux as
select distinct nomaut, prenomaut
from tpbd.l2ouvrages;

insert into auteurs 
select seqcodaut.nextval, nomaut, prenomaut
from auteursAux;


create table ecrit(
    codaut number,
    codouv char(4),
    
    constraint PK_ECRIT primary key(codaut, codouv),
    constraint FK_ECRIT_AUTEURS foreign key(codaut) references auteurs,
    constraint FK_ECRIT_LIVRES foreign key(codouv) references livres
);

insert into ecrit 
select a.codaut, o.codouv
from AUTEURS a, TPBD.L2OUVRAGES o 
where a.nomaut = o.nomaut
  and a.prenomaut = o.prenomaut;


create table MOTSCLES(
    codmot char(4),
    libelleMot varchar(30),
    codmotpere char(4),
    
    constraint PK_MOTSCLES primary key(codmot),
    constraint FK_MOTSCLES_MOTSCLES foreign key(codmotpere) references motscles
);


create table traite(
    codouv char(4),
    codmot char(4),
    
    constraint PK_TRAITE primary key(codouv, codmot),
    constraint FK_TRAITE_OUVRAGES foreign key(codouv) references ouvrages,
    constraint FK_TRAITE_MOTSCLES foreign key(codmot) references motscles
);

