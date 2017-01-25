 ***************************
*    GARNIER Arnaud	    *
*       - SI4 -		    *
*    Polytech Nice Sophia   *
 ***************************


 -> Travail réalisé :

Dans cette seconde itération du projet, le but était d'enregistrer dans un fichier texte
des valeurs de pixels, correspondant à des imagettes 16x16 pixels en niveaux de gris. Chaque
imagette correspond à une lettre en langage des signes.
Tout ceci dans le but de pouvoir implémenter le réseau de neurones par la suite.

Les étapes pour y parvenir :
 - utilisation de l'algorithme de Facedetect pour détecter le visage et calculer ainsi
   l'histogramme de la peau ;
 - une fois cette détection faite, on n'utilise non plus Facedetect pour suivre le
   visage, mais le tracking de l'algorithme CamShift (qui utilise l'histogramme) ;
 - on "masque"* le visage en réduisant la zone de recherche de la main à la partie
   gauche de l'image (afin de détecter la main droite) ;
 - grâce à l'histogramme, on peut retrouver la main sur la partie de l'image restante
   (avec le backproj, qui calcule les zone de probabilité de présence de peau sur 
   l'image) ;
 - on élargit un peu la zone autour de la main, afin de ne pas perdre de partie (bouts
   de doigts voir phalanges), ce qui pourrait nuire à la qualité de l'enregistrement 
   des lettres ;
 - on effectue avec la main une lettre de l'alphabet de la langue des signes et on appuie
   sur la touche du clavier correspondante pour l'enregistrer dans un fichier texte 
   (nommé letter.txt).

~~~~~
NB : à tout moment pendant la capture, on peut quitter l'application en appuyant sur la 
touche Echap, ou encore afficher l'histogramme obtenu pour la peau et le backproj de la 
zone de tracking.


* : se référer à la rubrique ci-dessous
---------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------


 -> Analyse critique :

On peut repprocher au code fournit quelques maladresses :
 - on n'applique pas véritablement de masque sur le visage, ce qui peut poser problème si
   le visage apparait dans la zone de recherche de la main. On ne fait que considérer
   la partie gauche de l'image.
 - le calcul de l'histogramme de prend pas en compte la saturation, ce qui n'est pas
   très optimisé pour détecter la peau.
