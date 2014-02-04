
/**
@page DevoirCSG DEVOIR : Arbres CSG en lancer de rayons

L'objectif de ce devoir est de construire et de visualiser des objets complexes définis par des arbres CSG.

\b ATTENTION : veuillez récupérer l'archive <A HREF="../raytracing.tgz">raytracing.tgz</a> contenant les outils
de base pour la gestion de la CSG qui ont été ajoutés par rapport à votre archive de TP. Ces outils concernent les classes
CSGNode, CSGUnion, CSGIntersection, CSGDifference et IntervalSet ainsi que quelques évolution de la structure interne du moteur.

Dans le fichier main.cpp, réintégrez les fonctions compute_image(), trace_ray() et compute_direct_lighting()
que vous avez écrites en TP (avec, éventuellement, toute autre fonction que vous avez écrites).
Ensuite, veuillez re-effectuer la première étape de compilation comme indiqué dans la section \ref compilation_premiere
de cette documentation. (mkdir build && cd build && cmake .. && make) ou l’équivalent via votre EDI.

Votre devoir sera évalué par le code que vous aurez fourni et validé par le calcul de l'image suivante, dont
la scène est construite par la fonction make_test_scene() :

\image html csg.png


\section  CSGSection Constructive Solid Geometry
\subsection CSGDefinition Définition
Lorsque l'on souhaite définir des formes complexes pour la CAO (Conception Assistée par Ordinateur) et la fabrication
de pièces mécaniques, de nombreuses méthodes existent. Parmi celles-ci, La CSG (en anglais,  "Constructive Solid Geometry")
consiste à assembler de manière ensembliste des solides fondamentaux pour créer des solides complexes.
Ainsi, à partir d'un ensemble de solides simples (sphère, cône, cylindre, parallélépipède rectangle (ou boite), ...) et
des opérateurs ensemblistes union, intersection et différence, il est possible de créer des objets complexes pouvant
ensuite être directement fabriqués par usinage ou impression 3D.
\image html teaser.jpg

Si l'on se limite aux opérateurs ensemblistes binaires union, intersection et différence, un arbre CSG peut se représenter comme
sur l'image suivante.
\image html csg_tree.png

Aux feuilles de l'arbre, on retrouve nos primitives géométriques qui sont combinées deux à deux par les opérateurs.
Si l'on se ramène à notre API, le noeud racine aura été créé par la fonction create_csg_difference().

Si l'on développe cet arbre avec notre API, cet objet est construit par l'expression

\code
create_csg_difference (
                      create_csg_intersection (
                                              create_box(...),
                                              create_sphere(...)
                      ),
                      create_csg_union(
                                        create_cylinder(...),
                                        create_csg_union(
                                                         create_cylinder(...),
                                                         create_cylinder(...)
                                        )
                      )
)
\endcode
Cet arbre, correspondant à l'objet au premier plan de l'image de validation que vous obtiendrez en fin
de devoir peut aussi être exprimé par l'expression de style LISP suivante
\code
(- (* (bo 0. 2.5 -3.25 1. 0. 0. 0. 0. 1. 1.0 1.0 1.0) (sp 0. 2.5 -3.25 0.65) ) (+ (cy 0. 2.5 -3.25 1.0 0.0 0.0 0.3 1.75) (+ (cy 0. 2.5 -3.25 0.0 1.0 0.0 0.3 1.75) (cy 0. 2.5 -3.25 0.0 0.0 1.0 0.3 1.75) ) ) )
\endcode

\subsection CSGRayTracing Intersection entre un rayon et un arbre CSG
Lorsque l'on souhaite visualiser un arbre CSG en lancer de rayons, on se ramène à un problème d'évaluation
d'opérations sur des ensembles représentés par des intervalles. En effet, l’ensemble des points communs à un rayon et un solide
peut être représenté par une collection d’intervalles réels [tmin, tmax] dans le repère du rayon (i.e. l'espace 1D définit par
l'équation paramétrique du rayon P(t) = O + tD ). Les bornes de ces intervalles correspondent aux évènements d'entrée/sortie du 
rayon dans le solide.

La structure de données IntervalSet stocke les intervalles par leurs évènements d'entrée/sortie (de type Bound) en
considérant qu'un évènement d'entrée sera obligatoirement suivi d'un évènement de sortie.
Cette propriété est à la base du fonctionnement des opérateurs ensemblistes qui sont utilisés pour
calculer l'intersection entre un rayon et un arbre CSG.
Ce calcul d’intersection est donc un problème similaire à un problème d'évaluation d'expressions
arithmétiques et l’arbre CSG est assimilable à un arbre de syntaxe abstraite tel que vous les avez vu en traduction des langages. 

Concernant les noeuds primitives géométriques, Sphere, Cylinder, Cone et Box3D, qui sont des solides convexes, il y a au plus un seul intervalle possible représentant l’intersection entre un rayon et ce solide.
Les méthodes Sphere::clip(), Cylinder::clip(), Cone::clip() et Box3D::clip() calculent cet intervalle, à partir des coordonnées
t sur le rayon, d'entrée et de sortie de la primitive.

Concernant les noeuds opérateurs CSGUnion, CSGIntersection et CSGDifference, il peut y avoir plusieurs intervalles
d'intersection entre le rayon et le noeud. Ces intervalles sont calculés par les méthodes CSGUnion::clip(),
CSGIntersection::clip() et CSGDifference::clip() à partir des intervalles évalués sur les deux arguments de
l'opérateur. Le comportement de ces opérateurs sur des intervalles peuvent s'illustrer comme sur le tableau suivants.
Dans ce tableau, La première ligne représente le résultat de l’opération entre un cube et une sphère, la seconde ligne schématise le comportement des opérateurs sur des intervalles. Dans ces schémas, une ligne représente l'espace paramétrique 1D d'un rayon. Une portion bleue indique que le rayon
est en dehors de la primitive, une portion rouge que le rayon est à l'intérieur d'une primitive. Les transitions
entre ces deux zones sont les informations calculées par la méthode polymorphe Geometry::clip() et définissent les bornes des intervalles.

<table border="1" style="margin: 1em auto; text-align: center; border-collapse: collapse; border-color: #aaa;">
<tr>
<th align="center" colspan="3">Opérateurs ensembliste sur les intervalles</th>
</tr>
<tr>
<td>Union</td>
<td>Intersection</td>
<td>Différence</td>
</tr>
<tr>
<td width="250"><img alt="Union" src="../images/boolean_union.png" width="250" /></td>
<td width="250"><img alt="Intersection" src="../images/boolean_intersection.png" width="250" /></td>
<td width="250"><img alt="Difference" src="../images/boolean_difference.png" width="250" /></td>
</tr>
<tr style="vertical-align: bottom;">
<td width="250"><img alt="Octaèdre" src="../images/union.png" width="250"/></td>
<td width="250"><img alt="Dodécaèdre" src="../images/intersection.png" width="250"/></td>
<td width="250"><img alt="Icosaèdre" src="../images/difference.png" width="250"/></td>
</tr>
</table>

Le principe algorithmique de ces opérateurs reposent sur la notion d'intérieur/extérieur (appelée parité) par rapport à une
primitive. Lorsque l'on parcours la collection d'intervalles (représentés par des évènements), le premier
évènement rencontré (d'abscisse t minimale) est obligatoirement un évènement d'entrée dans la primitive.
Dans la même collection d'intervalle, l'évènement suivant sera alors obligatoirement une sortie, suivie
éventuellement d'une entrée, etc... Le dernier évènement sera obligatoirement une sortie.

Ces opérateurs parcourent en simultané les deux collections d'intervalles associées aux deux arguments de l'opérateur en traitant les évènements dans l’ordre arithmétique, du plus petit au plus grand.
En fonction de la position intérieur/extérieur (de la parité) dans chaque collection et de la sémantique de l'opérateur,
une collection résultante contenant tout ou partie des évènements des deux collections initiales est crée.
Pour l’opération d’union, par exemple, un évènement ne sera ajouté dans l’ensemble résultant uniquement s’il fait passer de l’extérieur des deux objets à l’intérieur d’un seul ou réciproquement. Un évènement faisant passer de l’intérieur d’un objet à l’intérieur des deux, ou réciproquement, ne sera pas ajouté dans l’ensemble résultant.

Lorsque les évènements d'entrée/sortie du solide ont étés calculés à la racine de l'arbre, l'algorithme
du lancer de rayons conserve le plus proche de l'origine du rayon dans le sens positif qui caractérise alors le point
d'intersection entre le rayon et l'arbre.



\section TRDV3 Travail à réaliser
\subsection TRDV3_1 Programmation d'opérateurs ensemblistes pour le lancer de Rayons
Afin de pouvoir visualiser en lancer de rayons les arbres CSG, il ne manque à notre logiciel de lancer de
rayons que 3 fonctions de traitement des opérateurs ensemblistes sur nos collections d'intervalles.
Dans le fichier intervaloperators.cpp (situé dans le répertoire main), vous devrez programmer les trois opérateurs
union_of_intervals(), intersection_of_intervals() et difference_of_intervals().

Vous pouvez programmer autant de fonctions annexes que vous le souhaitez, la seule contrainte est de
programmer ces trois opérateurs en respectant scrupuleusement leur interface et leurs documentation.

Après avoir écrit ces opérateurs, si vous lancez le programme sans avoir modifié la fonction make_test_scene(),
vous devriez obtenir l'image suivante.
\image html operateurs.png

\subsection TRDV3_2 Construction d'un arbre CSG à partir d'une chaine de caractère
Comme nous l'avons vu dans la section \ref CSGDefinition, un arbre CSG correspond à un programme puisqu'il définit
une arbre de syntaxe abstraite pour l’évaluation d'opérateurs ensemblistes. Afin de pouvoir facilement créer des objets objets
complexes, nous souhaitons ajouter à notre lancer de rayon la possibilité de traduire une expression LISP-like
définissant un arbre CSG en un objet de type Geometry qui pourra être ajouté à la scène.

On définit notre langage de description d'arbre CSG de la façon suivante :
\code
  Objet :
    Sphere = (sp pos_x pos_y pos_z radius)
            -- sphére définie par son centre et son rayon
    Cylinder = (cy pos_x pos_y pos_z axis_x axis_y axis_z radius length)
            -- cylindre définit par son centre son axe, son rayon et sa longueur
    Cone = (co pos_x pos_y pos_z vertex_x vertex_y vertex_z radius)
            -- cone définit par le centre de sa base, son sommet et le rayon de sa base
    Box3D = (bo pos_x pos_y pos_z baseX_x baseX_y baseX_z baseY_x baseY_y baseY_z size_x size_y size_z)
            -- boite définie par son centre, deux vecteurs définissant son plan de base et les longueurs des aretes
  Operateur :
    CSGUnion        : (+ Operateur|Objet Operateur|Objet)
    CSGIntersection : (* Operateur|Objet Operateur|Objet)
    CSGDifference   : (- Operateur|Objet Operateur|Objet)
\endcode

Programmez la fonction csg_parse(), dans le fichier csg_parser.cpp qui, à partir d'une chaine de caractère contenant
la description de l'arbre à visualiser, construit le noeud Geometry correspondant.
Lorsque cette fonction aura été écrite, en lançant le programme sans avoir modifié la fonction  make_test_scene(),
vous devriez obtenir l'image suivante dont l'objet en bas au centre est défini par la chaine :
\code
(- (* (bo 0. 2.5 -3.25 1. 0. 0. 0. 0. 1. 1.0 1.0 1.0) (sp 0. 2.5 -3.25 0.65) ) (+ (cy 0. 2.5 -3.25 1.0 0.0 0.0 0.3 1.75) (+ (cy 0. 2.5 -3.25 0.0 1.0 0.0 0.3 1.75) (cy 0. 2.5 -3.25 0.0 0.0 1.0 0.3 1.75) ) ) )
\endcode
\image html csg.png


\subsection BAREME Fichiers attendus, barème et notation
Vous devez déposer sous moodle une archive au format tar.gz (et uniquement à ce format là) nommée :
prénom.nom-OIMD3.tar.gz (remplacez prénom et nom par VOTRE prénom et VOTRE nom).

Cette archive devra contenir UNIQUEMENT :
<ul>
<li>les répertoires main et coreraytracer</li>
<li>le fichier racine CMakeLists.txt</li>
<li>éventuellement un document au format pdf ou texte contenant les
informations que vous souhaitez communiquer sur votre travail
(Liste des fichiers modifiés, références bibliographiques, ajouts faits par rapport au sujet,
bugs trouvés et corrigés, bug trouvés et non corrigés, bugs rajoutés, ...)</li>
</ul>

Ce devoir sera évalué et noté de la façon suivante :
<ol>
<li>Respect des consignes de dépot : 2 points</li>
<li>Compilation : 3 points
<ul>
<li>Si la compilation échoue, la note 0 sera donnée à cette partie et la correction s'arrêtera là</li>
</ul></li>
<li>Execution : 5 points
<ul><li>Si l'exécution du programme obtenu correspond uniquement au TP ou si le programme ne fonctionne pas,
la note 0 sera donnée à cette partie et la correction s'arrêtera là.</li>
<li>Il sera compté 1 point par opérateur fonctionnant (union, intersection et différence) et 2 points si
la fonction csg_parse() fourni la bonne forme.</li>
</ul></li>

<li>Par opérateur, la qualité du code apportera 2 points au maximum. Les critères évalués seront la lisibilité, l'efficacité et l'élégance algorithmique.</li>
<li>Pour l'analyseur syntaxique, 2 points maximum seront ajoutés en fonction de sa robustesse, de son extensibilité (est-il simple de rajouter un opérateur ou un objet de base ?) et de la qualité de son code.</li>
<li>\b BONUS : 2 points de bonus seront attribués en fonction des différentes extension que vous avez ajouté par rapport au sujet :
<ul>
<li>Création d'objets complexes ou mise en scène originale</li>
<li>Extension de l'analyseur pour permettre la définition de "variables"</li>
<li>Association d’un matériau différent à chaque feuille de l’arbre CSG</li>
<li>Transformation du lancer de rayon en programme multi-thread</li>
<li>Toute surprise agréable et inattendue ... laisser aller votre imagination!</li>
</ul>
</ol>




*/
