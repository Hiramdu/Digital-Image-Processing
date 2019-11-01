#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cvaux.hpp>
#include <fstream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    
    // Read the images
    Mat foreground = imread("/Users/apple/Downloads/a.png");
    Mat background = imread("/Users/apple/Downloads/c.png");
    Mat alpha = imread("/Users/apple/Downloads/alpha.png");
    
    // Convert Mat to float data type
    foreground.convertTo(foreground, CV_32FC3);
    background.convertTo(background, CV_32FC3);
    
    // Normalize the alpha mask to keep intensity between 0 and 1
    alpha.convertTo(alpha, CV_32FC3, 1.0/255); //
    
    // Storage for output image
    Mat ouImage = Mat::zeros(foreground.size(), foreground.type());
    
    // Multiply the foreground with the alpha matte
    multiply(alpha, foreground, foreground);
    
    // Multiply the background with ( 1 - alpha )
    multiply(Scalar::all(1.0)-alpha, background, background);
    
    // Add the masked foreground and background.
    add(foreground, background, ouImage);
    
    // Display image
    imshow("alpha blended image", ouImage/255);
    waitKey(0);
    
    return 0;
}
