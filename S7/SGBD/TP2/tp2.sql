--Question 1
--on a le nom de la table et les commentaires
desc DICT
--Question 2
select * from DICT;
--Question 3
--le role
select * from DICT where TABLE_NAME = 'ALL_USERS';
--le schema
desc ALL_USERS
--Question 4
--select distinct OBJECT_TYPE from ALL_OBJECTS;
--Question 5
--le role
select * from DICT where TABLE_NAME = 'USER_USERS';
--le schema
desc USER_USERS
--Question 6
--systeme/utilisateur(owner)
--select * from ALL_CATALOG;
--select * from USER_CATALOG;
--Question 7
select CONSTRAINT_NAME, CONSTRAINT_TYPE from USER_CONSTRAINTS
 where TABLE_NAME = 'CHERCHEUR';
--Q1
--Ecoule : 00 :00 :00.00
--TABLE ACCESS BY INDEX ROWID|
select CodeEq from CHERCHEUR where CodeCh = 2;
--Q2
--Ecoule : 00 :00 :00.00
--TABLE ACCESS FULL|
select CodeCh from CHERCHEUR where CodeEq = 2;
--Q3
--Ecoule : 00 :00 :00.01
--TABLE ACCESS FULL|
select NomLabo, URL from LABORATOIRE;
--Q4
--Ecoule : 00 :00 :00.01
--HASH JOIN | TABLE ACCESS FULL|TABLE ACCESS FULL
select NomCh,CodeCh from CHERCHEUR, EQUIPE where CHERCHEUR.CodeEq = EQUIPE.CodeEq and NomEq = 'SMM';
--Q5
--Ecoule : 00 :00 :00.01
--MERGE JOIN CARTESIAN trie fusion
--HASH JOIN | MERGE JOIN CARTESIAN |BUFFER SORT | TABLE ACCESS FULL|TABLE ACCESS FULL
select NomCh,CodeCh from CHERCHEUR, EQUIPE, LABORATOIRE where CHERCHEUR.CodeEq = EQUIPE.CodeEq and EQUIPE.CodeLabo = LABORATOIRE.CodeLabo and NomLabo = 'IRIT';

--Exo 5
--a
--detecter la cle TRV_CH
select CONSTRAINT_NAME from USER_CONSTRAINTS
 where TABLE_NAME = 'TRAVAILLER';
--detecter la cle KEY_CHERCHEUR
select CONSTRAINT_NAME from USER_CONSTRAINTS
 where TABLE_NAME = 'CHERCHEUR';
--detecter la cle KEY_THEME
select CONSTRAINT_NAME from USER_CONSTRAINTS where TABLE_NAME = 'THEME';
--detecter la cle TRV_TH
select CONSTRAINT_NAME from USER_CONSTRAINTS
 where TABLE_NAME = 'TRAVAILLER';
-- KEY_LABO
select CONSTRAINT_NAME from USER_CONSTRAINTS where TABLE_NAME = 'LABORATOIRE';
--KEY_EQUIPE
select CONSTRAINT_NAME from USER_CONSTRAINTS where TABLE_NAME = 'EQUIPE';
--desactivons la cle
--utilite de cascade : supprime toutes les dependances (cle etrangere avant)
alter table TRAVAILLER disable constraint TRV_CH cascade;
alter table CHERCHEUR disable constraint KEY_CHERCHEUR cascade;
alter table EQUIPE disable constraint KEY_EQUIPE cascade;
alter table LABORATOIRE disable constraint KEY_LABO cascade;
--b Les requetes Q1 Q2 Q3 Q4 Q5