CFLAGS=-std=c++11 -Wall
LIBS=-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect

cam: src/cam.cpp 
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

writer: src/writer.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

color_detection: src/color_detection.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

color_tracking: src/color_tracking.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

motion_tracking: src/motion_tracking.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

cannyfilter: src/cannyfilter.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

cut_image: src/cut_image.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

histogram: src/histogram.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

kmeans: src/kmeans.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

mean_shift_seg: src/mean_shift_seg.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

gpu_test: src/gpu_test.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) -lopencv_gpu $< -o bin/$@

hough_circle: src/hough_circle.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

clean:
	rm -rf bin 
