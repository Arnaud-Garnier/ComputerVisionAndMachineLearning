#include "opencv2/core/core.hpp"
#include "opencv2/ml/ml.hpp"

#include <opencv2/core/utility.hpp>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"

#include <cstdio>
#include <iostream>
#include <ctype.h>
#include <fstream>

using namespace cv;
using namespace std;
using namespace cv::ml;

Mat image;

bool backprojMode = false;
bool selectObject = false;
int trackObject = 0;
bool showHist = false;
Point origin;
Rect selection;
int vmin = 10, vmax = 256, smin = 30;
int tolerance = 10;
double scale = 1.0;

Rect zoneRech;
string cascadeName = "haarcascade_frontalface_alt.xml";
bool visageDetecte = false;
bool firstTime = true;
Rect reductImg;
Rect boundingTrackBox;

Mat src, dst;
static void ErodeDilate(int, void*);
static void OpenClose(int, void*);

// Plus on diminue la valeur de open_close_pos et erode_dilate_pos,
// plus on augmente la dilatation-errosion et/ou ouverture-fermeture.
int max_iters = 10;
int open_close_pos = 15;
int erode_dilate_pos = 8;

int element_shape = MORPH_RECT;

void EdgeDetect(Mat& src, Mat& grad);

template<typename T>
static Ptr<T> load_classifier(const string& filename_to_load)
{
    // load classifier from the specified file
    Ptr<T> model = StatModel::load<T>( filename_to_load );
    if( model.empty() )
        cout << "Could not read the classifier " << filename_to_load << endl;
    else
        cout << "The classifier " << filename_to_load << " is loaded.\n";

    return model;
}


void detectAndDraw( Mat& img, CascadeClassifier& cascade, double scale );

string hot_keys =
    "\n\nHot keys: \n"
    "\tESC - quit the program\n"
    "\tc - stop the tracking\n"
    "\tb - switch to/from backprojection view\n"
    "\th - show/hide object histogram\n"
    "\tp - pause video\n"
    "To initialize tracking, select the object with mouse\n";

static void help()
{
    cout << "\nThis is a demo that shows mean-shift based tracking\n"
            "You select a color objects such as your face and it tracks it.\n"
            "This reads from video camera (0 by default, or the camera number the user enters\n"
            "Usage: \n"
            "   ./camshiftdemo [camera number]\n";
    cout << hot_keys;
}

const char* keys =
{
    "{help h | | show help message}{@camera_number| 0 | camera number}"
};

int main( int argc, const char** argv )
{
    VideoCapture cap;
    Rect trackWindow;
    int hsize = 16;
    float hranges[] = {0,180};
    const float* phranges = hranges;
    CommandLineParser parser(argc, argv, keys);
    CascadeClassifier cascade;
    Ptr<ANN_MLP> model;
    const string& filename_to_load = "letter.yaml";

    if ( parser.has("help") )
    {
        help();
        return 0;
    }
    int camNum = parser.get<int>(0);
    cap.open(camNum);
    if( !cascade.load( cascadeName ) )
    {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        return -1;
    }
    if( !cap.isOpened() )
    {
        help();
        cout << "***Could not initialize capturing...***\n";
        cout << "Current parameter's value: \n";
        parser.printMessage();
        return -1;
    }
    if( filename_to_load.empty() )
    {
        cout << "Error : could not load xml data." << endl;
        return -1;
    }

    // load xml file to analyze
    model = load_classifier<ANN_MLP>( filename_to_load );

    if( model.empty() )
        return false;

    cout << hot_keys;
    namedWindow( "CamShift Demo", 0 );

    Mat frame, hsv, hue, mask, hist, histimg = Mat::zeros(200, 320, CV_8UC3), backproj;
    bool paused = false;

    for(;;)
    {
        // Tant qu'on a pas trouvé de visage, on exécute l'algorithme facedetect
        while( !visageDetecte )
        {
            cap >> frame;
            detectAndDraw(frame, cascade, scale);
        }

        if( !paused )
        {
            cap >> frame;
            if( frame.empty() )
                break;
        }

        frame.copyTo(image);

        if( !paused )
        {
            cvtColor(image, hsv, COLOR_BGR2HSV);

            if( trackObject )
            {
                int _vmin = vmin, _vmax = vmax;

                inRange(hsv, Scalar(0, smin, MIN(_vmin,_vmax)),
                        Scalar(180, 256, MAX(_vmin, _vmax)), mask);

                int ch[] = {0, 0};
                hue.create(hsv.size(), hsv.depth());
                mixChannels(&hsv, 1, &hue, 1, ch, 1);

                if ( !firstTime )
                {
                    reductImg = Rect(0,0, frame.cols/2, frame.rows);
                }

                // Si on a demandé à lancer le tracking :
                if( trackObject < 0 )
                {

                    Mat roi(hue, selection), maskroi(mask, selection);

                    // On détermine l'histogramme de la peau lors de la première détection faciale.
                    if( firstTime )
                    {
                        calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
                        normalize(hist, hist, 0, 255, NORM_MINMAX);
                        firstTime = false;


                    trackWindow = selection;
                    trackObject = 1;

                    histimg = Scalar::all(0);
                    int binW = histimg.cols / hsize;
                    Mat buf(1, hsize, CV_8UC3);
                    for( int i = 0; i < hsize; i++ )
                        buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180./hsize), 255, 255);
                    cvtColor(buf, buf, COLOR_HSV2BGR);

                        // On dessine l'histogramme de la peau dans histimg :
                        for( int i = 0; i < hsize; i++ )
                        {
                            int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows/255);
                            rectangle( histimg, Point(i*binW,histimg.rows),
                                   Point((i+1)*binW,histimg.rows - val),
                                   Scalar(buf.at<Vec3b>(i)), -1, 8 );
                        }
                    }    

                }

                calcBackProject(&hue, 1, 0, hist, backproj, &phranges);

                // On réduit backproj à la zone de recherche de la main :
                backproj.cols /= 2;

                trackWindow.x -= 100;
                trackWindow.y -= 300;
                trackWindow.width += 200;
                trackWindow.height += 600;

                // Le rotated rectangle, dans lequel nous allons
                // dessiner l'ellipse.
                RotatedRect trackBox = CamShift(backproj, trackWindow,
                                    TermCriteria( TermCriteria::EPS | TermCriteria::COUNT, 10, 1 ));

                
                // Redimmensionnement le rectangle de tracking (pour ne pas perdre
                // trop de partie de la main).
                boundingTrackBox = trackBox.boundingRect();
                /*rectangle(image, boundingTrackBox, Scalar(255,0,0),5);
                boundingTrackBox.width += 100;

                rectangle(image, boundingTrackBox, Scalar(0,255,255),5);*/

                if( trackWindow.area() <= 1 )
                {
                    int cols = backproj.cols, rows = backproj.rows, r = (MIN(cols, rows) + 5)/6;
                    trackWindow = Rect(trackWindow.x - r, trackWindow.y - r,
                                       trackWindow.x + r, trackWindow.y + r) &
                                  Rect(0, 0, cols, rows);
                }

                imshow("hand", backproj(trackWindow));

                // Afficher le backproj de la main :
                if( backprojMode ) {
                    cvtColor( backproj, frame, COLOR_GRAY2BGR );
                    imshow("frame", frame);
                }
                // Dessine l'ellipse au niveau du visage.
                ellipse( image, trackBox, Scalar(0,0,255), 3, LINE_AA );
            }
        }

        else if( trackObject < 0 )
            paused = false;

        // Si on détecte un visage, on lance l'algorithme de tracking 
        // (en mettant trackObject à -1).
        if( visageDetecte )
        {
            selection = zoneRech;
            Mat roi(image, selection);
            trackObject = -1;
        }

        imshow( "CamShift Demo", image );

        // Touches utilisateur pour interagir avec le programme :
        char c = (char)waitKey(10);
        // Quitter le programme avec la touche ESC.
        if( c == 27 )
            break;

        // Affiche la lettre que l'utilisateur a effectuée avec sa main 
        // en appuyant sur ESPACE.
        if ( c == 32 )
        {
            src = backproj(trackWindow);
            Mat element = getStructuringElement(element_shape, Size(2 + 1, 2 + 1), Point(1, 1) );
            erode(src, dst, element);
            
            element = getStructuringElement(element_shape, Size(4 + 1,4 + 1), Point(2, 2) );
            dilate(dst, dst, element);

            Mat hand = dst;

            resize(hand, hand, Size(16,16), 0, 0, INTER_LINEAR);
            hand.convertTo(hand, CV_32FC1);

            Mat img = hand.reshape(0,1);

                    CvMat* mlp_response = cvCreateMat(1, 26, CV_32FC1);

            // On passe à predict la matrice 1x16
            try 
            {
                float r = model->predict( img );
                // r contient le résultat de la prédiction
                // Pour afficher une lettre et pas un double sur le terminal :
                r += 'A';
                cout << "Vous avez fait la lettre : " << (char) r << endl;
            } catch(Exception e)
            {
                cout << "Mlp predict exception" << endl;
            }
        }

        // Enregistre les valeurs des pixels des images dans un fichier letter.txt :
        else if ( c  >= 'a' && c <= 'z' )
        {
            src = backproj(trackWindow);
            Mat element = getStructuringElement(element_shape, Size(2 + 1, 2 + 1), Point(1, 1) );
            erode(src, dst, element);
            
            element = getStructuringElement(element_shape, Size(4 + 1,4 + 1), Point(2, 2) );
            dilate(dst, dst, element);

            Mat hand = dst;
            resize(hand, hand, Size(16,16), 0, 0, INTER_LINEAR);

            Mat img = hand.reshape(0,1);
            ofstream os("letter.txt", ios::out | ios::app);
            // On met la lettre en majuscule avant de l'enregistrer dans le fichier texte
            c = toupper(c);
            os << c;
            // Pour éviter les espaces et les crochets :
            int j;
            for(j = 0; j < 256; j++)
            {
                os << "," << (uint)img.at<uchar>(j) ;
            }
            os << std::endl;
            os.close();
        }

    }

    return 0;
}

// Méthode qui détecte un visage et dessine un cercle autour de celui-ci.
// NB : cette méthode n'est utilisée qu'une seule fois, lors de la première
// détection du visage. Elle est issue de l'algorithme facedetect.
void detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    double scale )
{
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

    cascade.detectMultiScale( smallImg, faces,
    1.1, 2, 0
    |CASCADE_SCALE_IMAGE,
    Size(30, 30) );

    // Si on a détecté un visage,
    // on dessine un cercle autour.
    if(faces.size() != 0)
    {
        // un seul visage est détectable lors du parcours de l'image
        Rect r = faces[0];
        // On fixe les coordonnées du point supérieur gauche
        // de la zone de recherche par rapport à la précédente
        // zone de recherche.
        zoneRech.x = r.x;
        zoneRech.y = r.y;
        zoneRech.width = r.width;
        zoneRech.height = r.height;

        // On précise qu'on a pas perdu le visage.
        visageDetecte = true;
    }

}

// callback function for open/close trackbar
static void OpenClose(int, void*)
{
    int n = open_close_pos - max_iters;
    int an = n > 0 ? n : -n;
    Mat element = getStructuringElement(element_shape, Size(an + 1, an + 1), Point(an, an) );
    if( n < 0 )
        morphologyEx(src, dst, MORPH_OPEN, element);
    else
        morphologyEx(src, dst, MORPH_CLOSE, element);
}


// callback function for erode/dilate trackbar
static void ErodeDilate(int, void*)
{
    int n = erode_dilate_pos - max_iters;
    int an = n > 0 ? n : -n;
    Mat element = getStructuringElement(element_shape, Size(an + 1, an + 1), Point(an, an) );
    if( n < 0 )
        erode(src, dst, element);
    else
        dilate(src, dst, element);
}

// From the opencv documentation
void EdgeDetect(Mat& src, Mat& grad)
{
    Mat src_gray;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    int c;

    GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

    /// Convert it to gray
    cvtColor( src, src_gray, CV_BGR2GRAY );


    /// Create window
    namedWindow( "Sobel demo", CV_WINDOW_AUTOSIZE );

    /// Generate grad_x and grad_y
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    /// Gradient X
    Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );

    /// Gradient Y
    Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );

    /// Total Gradient (approximate)
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

}
