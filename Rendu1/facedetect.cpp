#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

bool visageDetecte = false;
Rect previous = Rect(0, 0, 0, 0);
Rect zoneRech;
string cascadeName;

// Déclarations de méthodes, que l'on définiera plus bas.
void detectAndDraw( Mat& img, CascadeClassifier& cascade, double scale );
void redimensionner(int largeurImage, int hauteurImage);
// *** FIN DES DECLARATIONS ***

// *** METHODES ***
int main( int argc, const char** argv )
{
    VideoCapture capture;
    Mat frame, image;
    string inputName;
    CascadeClassifier cascade;
    double scale;

    // On parse la commande entrée sur le terminal...
    cv::CommandLineParser parser(argc, argv,
        "{cascade|../../data/haarcascades/haarcascade_frontalface_alt.xml|}"
        "{scale|1|}{@filename||}"
    );
    cascadeName = parser.get<string>("cascade");
    scale = parser.get<double>("scale");

    if (scale < 1)
        scale = 1;
    inputName = parser.get<string>("@filename");
    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }
    // Si on ne parvient pas à charger le fichier .xml...
    if( !cascade.load( cascadeName ) )
    {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        return -1;
    }
    if( inputName.empty() || (isdigit(inputName[0]) && inputName.size() == 1) )
    {
        int c = inputName.empty() ? 0 : inputName[0] - '0';
        if(!capture.open(c))
            cout << "Capture from camera #" <<  c << " didn't work" << endl;
    }

    // Pas d'erreur au chargement, on lance la détection !
    if( capture.isOpened() )
    {
        cout << "Video capturing has been started ..." << endl;

        for(;;)
        {
            capture >> frame;
            if( frame.empty() )
                break;

            Mat frame1 = frame.clone();
            // Détection du visage sur l'image...
            detectAndDraw( frame1, cascade, scale );

            // Pour quitter l'application à tout moment
            // pendant l'exécution.
            int c = waitKey(10);
            if( c == 27 || c == 'q' || c == 'Q' )
                break;
        }
    }

    return 0;
}

// Méthode qui détecte un visage et dessine un cercle autour de celui-ci.
void detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    double scale )
{
    double t = 0;
    // Notre tableau de visages, qui ne contiendra ici qu'un seul élément,
    // à savoir notre visage.
    vector<Rect> faces;

    Mat gray, smallImg;

    cvtColor( img, gray, COLOR_BGR2GRAY );
    double fx = 1 / scale;
    // Reduire l'image.
    resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR );
    // Egaliser l'histogramme de l'image (en niveaux de gris).
    equalizeHist( smallImg, smallImg );

    t = (double)cvGetTickCount();
    
    // Si on a pas détecté de visage, on parcours toute l'image...
    if(!visageDetecte)
    {
        cascade.detectMultiScale( smallImg, faces,
        1.1, 2, 0
        |CASCADE_SCALE_IMAGE,
        Size(30, 30) );
    }
    // Sinon, on parcours l'image restreinte à la zone
    // de recherche...
    else
    {
        cascade.detectMultiScale( smallImg(zoneRech), faces,
        1.1, 2, 0
        |CASCADE_SCALE_IMAGE,
        Size(30, 30) );
    }
    // Lorsqu'on arrive ici, on a détecté un visage.
    visageDetecte = true;

    // Affichage du temps de détection.
    t = (double)cvGetTickCount() - t;
    printf( "Detection time : %g ms\n", t/((double)cvGetTickFrequency()*1000.) );

    // Si on a détecté un visage,
    // on dessine un cercle autour.
    if(faces.size() != 0)
    {
        Point center;
        int radius;
        // un seul visage est détectable lors du parcours de l'image
        Rect r = faces[0];
        // On fixe les coordonnées du point supérieur gauche
        // de la zone de recherche par rapport à la précédente
        // zone de recherche (variable previous).
        zoneRech.x = previous.x + r.x;
        zoneRech.y = previous.y + r.y;
        zoneRech.width = r.width;
        zoneRech.height = r.height;

        // On agrandit notre zone de recherche 
        // pour ne pas qu'elle se rétrécisse continuellement,
        // et donc que l'on perde le visage au bout d'un
        // certain nombre de détections successives.
        redimensionner(smallImg.cols, smallImg.rows);
   
        // On dessine le cercle autour du visage détecté.
        center.x = cvRound((r.x+zoneRech.x + r.width*0.5)*scale);
        center.y = cvRound((r.y+zoneRech.y + r.height*0.5)*scale);
        radius = cvRound((r.width + r.height)*0.25*scale);
        circle( img, center, radius, Scalar(255,0,0), 3, 8, 0 );

        // On enregistre le rectangle de la zone 
        // de recherche dans la variable previous.
        previous = zoneRech;
        // On précise qu'on a pas perdu le visage.
        visageDetecte = true;

    }
    // Sinon, c'est qu'on a perdu le visage.
    // On va devoir à nouveau parcourir l'image à sa recherche...
    else
    {
        visageDetecte = false;
        previous = Rect(0, 0 ,0, 0);
        zoneRech = Rect(0, 0, 0, 0);
    }

    // Affichage de la fenêtre.
    imshow( "result", img );
}


// Méthode d'agrandissement de la zone de recherche.
void redimensionner(int largeurImage, int hauteurImage)
{
    // La largeur de la zone de recherche précédente.
    int prevWidth = zoneRech.width; 
    // La hauteur de la zone de recherche précédente.
    int prevHeight = zoneRech.height; 

    // On "recule" le point supérieur gauche de la
    // zone de recherche.
    zoneRech.x = zoneRech.x - 35;
    zoneRech.y = zoneRech.y - 35; 

    // On augmente par conséquent la largeur
    // et la hauteur de la zone de recherche.
    zoneRech.width = zoneRech.width + 70;
    zoneRech.height = zoneRech.height + 70;

    // On a dépassé à gauche de l'image,
    // on met le x du point supérieur gauche à 0.
    if(zoneRech.x < 0)
    { 
        zoneRech.x = 0;
    }
    // On a dépassé en haut de l'image,
    // on met le y du point supérieur gauche à 0.
    if(zoneRech.y < 0)
    {
        zoneRech.y = 0;
    }
    // On a traité les cas simples (c'est à dire
    // lorsque les coordonnées du point supérieur gauche
    // du rectangle sont négatives [et sortent par 
    // conséquent de l'image]).
    // On traite à présent le cas si la zone de recherche
    // dépasse à droite ou en bas.

    // Si la position du points supérieur gauche en ordonné
    // additionné avec la hauteur du rectangle de recherche
    // sort de l'image, c'est qu'on a dépassé en bas de
    // l'image.
    // On va donc tronquer la hauteur du rectangle de la
    // zone de recherche.
    if(zoneRech.y + zoneRech.height > hauteurImage)
    {
        zoneRech.height = hauteurImage - zoneRech.y;
    } 

    // De même si la position en abscisse du point supérieur
    // gauche additionné avec la largeur du rectangle de
    // la zone de recherche est supérieur à la largeur
    // de l'image, on sors à droite de l'image.
    // On tronque alors de même le rectangle de la zone 
    // de recherche, afin de ne pas sortir de l'image.
    if(zoneRech.x + zoneRech.width > largeurImage)
    {
        zoneRech.width = largeurImage - zoneRech.x; 
    }

}