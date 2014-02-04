(* Fichier graphe.ml - 16 septembre 2013
   Maîtrise d'Informatique - module TRP - 2013-2014

   Ce fichier contient des graphes sur lesquels tester un
   algorithme de recherche dans un graphe d'état.

*)

(* Une description du graphe g1 de l'énoncé*)
let estBut1 = (function "H" -> true | "I" -> true | _ -> false) ;;
let estBut1bis =(function "I"->true |_-> false );;
let estBut1ter =(function _-> false );;
let etatsSuivants1=(function 
    "A" -> ["C";"B"] 
  | "B" -> ["D";"E"] 
  | "C" -> ["F";"D"] 
  | "D" -> ["I"]
  | "E" -> ["I"]
  | "F" -> ["G";"H";"I"] 
  | _ -> [] );;

let opPoss1 = (function
    "A" -> [('b',"C",3);('h',"B",4)] 
  | "B" -> [('b',"D",7);('h',"E",4)] 
  | "C" -> [('d',"F",9);('g',"D",2)] 
  | "D" -> [('h',"I",6)]
  | "E" -> [('b',"I",4)]
  | "F" -> [('d',"G",7);('b',"H",9);('h',"I",7)] 
  | _ -> [] );;
let hEtat1 = (function
    "A" -> 7
  | "B" -> 3	
  | "C" -> 5
  | "D" -> 2
  | "E" -> 2
  | "F" -> 7
  | _ -> 0 );;

(* Description du graphe g2 *)
let estBut2 = (function "G" -> true | "H" -> true | _ -> false) ;;
let etatsSuivants2 =(function
    "A" -> ["B";"C"]
  | "B" -> ["E";"D"]
  | "C" -> ["D";"F"]
  | "D" -> ["G"]
  | "E" -> ["B";"G"]
  | "F" -> ["G";"H"]
  | _ -> [] );;

let opPoss2 = (function
    "A" -> [('h',"B",4); ('b',"C",3)]
  | "B" -> [('h',"E",7); ('b',"D",5)]
  | "C" -> [('h',"D",2); ('b',"F",9)]
  | "D" -> [('h',"G",6)]
  | "E" -> [('h',"B",1);('b',"G",2)]
  | "F" -> [('h',"G",7); ('b',"H",9)]
  | _ -> [] );;
let hEtat2 = (function
    "A" -> 7
  | "B" -> 3	
  | "C" -> 6
  | "D" -> 4
  | "E" -> 1
  | "F" -> 7
  | _ -> 0 );;

(* Description du graphe g3 *)
let estBut3 = (function "G" -> true | "H" -> true | _ -> false) ;;
let etatsSuivants3 = (function
    "A" -> ["B";"C"]
  | "B" -> ["B"; "E";"D"]
  | "C" -> ["D"; "F"]
  | "D" -> ["G"; "F"]
  | "E" -> ["D";"G"]
  | "F" -> ["G"; "H"]
  | _ -> [] );;
let opPoss3 = (function
    "A" -> [('h',"B",4); ('b',"C",2)]
  | "B" -> [('d',"B",2); ('h',"E",7); ('b',"D",2)]
  | "C" -> [('h',"D",3); ('b',"F",9)]
  | "D" -> [('h',"G",4); ('b',"F",1)]
  | "E" -> [('h',"D",1);('b',"G",2)]
  | "F" -> [('h',"G",7); ('b',"H",9)]
  | _ -> [] );;
let  hEtat3 = (function
    "A" -> 7
  | "B" -> 3	
  | "C" -> 6
  | "D" -> 4
  | "E" -> 1
  | "F" -> 7
  | _ -> 0 );;

(* g4 permet de tester la gestion de la pile d'attente:
  l'état c est mis en attente comme fils de a, associé
  à un coût de 10, mais en traitant le premier fils de a,
  qui est b, on rencontre à nouveau c associé cette
  fois-ci à un coût de 6: il faut donc modifier la pile
  d'attente.
*)

let estBut4 =(function "F" -> true | "G" -> true | _ -> false);;
let etatsSuivants4 = (function
	 "A"-> ["B";"C"]
	| "B"-> ["C"; "D"]
	| "C"-> ["F"]
	| "D"-> ["C"]
	|  _ -> []) ;;

let opPoss4 =(function
	 "A"-> [('h',"B",4); ('b',"C",10)]
	| "B"-> [('b',"C",2); ('h',"D",4)]
	| "C"-> [('b',"F",6)]
	| "D"-> [('b',"C",2)]
	|  _ -> []) ;;
let  hEtat4 =(function
      "A"->8
	| "B"->3
	| "C"->2
	| "D"->5
	|  _ ->0) ;;


(* g5 permet de tester la gestion de la liste des
    états vus: a a deux successeurs b et c. b ne
    permet pas d'arriver à l'état but à un coût optimal,
    il faut d'abord passer par c qui revient ensuite sur
    b avec un coût inférieur, alors que b est déjà dans vus.
*)

let  estBut5 = (function "D" -> true | _ -> false) ;;
let etatsSuivants5=(function
    "A" -> ["B";"C"]
  | "B" -> ["D"]
  | "C" -> ["B"]
  | "D" -> []
  | _->[] ) ;;
let  opPoss5 = (function
    "A" -> [('h',"B",10) ; ('b',"C",4)]
  | "B" -> [('h',"D",5)]
  | "C" -> [('h',"B",4)]
  | "D" -> []
  | _->[] ) ;;
let  hEtat5 = (function
    "A" -> 10
  | "B" -> 2
  | "C" -> 5
  | "D" -> 0
  |_->0) ;;


(* g6 permet de tester la gestion des cycles: c'est une
  boucle à deux noeuds sans état but. *)
let  estBut6 = (function _ -> false) ;;
let etatsSuivants6=(function
    "A" -> ["B"]
  | "B" -> ["A"]
  |_->[]) ;;
let  opPoss6 = (function
    "A" -> [('h',"B",2)]
  | "B" -> [('h',"A",2)]
  |_->[]) ;;
let  hEtat6 = (function
    "A"-> 4
  | "B" -> 3
  |_->0) ;;

