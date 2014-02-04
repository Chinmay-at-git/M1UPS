let rec profondeurV2 fileatt vus=match fileatt with
[]->failwith "pas d'etats but"
|x::res->if (estBut2 x) then x else let fils=etatsSuivants2 x in let rest= ajoute res fils  in  if( appartient x vus) then profondeurV2 res vus  else let vus2=x::vus in  profondeurV2 rest vus2;;


let prem l=match l with
[]->failwith"liste vide"
|x::res->x;;



let rec transfo l=match l with
[]->[]
|x::res -> [x]:: transfo res;;

let rec creerfils file chemin=match file with
[]->[]
|f::rest->(f::chemin)::(creerfils rest chemin);;

let rec profondeurV3 fa vu=match fa with
[]-> failwith " pas de solution"
|ch::restefa-> match ch with
   []-> failwith " erreur dans le chemin"
   |e::restech-> if (estBut2 e) then ch 
                 else if (List.mem e vu) 
                      then profondeurV3 restefa vu 
                      else  let fils= etatsSuivants2 e in 
                                let fils1= creerfils fils ch in 
                                       profondeurV3 (fils1@restefa) (e::vu) ;;

let rec creerfils2 l opere coupere=match l with
[]->[]
|(op,et,cout)::res->(et,op::opere,cout+coupere)::creerfils2 res opere coupere;;

let rec profondeurV4 fa vu=match fa with
[]-> failwith " pas de solution"
|(et,op,cout)::restfa -> if (estBut2 et) then (et,op,cout) 
                    else if ( List.mem et vu) then (profondeurV4 restfa vu) 
                            else profondeurV4((creerfils2 (opPoss1 et) op cout)@restfa) (et::vu);;