//save a video to a file

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
  VideoCapture cap(0);
  if (cap.isOpened() == false)
  {
    cout << "Cannot open the video camera"<< endl;
    cin.get();
    return -1;
  }

  int frame_width = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH));
  int frame_height = static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT));

  Size frame_size(frame_width, frame_height);
  int frames_per_second = 10;

  VideoWirter oVideoWriter("C:/myVideo.avi", VideoWirter::fourcc('M','J','P','G'), frames_per_second, frame_size, true);
  if (oVideowriter.isOpened() == false)
  {
    cout << "Cannot save the video" << endl;
    cin.get();
    return -1;
  }
  string window_name = "Camara feed";
  namedWindow(window_name, WINDOW_NORMAL);

  while (true)
  {
    Mat frame;
    bool isSuccess = cap.read(frame);
    if (isSuccess == false)
    {
      cout << "Video camera is disconnected" << endl;
      cin.get();
      break;
    }
    /* Make changes to the frame as necessray*/
    oVideoWriter.wirte(frame);
    imshow(window_name, frame);
    if (waitKey(10) == 27)
    {
      cout << "Esc key pressed"<< endl;
      break;
    }


  }

  oVideoWirter.release();

}