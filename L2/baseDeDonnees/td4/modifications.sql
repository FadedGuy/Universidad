alter table REALISATEURS modify prenomreal varchar(15) NOT NULL;

create table REALISENT(
    CODREAL varchar(5),
    CODFILM char(5),
    constraint PK_REALISENT primary key (CODREAL, CODFILM),
    constraint FK_REALISENT_CODREAL foreign key (CODREAL) references REALISATEURS,
    constraint FK_REALISENT_CODFILM foreign key (CODFILM) references FILMS); 

alter table JOUENT modify constraint pk_JOUENT primary key (Codfilm, Nact, Nompers);

alter table FILMS modify Catfilm varchar(25) NOT NULL;


create table producteurs(
    Codprod char(5),
    Nom varchar(25),
    Adresse varchar(20),
    Ville varchar(20),
    Pays varchar(20),
    Nationalite varchar(20),
    constraint PK_CODPROD primary key (Codprod));

create table produisent(
    Codprod char(5),
    Codfilm char(5),
    constraint PK_PRODUISENT primary key (Codfilm),
    constraint FK_PRODUISENT_CODPROD foreign key (Codprod) references producteurs,
    constraint FK_PRODUISENT_CODFILM foreign key (Codfilm) references FILMS);
