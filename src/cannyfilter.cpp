#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int static low = 0, high = 255, sigma = 0;

void createControlPanel(){
	cv::namedWindow("Control", CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar("Low", "Control", &low, 255);
	cvCreateTrackbar("High", "Control", &high, 255);
	cvCreateTrackbar("Sigma", "Control", &sigma, 5);
}

int main(int argc, char* argv[]){
	using namespace cv;
	VideoCapture cap;

	if(argc == 2){ // open file or cam
		cap.open(argv[1]);
	} else {
		cap.open(0);
	}

	if(!cap.isOpened()){
		std::cerr << "could not open file or cam!" << std::endl;
		return -1;
	}

	createControlPanel();
	Mat imgOriginal, imgGray, imgCanny;
	while(true){ //loop until ESC
		if(!cap.read(imgOriginal)){
			std::cerr << "could not read frame from video stream!" << std::endl;
			return -1;
		}

		cvtColor(imgOriginal, imgGray, COLOR_BGR2GRAY); //convert to grayscale
		GaussianBlur(imgGray, imgGray, Size(5, 5), sigma);
		Canny(imgGray, imgCanny, low, high);

		namedWindow("Original", CV_WINDOW_KEEPRATIO);
		namedWindow("Canny", CV_WINDOW_KEEPRATIO);
		imshow("Original", imgOriginal);
		imshow("Canny", imgCanny);

		switch(waitKey(10)){
			case 27: //ESC
				return 0;
				break;
			default:
				break;	
		}
	}
	return 0;
}
