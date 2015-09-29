#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>
#include <iostream>

cv::Rect const getRegionOfInterest(cv::Mat const &imgThreshold){
	cv::Mat tmp;
	imgThreshold.copyTo(tmp); // i don't know why this is necessary :(
	cv::Rect boundingRectangle;
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(tmp, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	if(contours.size() > 0){ //found something
		int maxArea = 0;
		for(int i = 0; i < contours.size(); i++){
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

int main(int argc, char* argv[]){
	using namespace cv;

	if(argc != 2){
		std::cerr << "usage: ./track_detection <filename>" << std::endl;
		return EXIT_FAILURE;
	}

	//namedWindow("Control", CV_WINDOW_AUTOSIZE);
	//int lowH = 0, highH = 179;
	//int lowS = 0, highS = 255;
	//int lowV = 0, highV = 255;

	//cvCreateTrackbar("LowH", "Control", &lowH, 179);
	//cvCreateTrackbar("HighH", "Control", &highH, 179);

	//cvCreateTrackbar("LowS", "Control", &lowS, 255);
	//cvCreateTrackbar("HighS", "Control", &highS, 255);

	//cvCreateTrackbar("LowV", "Control", &lowV, 255);
	//cvCreateTrackbar("HighV", "Control", &highV, 255);

	namedWindow("Thresholded Image", CV_WINDOW_KEEPRATIO);
	namedWindow("Orginal", CV_WINDOW_KEEPRATIO);
	namedWindow("Cut", CV_WINDOW_KEEPRATIO);
	Mat imgOrginal, imgHSV, imgThresholded, imgCut;
	Mat se = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	while(true){
		imgOrginal = imread(argv[1]);
		if(!imgOrginal.data){
			std::cerr << "could not read img!" << std::endl;
			return EXIT_FAILURE;
		}

		cvtColor(imgOrginal, imgHSV, COLOR_BGR2HSV);
		//inRange(imgHSV, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), imgThresholded);
		inRange(imgHSV, Scalar(0, 0, 0), Scalar(180, 170, 170), imgThresholded);

		morphOps(imgThresholded, se);
		
		//rectangle(imgOrginal, getRegionOfInterest(imgThresholded), cv::Scalar(0, 0, 255), 8);
		imgOrginal(getRegionOfInterest(imgThresholded)).copyTo(imgCut);
		imshow("Thresholded Image", imgThresholded);
		imshow("Orginal", imgOrginal);
		imshow("Cut", imgCut);

		switch(waitKey(10)){
			case 27: //ESC
				return EXIT_SUCCESS;
				break;
			default:
				//do nothing
				break;
		}
	}

	return EXIT_SUCCESS;
}
