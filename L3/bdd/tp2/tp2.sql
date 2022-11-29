create or replace trigger histopret_trg
    before
    delete
    on pret
    for each row
begin 
    insert into histopret (codex, datepret, codpers, dateret) values(:old.codex, :old.datep, :old.codpers, SYSDATE);
end;

--delete from pret 
--where codpers='PP92';
--
--insert into pret values('08S55', 'MB58', TO_DATE('26/10/22', 'DD/MM/YY'));

create or replace trigger livres_insert_trg
    before
    insert
    on livres
    for each row
begin
    insert into ouvrages values (:new.codouv, :new.titouv, :new.langue);
end;

create or replace trigger revues_insert_trg
    before
    insert
    on revues
    for each row
begin
    insert into ouvrages values (:new.codouv, :new.titouv, :new.langue);
end;

--insert into livres values ('PO15', 'Titre du nouveau', 'Anglais');


create or replace trigger livres_delete_trg
    after
    delete
    on livres
    for each row
begin
    delete from ouvrages o
    where :old.codouv = o.codouv; 
end;

create or replace trigger revues_delete_trg
    after
    delete
    on revues
    for each row
begin
    delete from ouvrages o
    where :old.codouv = o.codouv; 
end;

--delete from livres where codouv='PO15';


alter table personnes add (nbpret number);

update personnes p 
set p.nbpre = (
select count(pt.codpers)
from pret pt
where pt.codpers = p.codpers
group by pt.codpers
);

alter table personnes add (datederpret date);
update personnes p
set p.datederpret = (
select pt.datep
from pret pt
);

alter table personnes add (datederret date);

alter table livres add (nbpretl number);
alter table livres add (nbjourpret number);
alter table livres add (datederretl date);



