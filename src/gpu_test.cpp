#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/gpu/gpu.hpp"

int main (int argc, char* argv[]) {
	using namespace cv;
	Mat src_host; 

	if(argc == 2){
		src_host = imread(argv[1]);
	} else {
		std::cerr << "usage: ./gpu_test <img file>" << std::endl;
		return -1;
	}
	if(!src_host.data){
		std::cerr << "could not read img from: " << argv[1] << std::endl;
		return -1;
	}

	try {
		gpu::GpuMat dst, src;
		src.upload(src_host);

		gpu::threshold(src, dst, 128.0, 255.0, CV_THRESH_BINARY);

		Mat result_host(dst);
		imshow("Result", result_host);
		waitKey();
	} catch(const Exception& ex) {
		std::cout << "Error: " << ex.what() << std::endl;
	}
	return 0;
}
