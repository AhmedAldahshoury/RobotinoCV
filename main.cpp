
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main( )
{
    Mat image;
    image = imread("/home/ahmed/Desktop/123.jpg", CV_LOAD_IMAGE_COLOR);
    namedWindow( "original image", 2 );   imshow( "original image", image );

    // Load Face cascade (.xml file)
    CascadeClassifier robotino_cascade;

    robotino_cascade.load( "/home/ahmed/Desktop/data/cascade.xml" );

    //detecting robotinos
    std::vector<Rect> robotinos;
    // face_cascade.detectMultiScale( image, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    robotino_cascade.detectMultiScale(image,robotinos,1.9,160,0);

    // Draw circles on the detected faces
    for( int i = 0; i < robotinos.size(); i++ )
    {

        rectangle( image, cvPoint(robotinos[i].x,robotinos[i].y),cvPoint(robotinos[i].width+robotinos[i].x,robotinos[i].height+robotinos[i].y),CV_RGB(0,255,0), 3, 8,0);
    }
    namedWindow( "Detected Face", 2 );
    imshow( "Detected Face", image );

    waitKey(0);
    return 0;
}
