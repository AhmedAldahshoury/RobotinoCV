/**
 * @file objectDetection.cpp
 * @author A. Huaman ( based in the classic facedetect.cpp in samples/c )
 * @brief A simplified version of facedetect.cpp, show how to load a cascade classifier and how to find objects (Face + eyes) in a video stream
 */
#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
//-- Note, either copy these two files from opencv/data/haarscascades to your current folder, or change these locations
String robotino_cascade_name = "/home/ahmed/Documents/RobotinoCV/Cascade trials/data/cascade.xml";
CascadeClassifier robotino_cascade;
string window_name = "Capture - robotino detection";
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
    Mat frame_gray;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    robotino_cascade.detectMultiScale( frame_gray, robotinos, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( int i = 0; i < robotinos.size(); i++ )
    {

        rectangle( frame_gray, cvPoint(robotinos[i].x,robotinos[i].y),cvPoint(robotinos[i].width+robotinos[i].x,robotinos[i].height+robotinos[i].y),CV_RGB(0,255,0), 3, 8,0);
    }
 //-- Show what you got
    imshow( window_name, frame );
}
