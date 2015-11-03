#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <sstream>
#include <stdlib.h>
#include <string>

int const MIN_AREA = 30*30;


std::string const intToString(int n){
	std::stringstream ss;
	ss << n;
	return ss.str();
}

void const drawObject(cv::Point const &center, cv::Mat &frame, bool showCoords = false){
	cv::Scalar color(0, 255, 0);
	cv::circle(frame, center, 15, color, 2);
	if(showCoords){
		std::string coords = "x" + intToString(center.x) + " y" + intToString(center.y);
		cv::putText(frame, coords, cv::Point(center.x + 20, center.y), 1, 1, color, 1);
	}
}

cv::Point const findObject(cv::Mat const &imgThresholed){
	int posX = 0, posY = 0;
	cv::Moments mom = moments(imgThresholed);
	if(mom.m00 > MIN_AREA){
		posX = mom.m10 / mom.m00;	
		posY = mom.m01 / mom.m00;	
	}
	return cv::Point(posX, posY);
}

void const morphOps(cv::Mat &img, cv::Mat const &structuringElement){
	//morphological opening (remove small objects from the foreground)	
	cv::erode(img, img, structuringElement);
	cv::dilate(img, img, structuringElement);
	//morphological closing (fill small holes in the foreground)	
	cv::dilate(img, img, structuringElement);
	cv::erode(img, img, structuringElement);
}

void const intro(){
	using namespace std;
	cout << "ECS: Quit" << endl;
	cout << "SPACEBAR: toggle tracking" << endl;
	cout << "c: toggle coords" << endl;
}

int main(int argc, char* argv[]){
	using namespace cv;
	intro();

	VideoCapture cap;
	if(argc == 2){
		cap.open(argv[1]);
	} else {
		cap.open(0);
	}

	if(!cap.isOpened()){
		std::cerr << "could not open webcam!" << std::endl;
		return EXIT_FAILURE;
	}

	//Control window
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
	////

	namedWindow("Orginal", CV_WINDOW_KEEPRATIO);
	namedWindow("Thresholded Image", CV_WINDOW_KEEPRATIO);

	Mat imgOrginal, imgHSV, imgThresholded;
	Mat se = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	bool tracking = false, showCoords = false;
	while(true){
		if(!cap.read(imgOrginal)){
			std::cerr << "could not read frame from video stream!" << std::endl;
			return EXIT_FAILURE;
		}

		cvtColor(imgOrginal, imgHSV, COLOR_BGR2HSV);
		inRange(imgHSV, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), imgThresholded);

		morphOps(imgThresholded, se);
		imshow("Thresholded Image", imgThresholded);
		if(tracking){
			Point p = findObject(imgThresholded);
			if(p.x != 0 && p.y != 0){
				drawObject(p, imgOrginal, showCoords);
			}
		}
		imshow("Orginal", imgOrginal);

		int keyCode = waitKey(30);
		switch(keyCode){
			case 27: //ESC
				return EXIT_SUCCESS;
				break;
			case 32: //SPACEBAR
				tracking = !tracking;
				break;
			case 99: // c key
				showCoords = !showCoords;
				break;
			default:
				if(keyCode >= 0){
					std::cout << "keyCode: " << keyCode << std::endl;
				}
				break;
		}
	}

	return EXIT_SUCCESS;
}
