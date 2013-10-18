(*
Diallo Alpha Oumar Binta
Mise à niveau Ocaml
21007631
*)
(*Fonction est_pair de type bool*)
let est_pair = 
    let rec calcul = function
         0->true
        |1->false
        |n->calcul(n-2)
    in
        fun x -> calcul(abs x)
;;
(*Fonction max de 3 elements de type quelconques*)
let max2 = fun x y -> if x>y then x else y;;
let max = fun x y z ->
    let max_xy = max2 x y in
    let max_yz = max2 y z in
    max2 max_xy max_yz 
;;
(*Fonction syracuse qui admet un seul argument de type entier, elle renvoie son
argument divisé par 2 s'il est pair et renvoie (3 fois son argument) plus 1 
sinon*)
let syracuse(x:int) =
    if est_pair x then
        x/2
    else
        3*x+1
;;
(*Fonction factorielle*)
let factorielle = 
    let rec fact = function
         0->1
        |x->x*fact(x-1)
    in fun n-> if n>=0 then fact n else failwith "Erreur nombre negatif"
;;
(*Fonction est_pair récursivement sans utiliser le chiffre 2. Expliquez les
résultats obtenus avec 100 millions et -6.*)
let est_pair2 = 
    let rec impair = function
         1->true
        |0->false
        |n->impair(n-1)
    in
        fun x-> let res = impair x in
         if res then false
         else true
;;
(*Fonction qui affiche (utiliser print_int) les résultats des applications
successives de la fonction syracuse à un nombre n, puis au résultat obtenu,
etc., jusqu'à atteindre le
nombre 1, qu'elle affiche également.*)
let affiche(n:int) =
    let rec successives=function
        |0->print_int(1)
        |n->(print_int(syracuse(n)); print_newline(); successives(n-1))
    in successives n
;;
(*Fonction qui inverse une chaîne de caractères (utiliser String.sub et
String.length).*)
let inverse_chaine = fun x->
    let rec inverse = function
        |0 -> print_newline()
        |long ->(print_string(String.sub x (long-1) 1); inverse(long-1))
    in inverse (String.length x)
;;

(*Fonction insererEnTete qui insère un élément x de type quelconque en tête
d’une liste l et renvoie la nouvelle liste*)
let insererEnTete = fun x liste ->
    match liste with
    |[]->x::liste
    |head::tail->x::liste
;;
(*Fonction insererEnQueue qui insère un élément de type quelconque en queue
d’une liste et renvoie la nouvelle liste *)
let insererEnQueue = fun x liste ->
    match liste with
    |[]->x::liste
    |head::tail->(let newliste = x::[] in liste@newliste)
;;
(*Fonction somme qui retourne la somme de tous les éléments d’une liste
d’entiers*)
let rec somme = function
    []->0
    |t::q->t+somme(q)
;;
(*Fonction maximum qui retourne la valeur maximale contenue dans une liste 
d’entiers *)
let rec maximum = function
    []->failwith "liste vide"
    |[a]->a
    |t::q-> max2 t (maximum q)    
;;
(*Fonction insererEntierDansListeOrdonnee qui insère un entier au bon endroit
dans une liste ordonnée d’entiers triés par valeurs croissantes.*)
let rec insererEntierDansListeOrdonnee = fun x liste->
    match liste with
    []->x::liste
    |t::q->if x<t then insererEnTete x liste
           else t::insererEntierDansListeOrdonnee x q
;;


