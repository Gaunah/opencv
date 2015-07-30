all: 
	g++ -Wall cam.cpp -o cam -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect
