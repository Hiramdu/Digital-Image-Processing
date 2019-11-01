#include<opencv2\opencv.hpp>
#include<iostream>
#include<math.h>
using namespace cv;
using namespace std;


int main() {

	/* Test 1.1 Begins */
	//while (true) {

	//	cout << "����Ҫ���ص�ͼ��·����(��q�˳�)" << endl;
	//	string imageName;
	//	getline(cin, imageName);
	//	if (imageName == "q" || imageName == "Q") {
	//		break;
	//	}
	//	cout << imageName << endl;

	//	Mat image = imread(imageName);
	//	if (image.empty()) {
	//		cout << "cannot open " << imageName << endl;
	//	}
	//	else {
	//		namedWindow(imageName);
	//		imshow(imageName, image);
	//		waitKey(6000);
	//	}
	//
	//}
	/*Test 1.1 Ends.*/

	/*****************************************************************************************/

	/*Test 1.2 Begins*/

	Mat imgA = imread("d:\\a.png", -1);
	Mat alpha(imgA.rows,imgA.cols,CV_8UC1);
	for (int i = 0; i < imgA.rows; i++) {
		for (int j = 0; j < imgA.cols*3; j+=3) {
			//cout << (int)imgA.ptr<uchar>(i)[j/3*4+3]<<" ";
			alpha.ptr<uchar>(i)[j/3] =imgA.ptr<uchar>(i)[j / 3 * 4 + 3];
			//alpha.at<uchar>(i,j/3) = 255;
		}
		
		//cout <<endl<<"*************************************"<< endl;
	}

	imwrite("d:\\alpha.png",alpha);

	Mat a = imread("d:\\alpha.png",CV_LOAD_IMAGE_UNCHANGED);
	namedWindow("d:\\alpha.png");
	imshow("d:\\alpha.png", a);
	waitKey();

	while (true) {

		cout << "���뱳��ͼ��·����(��q�˳�)" << endl;
		string imageName;
		getline(cin, imageName);
		if (imageName == "q" || imageName == "Q") {
			break;
		}
		cout << imageName << endl;

		Mat image = imread(imageName);
		Mat a = imread("d:\\a.png");
		Mat result(image.rows, image.cols, CV_8UC3);
		if (image.empty()) {
			cout << "cannot open " << imageName << endl;
		}
		else {

			for (int i = 0; i < result.rows; i++) {

				for (int j = 0; j <result.cols; j++) {
					Vec3b pixel=image.at<Vec3b>(i,j);
					if (i < alpha.rows&&j < alpha.cols) {
						Vec3b aPixel = a.at<Vec3b>(i, j);
						if (alpha.at<uchar>(i, j)==255) {
							pixel = aPixel;
							
						}else{
							int al =alpha.at<uchar>(i, j);
							float alp = (float)al / 255;
							pixel[0] = (1 - alp)*pixel[0] + alp*aPixel[0];
							pixel[1] = (1 - alp)*pixel[1] + alp*aPixel[1];
							pixel[2] = (1 - alp)*pixel[2] + alp*aPixel[2];
						}
						
					}
					
					result.at<Vec3b>(i,j) = pixel;
				}
			}

			namedWindow("�ϳ�");
			imshow("�ϳ�", result);
			waitKey();
		}
	
	}

	/*Test 1.2 Ends*/

	/*****************************************************************************************/


	return 0;
}


//#include<iostream>
//#include<opencv2/core/core.hpp>
//#include<opencv2/highgui/highgui.hpp>
//using namespace cv;
//using namespace std;
//int x, y;
//void scale(Mat &srcmat, Mat &desmat, double sx, double sy);
//int main(int argc, char** argv) {
//
//	/*****************************************************************************************/
//
//	/*Test 2.1 Begins*/
//	//���ű���
//	/*double sx = 0, sy = 0;
//
//	while (true)
//	{
//		cout << "����Ҫ���ص�ͼ��·����(��q�˳�)" << endl;
//		string imageName;
//		getline(cin, imageName);
//		if (imageName == "q" || imageName == "Q") {
//			break;
//		}
//		Mat inputImg = imread(imageName);
//		if (inputImg.empty()) {
//			cout << "cannot open " << imageName << endl;
//		}
//		else {
//			cout << "�������ű���x" << endl;
//			cin >> sx;
//			cout << "�������ű���y" << endl;
//			cin >> sy;
//			cin.clear();
//			cin.ignore();
//			cin.sync();
//			namedWindow("ԭͼ", WINDOW_AUTOSIZE);
//			imshow("ԭͼ", inputImg);
//			y = int(inputImg.cols*sy);
//			x = int(inputImg.rows*sx);
//			Mat outputImg(x, y, CV_8UC3, Scalar::all(0));
//			scale(inputImg, outputImg, sx, sy);
//			imshow("����ͼ", outputImg);
//			waitKey();
//
//		}
//	}*/
//
//
//	/*Test 2.1 Ends*/
//
//	/*****************************************************************************************/
//
//	/*Test 2.2 Begins*/
//
//	/*while (true)
//	{
//		cout << "����Ҫ���ص�ͼ��·����(��q�˳�)" << endl;
//		string imageName;
//		getline(cin, imageName);
//		if (imageName == "q" || imageName == "Q") {
//			break;
//		}
//		Mat inputImg = imread(imageName);
//		if (inputImg.empty()) {
//			cout << "cannot open " << imageName << endl;
//		}
//		else {
//			
//			Mat outputImg(inputImg.rows,inputImg.cols,CV_8UC3);
//			
//			for (int i = 0; i < outputImg.rows; i++) {
//				for (int j = 0; j < outputImg.cols; j++) {
//
//					Vec3b outputP = outputImg.at<Vec3b>(i, j);
//
//					double x = ((double)j - 0.5*outputImg.cols) / (0.5*outputImg.cols);
//					double y = ((double)i - 0.5*outputImg.rows) / (0.5*outputImg.rows);
//
//
//					double r = sqrt(pow(x,2)+pow(y,2));
//					double o = pow((1 - r), 2);
//
//					if (r >= 1) {
//						outputP = inputImg.at<Vec3b>(i, j);
//					}
//					else {
//						
//						double ix = (cos(o)*x - sin(o)*y)*0.5*outputImg.cols+0.5*outputImg.cols;
//						double iy = (sin(o)*x + cos(o)*y)*0.5*outputImg.rows+0.5*outputImg.rows;
//
//						if (ix < inputImg.cols&&iy < inputImg.rows) {
//							outputP = inputImg.at<Vec3b>(iy, ix);
//						}
//						else {
//							outputP = inputImg.at<Vec3b>(inputImg.rows-1, inputImg.cols - 1);
//						}
//						
//					}
//					
//					outputImg.at<Vec3b>(i, j) = outputP;
//				}
//			}
//
//			namedWindow("ͼ�����", WINDOW_AUTOSIZE);
//			imshow("ͼ�����", outputImg);
//			waitKey();
//
//		}
//	}*/
//
//	/*Test 2.2 Ends*/
//  /*****************************************************************************************/
//
//	return 0;
//}
//
//
//void scale(Mat &inputMat, Mat &outputMat, double sx, double sy) {
//	int srccol = 0, srcrow = 0;
//	double alph = 0.0, beta = 0.0;
//
//	for (int i = 0; i < outputMat.rows; i++) {
//		uchar* desdata = outputMat.ptr<uchar>(i);
//		for (int j = 0; j <outputMat.cols; j++) {
//			srcrow = int(i / sx);
//			//�жϷŴ��ͼ���Ӧ��ԭͼ��������Ƿ�Խ���
//			if (srcrow >= inputMat.rows - 1) {
//				srcrow = inputMat.rows - 2;
//			}
//			alph = i / sx - srcrow;
//			if (alph >= 1)
//				alph = 1;
//			srccol = int(j / sy);
//			if (srccol >= inputMat.cols - 1)
//				srccol = inputMat.cols - 2;
//			beta = j / sy - srccol;
//			if (beta >= 1)
//				beta = 1;
//			for (int k = 0; k < 3; k++) {
//				double kk = inputMat.at<Vec3b>(srcrow, srccol)[k] +
//					beta*(inputMat.at<Vec3b>(srcrow, srccol + 1)[k] - inputMat.at<Vec3b>(srcrow, srccol)[k]);
//				double jj = inputMat.at<Vec3b>(srcrow + 1, srccol)[k] +
//					beta*(inputMat.at<Vec3b>(srcrow + 1, srccol + 1)[k] - inputMat.at<Vec3b>(srcrow + 1, srccol)[k]);
//				desdata[j * 3 + k] = kk + alph*(jj - kk);
//			}
//		}
//	}
//}
//
//#include<iostream>
//#include<opencv2/core/core.hpp>
//#include<opencv2/highgui/highgui.hpp>
//#include<cmath>
//using namespace cv;
//using namespace std;
//
//void Gaussian(const Mat &inputImg, Mat &outputImg, double sigma);
//void MeanFilter(const Mat &input, Mat &output, int window_size);
//
//
//int main() {
//
//	/*****************************************************************************************/
//	
//	/*Test 3.1 Begins*/
//	//while (true) {
//	//	cout << "����Ҫ�����ͼ��·����(��q�˳�)" << endl;
//	//	string imageName;
//	//	getline(cin, imageName);
//	//	if (imageName == "q" || imageName == "Q") {
//	//		break;
//	//	}
//	//	Mat inputImg = imread(imageName);
//	//	//Mat inputImg = imread("d:\\test.jpg");
//	//	if (inputImg.empty()) {
//	//		cout << "cannot open " << imageName << endl;
//	//	}
//	//	else {
//	//		double sigma;
//	//		cout << "�����˹�����ı�ע��sigma��" << endl;
//	//		cin >> sigma;
//	//			cin.clear();
//	//			cin.ignore();
//	//			cin.sync();
//	//			namedWindow("ԭͼ", WINDOW_AUTOSIZE);
//	//			imshow("ԭͼ", inputImg);
//	//			Mat outputImg(inputImg.rows, inputImg.cols, CV_8UC3);
//	//			Gaussian(inputImg, outputImg, sigma);
//	//			waitKey();
//	//			
//	//	}
//
//	//}
//
//	/*****************************************************************************************/
//
//	/*Test 3.2 Begins*/
//	//while (true) {
//	//	cout << "����Ҫ�����ͼ��·����(��q�˳�)" << endl;
//	//	string imageName;
//	//	getline(cin, imageName);
//	//	if (imageName == "q" || imageName == "Q") {
//	//		break;
//	//	}
//	//	Mat inputImg = imread(imageName);
//	//	//Mat inputImg = imread("d:\\test.jpg");
//	//	if (inputImg.empty()) {
//	//		cout << "cannot open " << imageName << endl;
//	//	}
//	//	else {
//	//		int size;
//	//		cout << "�����˲����ڴ�Сsize(����)��" << endl;
//	//		cin >> size;
//	//		while (size % 2 == 0 || size <= 0) {
//	//			cout << "���벻��ȷ�������������˲����ڴ�Сsize(����)��" << endl;
//	//			cin >> size;
//	//		}
//	//		cin.clear();
//	//		cin.ignore();
//	//		cin.sync();
//	//		namedWindow("ԭͼ", WINDOW_AUTOSIZE);
//	//		imshow("ԭͼ", inputImg);
//	//		Mat outputImg(inputImg.rows, inputImg.cols, CV_8UC3);
//	//		MeanFilter(inputImg, outputImg, size);
//	//		waitKey();
//
//	//	}
//
//	//}
//	
//
//	return 0;
//}
//void Gaussian(const Mat &inputImg, Mat &outputImg, double sigma) {
//
//	
//	//���㴰�ڴ�С
//	int windows = ((int)(6 * sigma - 1)) / 2 * 2 + 1;
//	
//	double *value = new double[windows];
//	double sum = 0;
//	//��������
//	int left = -windows / 2, right = windows / 2 + 1, border = windows / 2;
//	for (int i = left; i < right; i++){	
//		value[i + border] = pow(2.718, -(i * i) / (2 * sigma * sigma)) / (sqrt(2 * 3.1415926) * sigma);
//		sum += value[i + border];
//	}
//	for (int i = left; i < right; i++){
//		value[i + border] = value[i + border] / sum;
//		cout << value[i + border] << endl;
//	}
//
//	//�洢�м���ͼ��
//	Mat tempImg(inputImg.rows + border * 2, inputImg.cols + border * 2, CV_8UC3);
//
//	//���ͼ��
//	Mat fillImg(inputImg.rows + border * 2, inputImg.cols + border * 2, CV_8UC3);
//	for (int i = border; i < inputImg.rows + border; i++) {
//		for (int j = border; j < inputImg.cols + border; j++) {
//			fillImg.at<Vec3b>(i, j)[0] = inputImg.at<Vec3b>((i-border) % (inputImg.rows - 1),(j-border) % (inputImg.cols - 1))[0];
//			fillImg.at<Vec3b>(i, j)[1] = inputImg.at<Vec3b>((i - border) % (inputImg.rows - 1), (j - border) % (inputImg.cols - 1))[1];
//			fillImg.at<Vec3b>(i, j)[2] = inputImg.at<Vec3b>((i - border) % (inputImg.rows - 1), (j - border) % (inputImg.cols - 1))[2];
//		}
//	}
//	//���ͼ���Ϸ�
//	for (int i = 0; i < border; i++) {
//		for (int j = 0; j < inputImg.cols + border * 2; j++) {
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[0] = inputImg.at<Vec3b>(i%(inputImg.rows-1), j%(inputImg.cols-1))[0];
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[1] = inputImg.at<Vec3b>(i % (inputImg.rows - 1), j % (inputImg.cols - 1))[1];
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[2] = inputImg.at<Vec3b>(i % (inputImg.rows - 1), j % (inputImg.cols - 1))[2];
//		}
//	}
//	//���ͼ���·�
//	for (int i = inputImg.rows+border; i < inputImg.rows + border * 2; i++) {
//		for (int j = 0; j < inputImg.cols + border * 2; j++) {
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[0] = inputImg.at<Vec3b>((i-border*2) % (inputImg.rows - 1), j % (inputImg.cols - 1))[0];
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[1] = inputImg.at<Vec3b>((i - border * 2) % (inputImg.rows - 1), j % (inputImg.cols - 1))[1];
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[2] = inputImg.at<Vec3b>((i - border * 2) % (inputImg.rows - 1), j % (inputImg.cols - 1))[2];
//
//		}
//	}
//	//�����
//	for (int i = border; i < inputImg.rows + border; i++) {
//		for (int j = 0; j < border; j++) {
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[0] = inputImg.at<Vec3b>((i-border) % (inputImg.rows - 1), j % (inputImg.cols - 1))[0];
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[1] = inputImg.at<Vec3b>((i - border) % (inputImg.rows - 1), j % (inputImg.cols - 1))[1];
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[2] = inputImg.at<Vec3b>((i - border) % (inputImg.rows - 1), j % (inputImg.cols - 1))[2];
//
//		}
//	}
//	//����ҷ�
//	for (int i = border; i < inputImg.rows + border; i++) {
//		for (int j = inputImg.cols+border; j < inputImg.cols + border*2; j++) {
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[0] = inputImg.at<Vec3b>((i - border) % (inputImg.rows - 1), (j-border*2) % (inputImg.cols - 1))[0];
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[1] = inputImg.at<Vec3b>((i - border) % (inputImg.rows - 1), (j - border * 2) % (inputImg.cols - 1))[1];
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[2] = inputImg.at<Vec3b>((i - border) % (inputImg.rows - 1), (j - border * 2) % (inputImg.cols - 1))[2];
//
//		}
//	}
//	namedWindow("����", WINDOW_AUTOSIZE);
//	imshow("����", fillImg);
//
//	//��ÿ�н���һά��˹�˲�
//	for (int i = 0; i < tempImg.rows; i++){
//		for (int j = border; j < tempImg.cols - border; j++){
//			tempImg.at<Vec3b>(i, j)[0] = 0;
//			tempImg.at<Vec3b>(i, j)[1] = 0;
//			tempImg.at<Vec3b>(i, j)[2] = 0;
//			for (int k = left; k < right; k++){
//				tempImg.at<Vec3b>(i, j)[0] += (fillImg.at<Vec3b>(i, j + k)[0] * value[k + border]);
//				tempImg.at<Vec3b>(i, j)[1] += (fillImg.at<Vec3b>(i, j + k)[1] * value[k + border]);
//				tempImg.at<Vec3b>(i, j)[2] += (fillImg.at<Vec3b>(i, j + k)[2] * value[k + border]);
//			}
//		}
//	}
//
//	//�Խ����ÿ�н���һά��˹�˲�
//	for (int i = 0; i < outputImg.rows; i++){
//		for (int j = 0; j < outputImg.cols; j++){
//			outputImg.at<Vec3b>(i, j)[0] = 0;
//			outputImg.at<Vec3b>(i, j)[1] = 0;
//			outputImg.at<Vec3b>(i, j)[2] = 0;
//			for (int k = left; k < right; k++){
//				outputImg.at<Vec3b>(i, j)[0] += (tempImg.at<Vec3b>(i + k+border, j+border)[0] * value[k + border]);
//				outputImg.at<Vec3b>(i, j)[1] += (tempImg.at<Vec3b>(i + k+border, j+border)[1] * value[k + border]);
//				outputImg.at<Vec3b>(i, j)[2] += (tempImg.at<Vec3b>(i + k+border, j+border)[2] * value[k + border]);
//			}
//		}
//	}
//
//
//	namedWindow("��˹�˲�", WINDOW_AUTOSIZE);
//	imshow("��˹�˲�", outputImg);
//}
//
//void MeanFilter(const Mat &inputImg, Mat &outputImg, int window_size) {
//
//	
//
//	int w = (window_size - 1) / 2;
//	int z = window_size * window_size;//������
//
//	//���ͼ��
//	Mat fillImg(inputImg.rows + w * 2, inputImg.cols + w * 2 , CV_8UC3);
//	for (int i = w; i < inputImg.rows + w; i++) {
//		for (int j = w; j < inputImg.cols + w; j++) {
//			fillImg.at<Vec3b>(i, j)[0] = inputImg.at<Vec3b>((i - w) % (inputImg.rows - 1), (j - w) % (inputImg.cols - 1))[0];
//			fillImg.at<Vec3b>(i, j)[1] = inputImg.at<Vec3b>((i - w) % (inputImg.rows - 1), (j - w) % (inputImg.cols - 1))[1];
//			fillImg.at<Vec3b>(i, j)[2] = inputImg.at<Vec3b>((i - w) % (inputImg.rows - 1), (j - w) % (inputImg.cols - 1))[2];
//		}
//	}
//	//���ͼ���Ϸ�
//	for (int i = 0; i < w; i++) {
//		for (int j = 0; j < inputImg.cols + w * 2; j++) {
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[0] = inputImg.at<Vec3b>(i % (inputImg.rows - 1), j % (inputImg.cols - 1))[0];
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[1] = inputImg.at<Vec3b>(i % (inputImg.rows - 1), j % (inputImg.cols - 1))[1];
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[2] = inputImg.at<Vec3b>(i % (inputImg.rows - 1), j % (inputImg.cols - 1))[2];
//		}
//	}
//	//���ͼ���·�
//	for (int i = inputImg.rows + w; i < inputImg.rows + w * 2; i++) {
//		for (int j = 0; j < inputImg.cols + w * 2; j++) {
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[0] = inputImg.at<Vec3b>((i - w * 2) % (inputImg.rows - 1), j % (inputImg.cols - 1))[0];
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[1] = inputImg.at<Vec3b>((i - w * 2) % (inputImg.rows - 1), j % (inputImg.cols - 1))[1];
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[2] = inputImg.at<Vec3b>((i - w * 2) % (inputImg.rows - 1), j % (inputImg.cols - 1))[2];
//
//		}
//	}
//	//�����
//	for (int i = w; i < inputImg.rows + w; i++) {
//		for (int j = 0; j < w; j++) {
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[0] = inputImg.at<Vec3b>((i - w) % (inputImg.rows - 1), j % (inputImg.cols - 1))[0];
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[1] = inputImg.at<Vec3b>((i - w) % (inputImg.rows - 1), j % (inputImg.cols - 1))[1];
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[2] = inputImg.at<Vec3b>((i - w) % (inputImg.rows - 1), j % (inputImg.cols - 1))[2];
//
//		}
//	}
//	//����ҷ�
//	for (int i = w; i < inputImg.rows + w; i++) {
//		for (int j = inputImg.cols + w; j < inputImg.cols + w * 2; j++) {
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[0] = inputImg.at<Vec3b>((i - w) % (inputImg.rows - 1), (j - w * 2) % (inputImg.cols - 1))[0];
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[1] = inputImg.at<Vec3b>((i - w) % (inputImg.rows - 1), (j - w * 2) % (inputImg.cols - 1))[1];
//			fillImg.at<Vec3b>(i%fillImg.rows, j%fillImg.cols)[2] = inputImg.at<Vec3b>((i - w) % (inputImg.rows - 1), (j - w * 2) % (inputImg.cols - 1))[2];
//
//		}
//	}
//	namedWindow("����", WINDOW_AUTOSIZE);
//	imshow("����", fillImg);
//		
//
//	//�洢����ͼ
//	int ***integral;
//
//	integral = new int**[fillImg.rows];
//	for (int i = 0; i<fillImg.rows; i++) {
//		integral[i] = new int*[fillImg.cols];
//	}
//	for (int i = 0; i < fillImg.rows; i++) {
//		for (int j = 0; j < fillImg.cols; j++) {
//			integral[i][j] = new int[3];
//		}
//	}
//
//	//��������ͼ�����ͼ
//	for (int i = 0; i < fillImg.rows; i++) {
//		for (int j = 0; j < fillImg.cols; j++) {
//
//			//Integral(i,j) = Integral(i,j-1) + ColumnSum(j);
//			int *columnSum=new int[3];
//			columnSum[0] = 0;
//			columnSum[1] = 0;
//			columnSum[2] = 0;
//			for (int k = 0; k < i+1; k++) {
//				columnSum[0] += (int)fillImg.at<Vec3b>(k, j)[0];
//				columnSum[1] += (int)fillImg.at<Vec3b>(k, j)[1];
//				columnSum[2] += (int)fillImg.at<Vec3b>(k, j)[2];
//				//cout << (int)columnSum[0] << " ";
//			}
//			if (j == 0) {
//				integral[i][j][0] = columnSum[0];
//				integral[i][j][1] = columnSum[1];
//				integral[i][j][2] = columnSum[2];
//
//			}
//			else {
//				integral[i][j][0] = integral[i][j - 1][0] + columnSum[0];
//				integral[i][j][1] = integral[i][j - 1][1] + columnSum[1];
//				integral[i][j][2] = integral[i][j - 1][2] + columnSum[2];
//				//cout << (int)integral[i][j][0] << " ";
//			}
//			
//			
//
//		}
//	}
//
//	
//	//���پ�ֵ�˲�
//	for (int i = w + 1; i < fillImg.rows - w - 1; i++) {
//		for (int j = w + 1; j < fillImg.cols - w - 1; j++) {
//			outputImg.at<Vec3b>(i-w-1, j-w-1)[0] = (integral[i + w][j + w][0] + integral[i - w - 1][j - w - 1][0] - integral[i + w][j - w - 1][0] - integral[i - w - 1][j + w][0]) / z;
//			outputImg.at<Vec3b>(i-w-1, j-w-1)[1] = (integral[i + w][j + w][1] + integral[i - w - 1][j - w - 1][1] - integral[i + w][j - w - 1][1] - integral[i - w - 1][j + w][1]) / z;
//			outputImg.at<Vec3b>(i-w-1, j-w-1)[2] = (integral[i + w][j + w][2] + integral[i - w - 1][j - w - 1][2] - integral[i + w][j - w - 1][2] - integral[i - w - 1][j + w][2]) / z;
//
//		}
//	}
//
//
//
//	namedWindow("���پ�ֵ�˲�", WINDOW_AUTOSIZE);
//	imshow("���پ�ֵ�˲�", outputImg);
//
//	/*for (int i = 0; i<2; i++){
//		for (int j = 0; j<20; j++){
//			cout <<i<<" "<<j<<" "<< (int)integral[i][j][0] << endl;
//		}
//	}
//*/
//	for (int i = 0; i<fillImg.rows; i++)
//	{
//		for (int j = 0; j<fillImg.cols; j++)
//			delete[] integral[i][j];
//		delete[] integral[i];
//	}
//	delete[] integral;
//
//}






