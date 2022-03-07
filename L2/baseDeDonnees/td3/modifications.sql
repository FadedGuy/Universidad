alter table FILMS modify Titrefilm varchar(70);

alter table REALISATEURS add Prenomreal varchar(20);


update REALISATEURS set Prenomreal='James' where Codreal='CAM01';
update REALISATEURS set Prenomreal='Ridley' where Codreal='SCO01';
update REALISATEURS set Prenomreal='Sam' where Codreal='MEN01';
update REALISATEURS set Prenomreal='Jean' where Codreal='NEG01';
update REALISATEURS set Prenomreal='Guillaume' where Codreal='CAN01';
update REALISATEURS set Prenomreal='Claude' where Codreal='BER01';
update REALISATEURS set Prenomreal='Danny' where Codreal='BOY01';
update REALISATEURS set Prenomreal='Gilles' where Codreal='LEL01';

update FILMS set Budget=Budget*1.1;

alter table FILMS drop constraint fk_FILMS_REALISATEURS;

alter table REALISATEURS modify Codreal char(5);
alter table FILMS modify Codreal char(5);
alter table FILMS add constraint fk_FILMS_REALISATEURS foreign key (Codreal) references REALISATEURS;


alter table FILMS add Catfilm char(20);
alter table FILMS add constraint ck_FILMS_Catfilm check (Catfilm in ('comédie','drame','policier','science-fiction','horreur','thriller','comédie dramatique'));
update FILMS set Catfilm='science-fiction' where Codfilm='F011';
update FILMS set Catfilm='science-fiction' where Codfilm='F012';
update FILMS set Catfilm='science-fiction' where Codfilm='F013';
update FILMS set Catfilm='drame' where Codfilm='F014';
update FILMS set Catfilm='drame' where Codfilm='F015';
update FILMS set Catfilm='drame' where Codfilm='F016';
update FILMS set Catfilm='comédie dramatique' where Codfilm='F017';
update FILMS set Catfilm='comédie dramatique' where Codfilm='F018';
update FILMS set Catfilm='thriller' where Codfilm='F019';
update FILMS set Catfilm='comédie' where Codfilm='F020';
