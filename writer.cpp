#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdlib.h>

#define WINDOW_NAME "WebCam Feed"
#define FILE_NAME "test.avi"
int const FOURCC = CV_FOURCC('D','I','V','3');
int const FPS = 25;

int main(){
	std::cout << "SPACEBAR: Toggle recording" << std::endl;
	std::cout << "ESC: Quit programm" << std::endl;

	cv::VideoCapture cap(0);
	if(!cap.isOpened()){
		std::cerr << "could not initialize video capture." << std::endl;
		return EXIT_FAILURE;
	}
	cv::Size const FRAME_SIZE(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));

	cv::VideoWriter writer(FILE_NAME, FOURCC, FPS, FRAME_SIZE);
	if(!writer.isOpened()){
		std::cerr << "error opening videowriter" << std::endl;
		return EXIT_FAILURE;
	}
	
	cv::namedWindow(WINDOW_NAME, CV_WINDOW_AUTOSIZE);
	cv::Mat frame;
	bool recording = true;
	while(true){ // capture loop
		if(!cap.read(frame)){
			std::cerr << "error reading frame from cam feed" << std::endl;
			return EXIT_FAILURE;
		}
		if(recording){
			writer.write(frame);
			cv::putText(frame, "[REC]", cv::Point(0, 20), 1, 1, cv::Scalar(0,0,255));
		}
		cv::imshow(WINDOW_NAME, frame);

		switch(cv::waitKey(1000 / FPS)){ //read key event
			case 27: //ESC
				return EXIT_SUCCESS;
				break;
			case 32: // SPACEBAR
				recording = !recording;
				break;
			default:
				//do nothing
				break;
		}
	}

	return EXIT_SUCCESS;
}
