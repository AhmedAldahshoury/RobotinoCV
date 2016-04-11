
#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
String robotino_cascade_name = "/home/festo/ClionProjects/RobotinoCV/Cascade trials/data13/cascade.xml";
String puck_cascade_name = "/home/festo/ClionProjects/RobotinoCV/Cascade trials/datapuck4/cascade.xml";
CascadeClassifier robotino_cascade;
CascadeClassifier puck_cascade;
string window_name = "Capture - robotino & puck detection";
RNG rng(12345);

/**
 * @function main
 */
int main( void )
{
    VideoCapture capture;
    Mat frame;

    //-- 1. Load the cascades
    if( !robotino_cascade.load( robotino_cascade_name ) ){ printf("--(!)Error loading1\n"); return -1; };
    if( !puck_cascade.load( puck_cascade_name ) ){ printf("--(!)Error loading2\n"); return -1; };

    //-- 2. Read the video stream
    capture.open( -1 );
    if( capture.isOpened() )
    {
        for(;;)
        {
            capture >> frame;

            //-- 3. Apply the classifier to the frame
            if( !frame.empty() )
            { detectAndDisplay( frame ); }
            else
            { printf(" --(!) No captured frame -- Break!"); break; }

            int c = waitKey(10);
            if( (char)c == 'c' ) { break; }

        }
    }
    return 0;
}

/**
 * @function detectAndDisplay
 */
void detectAndDisplay( Mat frame )
{
    std::vector<Rect> robotinos;
    std::vector<Rect> pucks;

    Mat frame_gray;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    puck_cascade.detectMultiScale(frame,pucks,1.9,10,0);
    robotino_cascade.detectMultiScale(frame,robotinos,1.9,3,0);

    for( int i = 0; i < robotinos.size(); i++ )
    {

        rectangle( frame, cvPoint(robotinos[i].x,robotinos[i].y),cvPoint(robotinos[i].width+robotinos[i].x,robotinos[i].height+robotinos[i].y),CV_RGB(0,255,0), 3, 8,0);
    }
    for( int i = 0; i < pucks.size(); i++ )
    {

        rectangle( frame, cvPoint(pucks[i].x,pucks[i].y),cvPoint(pucks[i].width+pucks[i].x,pucks[i].height+pucks[i].y),CV_RGB(0,0,255), 3, 8,0);
    }
    //-- Show what you got
    imshow( window_name, frame );
}
