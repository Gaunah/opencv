#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>

void morphOps(cv::Mat &img, cv::Mat const &structuringElement){
	//morphological opening (remove small objects from the foreground)	
	cv::erode(img, img, structuringElement);
	cv::dilate(img, img, structuringElement);
	//morphological closing (fill small holes in the foreground)	
	cv::dilate(img, img, structuringElement);
	cv::erode(img, img, structuringElement);
}

int main(){
	using namespace cv;

	VideoCapture cap(0);
	if(!cap.isOpened()){
		std::cerr << "could not open webcam!" << std::endl;
		return EXIT_FAILURE;
	}

	namedWindow("Control", CV_WINDOW_AUTOSIZE);
	int lowH = 0, highH = 179;
	int lowS = 0, highS = 255;
	int lowV = 0, highV = 255;

	cvCreateTrackbar("LowH", "Control", &lowH, 179);
	cvCreateTrackbar("HighH", "Control", &highH, 179);

	cvCreateTrackbar("LowS", "Control", &lowS, 255);
	cvCreateTrackbar("HighS", "Control", &highS, 255);

	cvCreateTrackbar("LowV", "Control", &lowV, 255);
	cvCreateTrackbar("HighV", "Control", &highV, 255);

	Mat imgOrginal, imgHSV, imgThresholded;
	Mat se = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	while(true){
		if(!cap.read(imgOrginal)){
			std::cerr << "could not read frame from video stream!" << std::endl;
			return EXIT_FAILURE;
		}
		
		cvtColor(imgOrginal, imgHSV, COLOR_BGR2HSV);
		inRange(imgHSV, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), imgThresholded);
	
		morphOps(imgThresholded, se);
		imshow("Thresholded Image", imgThresholded);
		imshow("Orginal", imgOrginal);

		switch(waitKey(30)){
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
