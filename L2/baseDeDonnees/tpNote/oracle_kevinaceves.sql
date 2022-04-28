create table DRUIDES(
    CODDRUID varchar(6),
    NOMDRUIDE varchar(20),
    VILLAGE varchar(20),
    PAYS varchar(20),
    constraint pk_DRUIDES primary key (CODDRUID));

create table POTIONS(
    CODPOT varchar(6),
    NOMPOTION varchar(20),
    CATEGPOTION varchar(20),
    CODDRUID varchar(6),
    constraint pk_POTIONS primary key (CODPOT),
    constraint fk_POTIONS_DRUIDES foreign key (CODDRUID) references DRUIDES);

create table INGREDIENTS(
    CODINGRED varchar(6),
    NOMINGRED varchar(20),
    TYPE varchar(20),
    constraint pk_INGREDIENTS primary key (CODINGRED));

create table RECETTES(
    CODPOT varchar(6),
    CODINGRED varchar(6),
    QTE number,
    constraint pk_RECETTES primary key(CODPOT, CODINGRED),
    constraint fk_RECETTES_POTIONS foreign key (CODPOT) references POTIONS,
    constraint fk_RECETTES_INGREDIENTS foreign key (CODINGRED) references INGREDIENTS);


SELECT D.CODDRUID, D.NOMDRUIDE
FROM DRUIDES D, POTIONS P 
WHERE D.CODDRUID=P.CODDRUID
  AND P.CODPOT NOT IN (SELECT P.CODPOT
                       FROM POTIONS P, RECETTES R 
                       WHERE P.CODPOT=R.CODPOT);

SELECT *
FROM INGREDIENTS
WHERE CODINGRED = (SELECT MAX(R.CODINGRED)
                   FROM INGREDIENTS I, RECETTES R, POTIONS P
                   WHERE I.CODINGRED=R.CODINGRED
                   AND R.CODPOT=P.CODPOT
                   AND I.TYPE='tubercules');

SELECT CODPOT, NOMPOTION
FROM POTIONS
WHERE CATEGPOTION='capillaire'
  AND CODPOT IN (SELECT CODPOT
                 FROM POTIONS
                 minus 
                 SELECT CODPOT 
                 FROM RECETTES R, INGREDIENTS I
                 WHERE R.CODINGRED=I.CODINGRED
                   AND R.QTE<=50);

SELECT D.PAYS, COUNT(DISTINCT P.CODDRUID)
FROM DRUIDES D, POTIONS P, RECETTES R, INGREDIENTS I
WHERE D.CODDRUID=P.CODDRUID
  AND P.CODPOT=R.CODPOT
  AND R.CODINGRED=I.CODINGRED
  AND I.NOMINGRED='gui'
GROUP BY D.PAYS;

SELECT I.CODINGRED, I.NOMINGRED
FROM INGREDIENTS I, RECETTES R, POTIONS P
WHERE I.CODINGRED=R.CODINGRED
  AND R.CODPOT=P.CODPOT
  AND (P.CATEGPOTION='énergisantes' AND P.CATEGPOTION='Capillaire');


