#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

cv::Mat imgOriginal, imgMShift, imgROI;
int sr = 20; //The spatial window radius.
int sp = 35; //The color window radius.

cv::Rect const getRectangle(cv::Mat const &mat){
	return cv::Rect(0, 0, mat.size().width, mat.size().height/2);
}

void PMShift(int, void*){
	cv::pyrMeanShiftFiltering(imgOriginal, imgMShift, sp, sr, 1);
	cv::imshow("Mean Shift", imgMShift);
}

int main(int argc, char* argv[]){
	using namespace cv;

	if(argc == 2){
		imgOriginal = imread(argv[1]);
	} else {
		std::cerr << "usage: ./mean_shift_seg <img file>" << std::endl;
		return -1;
	}
	if(!imgOriginal.data){
		std::cerr << "could not read img from: " << argv[1] << std::endl;
		return -1;
	}
	
	namedWindow("Original", CV_WINDOW_KEEPRATIO);
	namedWindow("Mean Shift", CV_WINDOW_KEEPRATIO);
	createTrackbar("Spatial radius", "Original", &sr, 100, PMShift);
	createTrackbar("Color radius", "Original", &sp, 100, PMShift);
	pyrMeanShiftFiltering(imgOriginal, imgMShift, sr, sp, 1);

	imgOriginal.copyTo(imgROI);
	Mat mask(imgOriginal.size(), CV_8U, Scalar(0));
	rectangle(mask, getRectangle(imgOriginal), Scalar(1), -1);

	imshow("Original", imgROI);
	imgOriginal.copyTo(imgMShift, mask);
	imshow("Mean Shift", imgMShift);
	//PMShift(0, 0);

	while(waitKey(0) != 27){}; //wait until ESC is hit
	//imwrite("out.jpg", imgMShift);
	return 0;
}
