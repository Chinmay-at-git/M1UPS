(*
Diallo Alpha Oumar Binta
groupe 3.2 IHM
21007631, adiall14
#use "tp1.ml";;
profondeurV2(["A"],[]);;
*)
#use "graphes.ml";;
let rec profondeurV1 = function
	[]->failwith "pas de solution"
	|t::q->if estBut1(t)
           then 
                t 
           else 
                profondeurV1((etatsSuivants1 t)@q)
;;

let rec appartient = fun el liste ->
    match liste with
    []->false;
    |t::q->if t=el then true else appartient el q
;;

let ajoute = fun el liste -> liste::el;;

let rec profondeurV2 = fun fileAttente vus->
    match fileAttente with
    []-> failwith "pas de solution"
    |t::q->if estBut2(t) then t
                  else
                     (* fils de l'etat courant*)
                     let fils = etatsSuivants2 t in
                     (*reste de la file queue+fils de l'etat courant*)
                     let reste =  q@fils in
                     (* si l'etat est deja vu (present dans la liste vus), on evite de le developper, on passe a l'etat suivant, queue*)
                     if(appartient t vus) then profondeurV2 q vus
                     else profondeurV2 reste (t::vus)
;;
let rec creerfils = fun fileAttente path->
    match fileAttente with
    []->[]
    |t::q->(t::path)::(creerfils q path)
;;

let rec profondeurV3 =fun fileAttente vus ->
    match fileAttente with
    []-> failwith "pas de solution"
    |path::resteF-> match path with
                    []-> failwith "erreur au niveau du chemin"
                    |etat::restePath-> if(estBut2 etat) then path
                                       else if (appartient etat vus) then
                                       profondeurV3 resteF vus
                                       else let etatSuiv = etatsSuivants2 etat in
                                       let fils = creerfils etatSuiv path in
                                       profondeurV3 (fils@resteF) (etat::vus)
;;

let rec profondeurV2 = function
    []->failwith "pas de solution"
    |(etat,valeur)::resteF -> if(estbut1 etat) then (etat,valeur)::[]
                              else (etat,valeur)::(profondeurV2 (ajouterFils (opPoss1 etat) resteF (valeur - (hEtat1 etat))))
    | (etat,valeur, chemin)::r -> if (estBut1 etat) then (chemin,valeur)
    else (profondeurV2 (ajouterFils (opPoss1 etat) r (valeur - (hEtat1 etat)) chemin))
;;
    