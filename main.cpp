#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include<dirent.h>
#include<string.h>
#include <iostream>
#include <cv.h>

using namespace std;
using namespace cv;

int main()
{
    CascadeClassifier robotino_cascade;
    robotino_cascade.load( "/home/festo/ClionProjects/RobotinoCV/Cascade trials/puck6data/cascade.xml" );
    std::vector<Rect> robotinos;
    string dirName = "/home/festo/Downloads/chosen mob images/";
    DIR *dir;
    dir = opendir(dirName.c_str());
    string imgName;
    struct dirent *ent;
    if (dir != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            imgName= ent->d_name;
            //I found some . and .. files here so I reject them.
            if(imgName.compare(".")!= 0 && imgName.compare("..")!= 0)
            {
                string aux;
                aux.append(dirName);
                aux.append(imgName);
                cout << aux << endl;
                Mat image= imread(aux);
                robotino_cascade.detectMultiScale(image,robotinos,1.9,10,0);
                for( int i = 0; i < robotinos.size(); i++ )
                {
                    rectangle( image, cvPoint(robotinos[i].x,robotinos[i].y),cvPoint(robotinos[i].width+robotinos[i].x,robotinos[i].height+robotinos[i].y),CV_RGB(0,255,0), 30, 8,0);
                }

                namedWindow( "Detected Robotino", 2 );
                imshow( "Detected Robotino", image );
                waitKey(0);
                cvDestroyWindow("Detected Robotino");
            }
        }
        closedir (dir);
    } else {
        cout<<"not present"<<endl;
    }
}
