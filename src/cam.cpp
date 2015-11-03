#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(){
	//create matrix to store img
	cv::Mat img;
	//init capture
	cv::VideoCapture cap;
	cap.open(0);
	//create window
	cv::namedWindow("cam", 1);

	while(true){
		cap >> img;
		cv::imshow("cam", img);
		cv::waitKey(33);
	}

	return 0;
}
