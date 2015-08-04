#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>


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

	Mat imgOrginal, imgOrginal2, imgGray1, imgGray2, imgDiff;	
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

		if(tracking){
			//tracking action	
		}
		
		imshow("Orginal", imgDiff);

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
