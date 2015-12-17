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
	namedWindow("Gauss", CV_WINDOW_KEEPRATIO);
	namedWindow("Median", CV_WINDOW_KEEPRATIO);
	namedWindow("Bilateral", CV_WINDOW_KEEPRATIO);
	Mat imgOriginal, imgGauss, imgMedian, imgBilateral;
	
	imgOriginal = imread(argv[1]);
	if(!imgOriginal.data){
		std::cerr << "could not read img!" << std::endl;
		return -1;
	}
	Size ksize(11, 11);
	cv::GaussianBlur(imgOriginal, imgGauss, ksize, 0);
	cv::medianBlur(imgOriginal, imgMedian, 11);
	
	double sigmaColor = 10, simgaSpace = 10;
	cv::bilateralFilter(imgOriginal, imgBilateral, 10, sigmaColor, simgaSpace, 0);

	imshow("Original", imgOriginal);
	imshow("Gauss", imgGauss);
	imshow("Median", imgMedian);
	imshow("Bilateral", imgBilateral);

	while(waitKey(0) != 27){}; //wait until ESC is hit
	return 0;
}

