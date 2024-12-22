#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include<iostream>

using namespace std;
using namespace cv;

void detectAndDisplay(Mat frame){
   CasecadeClassifier face_cascade;
   String face_cascade_name;

}


int main(int agrc , const char** argv){
    CommandLineParser parser(argc , argv , "{camera|0|Camera device number.}");
    face_cascade_name = "C:/Downloads/OpenCV CPP/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml"
   if(!face_cascade.load(face_casecade_name)){
      cout<<"--!! Error loading face casecade \n";
      return -1;
   };

   int camera_device = parser.get<int>("camera");

   VideoCapture capture;

   capture.open(camera_device);

   if(!captured.isOpened()){
      cout<<" -- Error loading video capture \n";
      return -1;
   }

   Mat frame;

   int width = 640;
   int height = 480;

   capture.set(CAP_PROP_FRAME_WIDTH , width);
   capture.set(CAP_PROP_FRAME_HEIGHT , height);


   while(capture.read(frame))
    if(frame.empty()){
        cout<<"--!! No captured frame detected\n";
        break;
    }

    detectAndDisplay(frame);

    if(waitKey(10) == 27){
        break;
    }
  
  return 0;

}

void DetectAndDisplay(Mat Frame){
    Mat frame_gray;
    cvtColor(frame , frame_gray , COLOR_BGR2GRAY);
    equlizeHist(frame_gray , frame_gray);
    std::vector<Rect> faces;
    face_cascade.detectMultiScale(frame_gray , faces);

    for(size_t = 0 ; i < faces.size() ; i++){

        Mat faceROI = frame_gray(faces[i]);
        int x = faces[i].x;
        int y = faces[i].y;
        int h = y + faces[i].height;
        int w = y + faces[i].width;
        rectangle(frame , Point(x , y) , Point(w , h) , Scaler(255 , 0 , 255) , 2 , 0 , 8);
        imshow("Face Detection" , frame);


    }



}
