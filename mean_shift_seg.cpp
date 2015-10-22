#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

cv::Mat imgOrginal, imgMShift;
int sr = 0; //The spatial window radius.
int sp = 0; //The color window radius.

void PMShift(int, void*){
	cv::pyrMeanShiftFiltering(imgOrginal, imgMShift, sp, sr, 1);
	cv::imshow("Mean Shift", imgMShift);
}

int main(int argc, char* argv[]){
	using namespace cv;

	if(argc == 2){
		imgOrginal = imread(argv[1]);
	} else {
		std::cerr << "usage: ./mean_shift_seg <img file>" << std::endl;
		return -1;
	}
	if(!imgOrginal.data){
		std::cerr << "could not read img from: " << argv[1] << std::endl;
		return -1;
	}
	
	namedWindow("Orginal", CV_WINDOW_KEEPRATIO);
	namedWindow("Mean Shift", CV_WINDOW_KEEPRATIO);
	createTrackbar("Spatial radius", "Orginal", &sr, 100, PMShift);
	createTrackbar("Color radius", "Orginal", &sp, 100, PMShift);

	imshow("Orginal", imgOrginal);
	PMShift(0, 0);

	while(waitKey(0) != 27){}; //wait until ESC is hit
	return 0;
}
