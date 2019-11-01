#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cvaux.hpp>
#include <fstream>

using namespace cv;
using namespace std;

int main()
{
    Mat image=imread("/Users/apple/Downloads/a.png",-1);
    vector<Mat> channels;
    split(image,channels);
    Mat A = channels.at(3);
    namedWindow("提取alpha");
    imshow("image",A);
    waitKey();
    return true;
    
}
