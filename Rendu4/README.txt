 *******************************
*       GARNIER Arnaud          *
*          - SI4 -              *
*       Polytech Nice Sophia    *
 *******************************

 -> Travail réalisé :

Dans ce rendu du projet, le but était d'améliorer la qualité du programme de détection du langage des
signes. Les objectifs d'amélioration que j'ai entrepris étaient l'application d'ouvertures/fermetures
et errosion/dilatation avec morphomaths ainsi que la détection des contours de la main. Ce deuxième
objectif n'a pas pu être obtenu en raison d'une erreur que je n'ai pu résoudre (voir plus bas pour
plus de détails).

-------------------------------------------------------------------------------------------------------

 -> Comment exécuter le code ?

Il faut lancer letter_recog avec les options -mlp, -data=letter.txt et -save=letter.yaml. Il suffit par
la suite de lancer facedetect.cpp.
Pour détecter une lettre, on reproduit avec la main le signe puis on appuie sur ESPACE pour l'afficher
sur le terminal.

Remarque : la détection des lettres a été plus efficace après avoir mélangé les lignes du fichier de 
données (letter.txt) avec la commande unix shuf.

-------------------------------------------------------------------------------------------------------

 -> Analyse :

- Application du filtre morphomaths :
J'ai tout d'abord réduit la taille des points des fonctions d'errosion/dilatation pour affiner
les résultats. Le constat de cette méthode est assez immédiat : de meilleurs résultats à la
reconnaissance. Ceci peut s'expliquer notamment par l'élimination d'une partie du bruit autour
de la main. Cependant, en cas de trop forte dilatation, la reconnaissance devient mauvaise
(très peu de détails apparaissent sur la main, le programme reconnait toujours la même lettre).
De même, si on applique une trop forte errosion, la main très peu visible (se confond presque
avec le fond de la pièce).
- Détetcion des contours :
Je n'ai pas réussi à appliquer les contours à la zone de détection de la main car le type de 
backproj(trackWindow) n'était pas compatible avec les arguments que doit prendre la fonction
de détection des contours (en fin de fichier). J'ai réussi à l'appliquer à l'image mais pour
une raison que je n'ai pu trouver, cela ne s'applique pas à backproj(trackWindow), la fenêtre
de détection de la main.

