 *******************************
*       GARNIER Arnaud          *
*          - SI4 -              *
*       Polytech Nice Sophia    *
 *******************************

 -> Travail réalisé :

Dans ce rendu du projet, il a fallu adapter le code de camshift/facedetect avec le code letter_recog 
afin de reconnaître des lettres du langage des signes, faites avec la main.
Nous avons choisi ici de reconnaître 4 lettres relativement distinctes : A, B, C et Y.
Dans le code de letter_recog, on a conservé uniquement l'algorithme mlp.
La topologie choisie dans letter_recog est une topologie 3 couches à 8 neurones.
Dans le code de camshift/facedetect, on a récupéré la fonction permettant de charger le fichier
d'apprentissage (on a ajouté en dur dans le code qu'il faut charger le fichier nommé letter.yaml 
au démarrage du programme).
Pour ce qui est de la détection, elle s'effectue avec la méthode predict. On appelle cette fonction
sur le fichier d'aprentissage chargé. Le résultat de cet appel est un double, que l'on pourra
afficher sur le terminal sous forme de lettre de l'alphabet après conversion.

-------------------------------------------------------------------------------------------------------

 -> Comment exécuter le code ?

Il faut lancer letter_recog avec les options -mlp, -data=letter.txt et -save=letter.yaml. Il suffit par
la suite de lancer camshift/facedetect (cf. ci-dessus).
Pour détecter une lettre, on reproduit avec la main le signe puis on appuie sur ESPACE pour l'afficher
sur le terminal.

Remarque : la détection des lettres a été plus efficace après avoir mélangé les lignes du fichier de 
données (letter.txt) avec la commande unix shuf.

-------------------------------------------------------------------------------------------------------

 -> Analyse :

Pour ce qui est de la topologie du réseau :
- De base, le programme met en place une topologie de réseau à 2 couches composées chacune de 100 neurones.
  Dans notre cas, on ne va s'intéresser qu'à un nombre réduit de lettres. On pourra donc réduire cette valeur :
  ici, la reconnaissance est optimisée pour une topologie de 3 couches à 8 neurones chacune.
  On remarque que la détection des lettres se passe plutôt bien avec cette topologie (taux de test à environ 90%).
- Si on ajoute trop de couches, le recognition rate n'est plus à 100% et le programmme ne reconnait presque plus 
  certaines lettres. La notion de "trop de couches" dépend du nombre de neurones sur chaque couche. Par exemple,
  avec la topologie 2 couches, 4 neurones sur chaque couche, le recognition rate n'est plus à 100% à partir de 3
  couches. Par contre, pour si on met 50 neurones par couche, on peut ajouter une troisième couche et conserver 
  une recognition rate de 100%. Le fait d'ajouter des couches augmente le temps d'apprentissage, tout
  comme le fait d'augmenter le nombre de neurones sur chaque couche.
- Pour une unique couche à 800 neurones, le temps de calcul augmente fortement (on passe d'une dixaine de secondes
  à environ 2 minutes pour l'apprentissage). De plus, le programme détecte très mal les lettres et renvoie parfois
  même des lettres qui ne sont pas apprises par le programme. Les couches uniques avec un nombre important de neurones
  donnent, dans notre cas, de très mauvaises détections des lettres.
- La limite de topologie qui ne fait pas baisser les performances est la topologie 3 couches de 20 neurones. Au delà,
  on note soit une mauvaise détection des lettres, soit un temps de calcul plus long (avec un résultat de détection
  similaire).
- On note une ambiguïté pour la reconnaissance des lettres A et Y : ceci est dû au fait que la fenêtre de détection
  tronque la main au niveau de l'auriculaire. Pour appuyer cette constatation, on fait un test de reconnaissance
  pour ces deux lettres. Le test sur les A donne un résultat de tests à 41.0% et le Y donne un taux de reconnaissance
  de 20.6%. Il faudra donc refaire les acquisitions pour la lettre Y après avoir redimensionné le rectangle autour 
  de la main.
- Concernant la qualité de la détection, les acquisitions ont été effecutées pour la plupart dans la même salle.
  L'acquisition du Y a été faite dans une autre salle, avec un autre environnement lumineux. Cela expliquerait
  également la mauvaise détection de cette lettre par rapport aux autres lors de la démonstration.

