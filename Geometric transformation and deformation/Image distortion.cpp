#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    Mat input=imread("/Users/apple/Downloads/a.png");
    if(input.empty())
    {
        cout<<"cannot open"<<endl;
    }
    else{
        Mat output(input.rows,input.cols,CV_8UC3);
        for(int i=0;i<output.rows;i++){
            for(int j=0;j<output.cols;j++){
                Vec3b outputP = output.at<Vec3b>(i, j);
                
                double x = ((double)j - 0.5*output.cols) / (0.5*output.cols);
                double y = ((double)i - 0.5*output.rows) / (0.5*output.rows);
                
                double r=sqrt(pow(x,2)+pow(y,2));
                double o=pow(1-r,2);
                
                if(r>=1){
                    outputP=input.at<Vec3b>(i, j);
                }
                else{
                    double ix = (cos(o)*x - sin(o)*y)*0.5*output.cols+0.5*output.cols;
                    double iy = (sin(o)*x + cos(o)*y)*0.5*output.rows+0.5*output.rows;
                    if (ix < input.cols&&iy < input.rows){
                        outputP=input.at<Vec3b>(iy,ix);
                    }
                    else{
                        outputP=input.at<Vec3b>(input.rows-1,input.cols-1);
                    }
                }
                output.at<Vec3b>(i,j)=outputP;
            }
        
        }
        namedWindow("图像变形",WINDOW_AUTOSIZE);
        imshow("变形图像",output);
        waitKey();
    }
    return 0;
}

