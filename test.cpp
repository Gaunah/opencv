// Usage: ./app input.jpg
#include "opencv2/opencv.hpp"
#include <string>

using namespace cv;
using namespace std;

class WatershedSegmenter{
	private:
		cv::Mat markers;
	public:
		void setMarkers(cv::Mat& markerImage)
		{
			markerImage.convertTo(markers, CV_32S);
		}

		cv::Mat process(cv::Mat &image)
		{
			cv::watershed(image, markers);
			markers.convertTo(markers,CV_8U);
			return markers;
		}
};


int main(int argc, char* argv[])
{
	cv::Mat image = cv::imread(argv[1]);
	cv::Mat blank(image.size(),CV_8U,cv::Scalar(0xFF));
	cv::Mat dest;
	namedWindow("originalimage", CV_WINDOW_KEEPRATIO);
	imshow("originalimage", image);

	// Create markers image
	cv::Mat markers(image.size(),CV_8U,cv::Scalar(-1));
	//Rect(topleftcornerX, topleftcornerY, width, height);
	//top rectangle
	markers(Rect(0,0,image.cols, 5)) = Scalar::all(1);
	//bottom rectangle
	markers(Rect(0,image.rows-5,image.cols, 5)) = Scalar::all(1);
	//left rectangle
	markers(Rect(0,0,5,image.rows)) = Scalar::all(1);
	//right rectangle
	markers(Rect(image.cols-5,0,5,image.rows)) = Scalar::all(1);
	//centre rectangle
	int centreW = image.cols/4;
	int centreH = image.rows/4;
	markers(Rect((image.cols/2)-(centreW/2),(image.rows/2)-(centreH/2), centreW, centreH)) = Scalar::all(2);
	markers.convertTo(markers,CV_BGR2GRAY);
	namedWindow("markers", CV_WINDOW_KEEPRATIO);
	imshow("markers", markers);

	//Create watershed segmentation object
	WatershedSegmenter segmenter;
	segmenter.setMarkers(markers);
	cv::Mat wshedMask = segmenter.process(image);
	cv::Mat mask;
	convertScaleAbs(wshedMask, mask, 1, 0);
	//double thresh = threshold(mask, mask, 1, 255, THRESH_BINARY);
	bitwise_and(image, image, dest, mask);
	dest.convertTo(dest,CV_8U);

	namedWindow("final_result", CV_WINDOW_KEEPRATIO);
	imshow("final_result", dest);
	cv::waitKey(0);

	return 0;
}
