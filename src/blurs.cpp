#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

int main( int argc, char** argv ){
	using namespace cv;

	if(argc != 2){
		std::cerr << "usage: ./blurs <filename>" << std::endl;
		return -1;
	}

	namedWindow("Original", CV_WINDOW_KEEPRATIO);
	namedWindow("Blur", CV_WINDOW_KEEPRATIO);
	Mat imgOriginal, imgBlur;
	
	imgOriginal = imread(argv[1]);
	if(!imgOriginal.data){
		std::cerr << "could not read img!" << std::endl;
		return -1;
	}

	//TODO

	return 0;
}

