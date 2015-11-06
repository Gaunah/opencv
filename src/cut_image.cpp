#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>

int lowH = 0, highH = 179;
int lowS = 0, highS = 255;
int lowV = 0, highV = 255;

cv::Rect const getRegionOfInterest(cv::Mat const &imgThreshold){
	cv::Mat tmp;
	imgThreshold.copyTo(tmp); // i don't know why this is necessary :(
	cv::Rect boundingRectangle;
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(tmp, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	if(contours.size() > 0){ //found something
		int maxArea = 0;
		for(unsigned int i = 0; i < contours.size(); i++){
			cv::Rect tmpRect = cv::boundingRect(contours[i]);
			if(tmpRect.area() > maxArea){
				boundingRectangle = tmpRect;
				maxArea = tmpRect.area();
			}
		}
	}
	return boundingRectangle;
}

void morphOps(cv::Mat &img, cv::Mat const &structuringElement){
	//morphological opening (remove small objects from the foreground)	
	cv::erode(img, img, structuringElement);
	cv::dilate(img, img, structuringElement);
	//morphological closing (fill small holes in the foreground)	
	cv::dilate(img, img, structuringElement);
	cv::erode(img, img, structuringElement);
}

void createControl(){
	cvCreateTrackbar("LowH", "Thresholded Image", &lowH, 179);
	cvCreateTrackbar("HighH", "Thresholded Image", &highH, 179);

	cvCreateTrackbar("LowS", "Thresholded Image", &lowS, 255);
	cvCreateTrackbar("HighS", "Thresholded Image", &highS, 255);

	cvCreateTrackbar("LowV", "Thresholded Image", &lowV, 255);
	cvCreateTrackbar("HighV", "Thresholded Image", &highV, 255);
}

int main(int argc, char* argv[]){
	using namespace cv;

	if(argc != 2){
		std::cerr << "usage: ./track_detection <filename>" << std::endl;
		return EXIT_FAILURE;
	}

	//namedWindow("Control", CV_WINDOW_AUTOSIZE);

	namedWindow("Thresholded Image", CV_WINDOW_KEEPRATIO);
	namedWindow("Original", CV_WINDOW_KEEPRATIO);
	namedWindow("Cut", CV_WINDOW_KEEPRATIO);
	namedWindow("HSV", CV_WINDOW_KEEPRATIO);
	//createControl();

	Mat imgOriginal, imgHSV, imgThresholded, imgCut;
	Mat se = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));

	imgOriginal = imread(argv[1]);
	if(!imgOriginal.data){
		std::cerr << "could not read img!" << std::endl;
		return EXIT_FAILURE;
	}

	cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);
	//inRange(imgHSV, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), imgThresholded);
	inRange(imgHSV, Scalar(0, 30, 0), Scalar(50, 130, 200), imgThresholded);

	morphOps(imgThresholded, se);

	//rectangle(imgOriginal, getRegionOfInterest(imgThresholded), cv::Scalar(0, 0, 255), 8);
	imgOriginal(getRegionOfInterest(imgThresholded)).copyTo(imgCut);
	imshow("Thresholded Image", imgThresholded);
	imshow("Original", imgOriginal);
	imshow("Cut", imgCut);
	imshow("HSV", imgHSV);

	while(waitKey(0) != 27){}; //wait until ESC is hit
	imwrite("out.jpg", imgCut);
	return EXIT_SUCCESS;
}
