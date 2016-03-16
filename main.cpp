
#include <iostream>
#include <opencv2/opencv.hpp>


#include "package_bgs/FrameDifferenceBGS.cpp"

#if CV_MAJOR_VERSION >= 2 && CV_MINOR_VERSION >= 4 && CV_SUBMINOR_VERSION >= 3

#endif

#include "package_bgs/jmo/MultiLayerBGS.h"


int main(int argc, char **argv){

    std::cout << "Using OpenCV " << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << "." << CV_SUBMINOR_VERSION << std::endl;

    CvCapture *capture = 0;
    int resize_factor = 100;
    argv[1] ="/home/ahmed/RobotinoCV/car-overhead-1.avi" ;
    argc++;

    if(argc > 1)
    {
        std::cout << "Openning: " << argv[1] << std::endl;

        capture = cvCaptureFromAVI(argv[1]);
    }
    else
    { std::cout << "3ak " << std::endl;
        capture = cvCaptureFromCAM(0);
        resize_factor = 50; // set size = 50% of original image
    }

    if(!capture)
    {
        std::cerr << "Cannot initialize video!" << std::endl;
        return -1;
    }



    IplImage *frame_aux = cvQueryFrame(capture);
    IplImage *frame = cvCreateImage(cvSize((int)((frame_aux->width*resize_factor)/100) , (int)((frame_aux->height*resize_factor)/100)), frame_aux->depth, frame_aux->nChannels);
    cvResize(frame_aux, frame);

    /* Background Subtraction Methods */
    IBGS *bgs;

    /*** Default Package ***/
    bgs = new FrameDifferenceBGS;


    int key = 0;
    while(key != 'q')
    {
        frame_aux = cvQueryFrame(capture);
        if(!frame_aux) break;

        cvResize(frame_aux, frame);

        cv::Mat img_input(frame);
        cv::imshow("input", img_input);

        cv::Mat img_mask;
        cv::Mat img_bkgmodel;
        bgs->process(img_input, img_mask, img_bkgmodel);

        key = cvWaitKey(33);
    }

    delete bgs;

    cvDestroyAllWindows();
    cvReleaseCapture(&capture);

    return 0;
}
