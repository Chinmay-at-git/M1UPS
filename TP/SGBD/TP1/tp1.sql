/*Question 1*/
Create or replace view CHERCHEUR_2400 as select CodeCh, NomCh, Salaire
     from CHERCHEUR where salaire > 2400;
insert into CHERCHEUR values(15,'Thierry',2,2600);
/* On remarque que la vue a ete mise a jour, en inserant thierry dans la table
chercheur avec un salaire superieur a 2400, il a ete rajoute sur la vue*/

/*Question 2*/
create or replace view CHERCHEUR_EQ1 as select CodeCh, NomCH
    from CHERCHEUR where CodeEq=1;
insert into CHERCHEUR values(14,'RENAUD',1,1000);
update CHERCHEUR_EQ1 set NomCh='RENAUDIN' where CodeCh = 14;
/* en modifiant la vue, la table est aussi modifié */
insert into CHERCHEUR(CodeCh, NomCh) values(18,'LALANDE');
/* LALANDE n'est pas visible dans la vue CHERCHEUR_EQ1 car son son CodeEq est nulle*/
delete from CHERCHEUR where CodeCh=18;

/*Question 3*/
create or replace view CHERCHEUR_EQUIPE as select CodeCh, NomCH, NomEq,CodeResp as Resp_Eq
    from CHERCHEUR, EQUIPE where CHERCHEUR.CodeEq = EQUIPE.CodeEQ;
select * from CHERCHEUR_EQUIPE where NomEq= 'FIRM';
update CHERCHEUR_EQUIPE set NomCh='Thierry Henry' where CodeCh = 15;
update CHERCHEUR_EQUIPE set NomEq='SIMPA' where CodeCh = 15;
/* la premiere mise a jour de la ligne marche, mais si on veut mettre a jour a partir du nom de l'equipe, le changement est impossible car la colonne correspond a une table non protogee par la cle (CodeEq est absent)*/

/*Question 4*/
create or replace view BUDGET_LABO as select CodeLabo, avg(Budget) as moyenne from EQUIPE group by CodeLabo;
/* il n'est pas possible de mettre a jour une vue statique comportant une fonction d'agregat */

/* Exercice 2*/
/*Question 1
Pour affceter un charcheur a plusieurs equipes, il nous faut modifier le schema relationnel, donc cree une nouvelle table CHERCHEUR_EQ contenant le CodeCh et le CodeEq puis supprimer la colonne CodeEQ dans la table CHERCHEUR
*/

create table CHERCHEUR_EQ
( CodeCh number(5) ,
  CodeEq Number(5),
  constraint Code_Ch Foreign key (CodeCh) references CHERCHEUR (CodeCh),
  constraint Code_Eq Foreign key (CodeEq) references EQUIPE (CodeEq),
  constraint key_CHERCHEUR_EQ primary key (CodeCh, CodeEq));
insert into CHERCHEUR_EQ (CodeCh, CodeEq) (select codeCh, CodeEq from CHERCHEUR);
alter table CHERCHEUR drop (CodeEq);