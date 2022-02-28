create table REALISATEURS(
    Codreal varchar(6),
    Nomreal varchar(20),
    Nationreal varchar(20),
    Dnaissreal date,
    Ddecreal date,
    constraint pk_REALISATEURS primary key (Codreal),
    constraint ck_REALISATEURS_Ddecreal check (Ddecreal > Dnaissreal));

create table FILMS(
    Codfilm char(4),
    Titrefilm varchar(50),
    Datesortie date,
    Duree number,
    Budget number,
    Codreal varchar(6),
    constraint pk_FILMS primary key (Codfilm),
    constraint fk_FILMS_REALISATEURS foreign key (Codreal) references REALISATEURS,
    constraint ck_FILMS_Duree Check (Duree > 0),
    constraint ck_FILMS_Budget Check (Budget > 0));


create table ACTEURS(
    Codact char (5),
    Nomact varchar(20),
    Prenomact varchar (20),
    Nationact varchar (20),
    Sexe char (1),
    Dnaissact date,
    Ddecact date,
    constraint pk_ACTEURS primary key (Codact),
    constraint ck_ACTEURS_Sexe check (Sexe in ('H','F')),
    constraint ck_ACTEURS_Ddecact check (Ddecact > Dnaissact));

create table JOUENT(
    Codfilm char(4),
    Nact char(5),
    Nompers varchar(30),
    constraint pk_JOUENT primary key (Codfilm, Nact),
    constraint fk_JOUENT_FILMS foreign key (Codfilm) references FILMS,
    constraint fk_JOUENT_ACTEURS foreign key (Nact) references ACTEURS);