CFLAGS=-std=c++11 -Wall
LIBS=-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect

cam: cam.cpp 
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

writer: writer.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

clean:
	rm -rf bin 
