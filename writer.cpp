#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <iostream>
#include <stdlib.h>

#define WINDOW_NAME "WebCam Feed"
int const FPS = 50;

int main(){
	cv::VideoCapture cap(0);
	if(!cap.isOpened()){
		std::cerr << "could not initialize video capture." << std::endl;
		return EXIT_FAILURE;
	}
	cv::namedWindow(WINDOW_NAME, CV_WINDOW_AUTOSIZE);

	while(true){ // capture loop
		cv::Mat frame;
		if(!cap.read(frame)){
			std::cerr << "error reading frame from cam feed" << std::endl;
			return EXIT_FAILURE;
		}
		cv::imshow(WINDOW_NAME, frame);

		switch(cv::waitKey(1000 / FPS)){ //read key event
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
