#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

int x, y;
void scale(Mat &input, Mat &output, double sx, double sy);
double sx,sy;
int main(int argc, char** argv) {
    Mat input=imread("/Users/apple/Downloads/a.png");
    if(input.empty())
    {
        cout<<"cannot open"<<endl;
    }
    else{
        cout<<"输入x方向缩放比例"<<endl;
        cin>>sx;
        cout<<"输入y方向缩放比例"<<endl;
        cin>>sy;
        namedWindow("original image",WINDOW_AUTOSIZE);
        imshow("original image",input);
        x=int(input.rows*sx);
        y=int(input.cols*sy);
        Mat output(x, y, CV_8UC3, Scalar::all(0));
        scale(input,output,sx,sy);
        imshow("缩放图",output);
        waitKey();
    }
    return 0;
}

void scale(Mat &input, Mat &output, double sx, double sy) {
    int col=0,row=0;
    double alpha=0.0,beta=0.0;
    for(int i=0;i<output.rows;i++)
    {
        uchar* desdata = output.template ptr<uchar>(i);
        for(int j=0;j<output.cols;j++)
        {
            row=int(i/sx);
            if(row>=input.rows-1)
            {
                row=input.rows-2;
            }
            alpha=i/sx-row;
            if(alpha>=1)
                alpha=1;
            
            col=int(j/sy);
            if(col>=input.cols-1)
            {
                col=input.cols-2;
            }
            beta=j/sy-col;
            if(beta>=1)
                beta=1;
            
            for(int k=0;k<3;k++)
            {
                double kk = input.at<Vec3b>(row, col)[k] +
                beta*(input.at<Vec3b>(row, col + 1)[k] - input.at<Vec3b>(row, col)[k]);
                double jj = input.at<Vec3b>(row + 1, col)[k] +
                beta*(input.at<Vec3b>(row + 1, col + 1)[k] - input.at<Vec3b>(row + 1, col)[k]);
                desdata[j * 3 + k] = kk + alpha*(jj - kk);
            }
        }
    }
}

