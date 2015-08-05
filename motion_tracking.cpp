#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

//int const SENSITIVTY = 10;
//int const BLUR_SIZE = 30;


std::string const intToString(int n){
	std::stringstream ss;
	ss << n;
	return ss.str();
}

cv::Rect const searchForMovement(cv::Mat const &imgThreshold){
	cv::Mat tmp;
	imgThreshold.copyTo(tmp); // i don't know why this is necessary :(
	cv::Rect boundingRectangle;
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(tmp, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	if(contours.size() > 0){ //found something
		boundingRectangle = cv::boundingRect(contours[contours.size() - 1]);
	}
	return boundingRectangle;
}

void const drawObject(cv::Point const &center, cv::Mat &frame, bool showCoords = false){
	cv::Scalar color(0, 255, 0);
	if(center.x > 0 && center.y > 0){ cv::circle(frame, center, 15, color, 2); }
	if(showCoords){
		std::string coords = "x" + intToString(center.x) + " y" + intToString(center.y);
		cv::putText(frame, coords, cv::Point(center.x + 20, center.y), 1, 1, color, 1);
	}
}

void const intro(){
	using namespace std;
	cout << "ECS: Quit" << endl;
	cout << "SPACEBAR: toggle tracking" << endl;
	cout << "c: toggle coords" << endl;
}

int main(){
	using namespace cv;
	intro();

	VideoCapture cap(0);
	if(!cap.isOpened()){
		std::cerr << "could not open webcam!" << std::endl;
		return EXIT_FAILURE;
	}

	namedWindow("Control", CV_WINDOW_AUTOSIZE);
	int SENSITIVTY = 10, BLUR_SIZE = 30;
	cvCreateTrackbar("Sensitivity", "Control", &SENSITIVTY, 100);
	cvCreateTrackbar("Blur size", "Control", &BLUR_SIZE, 100);

	Mat imgOrginal, imgOrginal2, imgGray1, imgGray2, imgDiff, imgThreshold;	
	bool tracking = false, showCoords = false;
	while(true){
		if(!cap.read(imgOrginal)){
			std::cerr << "could not read frame from video stream!" << std::endl;
			return EXIT_FAILURE;
		}
		cvtColor(imgOrginal, imgGray1, COLOR_BGR2GRAY);
		cap.read(imgOrginal2);
		cvtColor(imgOrginal2, imgGray2, COLOR_BGR2GRAY);

		absdiff(imgGray1, imgGray2, imgDiff);
		blur(imgDiff, imgDiff, Size(BLUR_SIZE+1, BLUR_SIZE+1));
		threshold(imgDiff, imgThreshold, SENSITIVTY, 255, THRESH_BINARY);
		
		if(tracking){
			Rect r = searchForMovement(imgThreshold);
			drawObject(Point(r.x + r.width / 2, r.y + r.height / 2), imgOrginal, showCoords);
		}
		
		imshow("Thresholded", imgThreshold);
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
