// paly a video file forwards

#include <opencv/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]){
  VideoCapture cap("C:/filename.mp4");
  if (cap.isOpened()==false){
    cout<< "Cannot open the video file"<<endl;
    return -1;  
  }

  double fps = cap.get(CAP_PROP_FPS);
  cout<<"Frames per Seconds:  "<< fps <<endl;

  String window_name = "Show the video";
  namedWindow(window_name, WINDOW_NORMAL);

  while(true){
    Mat frame;
    bool bSuccess = cap.read(frame);

    if (bSuccess == false){
      cout << "Found the end of the video"<<endl;
      break;
    }

    imshow(window_name, frame);
    if (waitKey(10) == 27){
      cout << "Esc key is pressend by user. Stopping the video"<<endl;
      break;
    }

  }

  return 0;

}