drop table CHERCHEUR cascade constraint;
drop table LABORATOIRE cascade constraint;
drop table EQUIPE cascade constraint;
drop table theme cascade constraint;
drop table travailler cascade constraint;
-- creation de la base

create table CHERCHEUR
( CodeCh number(5) constraint Key_Chercheur PRIMARY KEY,
  NomCh varchar(20),
  CodeEq Number(5),
  Salaire Number(5));

create table LABORATOIRE
( CodeLabo number(5) constraint Key_Labo PRIMARY KEY,
  Type varchar(5) constraint Type_labo Check (Type in ('UNIV', 'INRIA', 'CNRS')),
  NomLabo varchar(20),
  URL varchar(15),
  CodeDir number(5),
  constraint Dir_Labo Foreign key (CodeDir) references CHERCHEUR (CodeCh));

create table EQUIPE
( CodeEq number(5) constraint Key_Equipe PRIMARY KEY,
  NomEq varchar(20),
  CodeResp number(5),
  CodeLabo number(5),
  DateCrea date,
  Budget number(5),
  constraint Resp_Equipe foreign key (CodeResp) references CHERCHEUR (CodeCh));

Alter table CHERCHEUR
add constraint Eq_Ch foreign key (CodeEq) references EQUIPE (CodeEq);

 create table THEME
 (CodeTh number(5) constraint Key_Theme PRIMARY KEY,
  Libelle varchar(35));
  
  create table TRAVAILLER
  ( CodeCh number(5),
    CodeTh number(5),
    constraint Trv_Ch foreign key (CodeCh) references CHERCHEUR (CodeCh),
    constraint Trv_Th foreign key (CodeTh) references THEME (CodeTh));
    




  
