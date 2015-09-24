CFLAGS=-std=c++11 -Wall
LIBS=-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect

cam: cam.cpp 
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

writer: writer.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

color_detection: color_detection.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

color_tracking: color_tracking.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

motion_tracking: motion_tracking.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

cannyfilter: cannyfilter.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

test: test.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

clean:
	rm -rf bin 
