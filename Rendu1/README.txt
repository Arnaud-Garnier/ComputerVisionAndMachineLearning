 ***************************
*	GARNIER Arnaud			*
*	SI4						*
*	Polytech Nice Sophia	*
 ***************************


 -> Travail réalisé :

Le but de ce premier TD était de rendre plus efficace l'algorithme de détection de visage.
On peut discerner 2 grandes étapes :
	- le nettoyage du code originel : en effet, dans le code fournit, beaucoup de choses
	n'étaient pas utiles dans le cadre du projet. Le but étant de détecter un seul visage
	par capture vidéo, la partie conscernant les traitements d'images a était supprimée.
	De même, la boucle for qui parcourait le tableau de visages a était remplacé par un simple if,
	car nous ne détectons ici qu'un seul visage.

	- l'amélioration de l'algorithme. Pour implémenter cette amélioration, l'ajout d'un
	booléen visageDetecte était nécéssaire. Il permet ainsi, lors de la première recherche de visage,
	de parcourir toute la capture vidéo à la recherche du visage (de même que si on le perd à un
	moment donné pendant utilisation). Une fois détecté, on fixe un rectangle de recherche
	autour de ce visage : ce sera notre zone de recherche. Le bolléen passe à true. Cette zone de recherche permettra 
	de diminuer grandement le temps de détection, car on travaillera dans une zone réduite à 
	ce rectangle. Un problème est apparu : le fait de faire plusieurs recherches
	simultanées dans la zone de recherche réduisait la taille de cette dernière. En effet, ne se plaçant pas au
	niveau de la capture vidéo pour les calculs mais au niveau de la zone réduite, la zone de recherche
	était réduite à chaque détection (on cherche un visage plus petit que la zone dans laquelle on fait la recherche), 
	ce qui faisait que le visage était perdu au bout de quelques secondes (zone de recherche devenue trop petite).
	Il a alors fallu augmenter la taille de cette zone. La méthode dimensionner permet d'éviter ce problème,
	en effectuant les calculs selon la capture vidéo entière. Enfin le dernier problème était celui des sorties
	de la capture : en effet, une erreur de type "Core Dumped" se produisait à chaque fois que la zone de 
	recherche sortait de la capture vidéo. Un redimensionnement du rectangle pour éviter de sortir de la capture
	vidéo était donc nécéssaire, et a été implémenté dans la méthode redimensionner (disjonction de cas).


---------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------


 -> Analyse des nouvelles performances :

Avant d'implémenter cet algorithme, la détection d'un visage prenait entre 90 et 140ms.
Après impémentation, on arrive à un temps de détection allant de 20 à 38ms. 
On peut voir l'efficacité de l'algorithme à la fluidité de la capture vidéo.