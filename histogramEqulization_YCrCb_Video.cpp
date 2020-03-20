// Histogram Equalization of a video with OpenCV

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    //Open the video file for reading
    VideoCapture cap("D:/My OpenCV Website/A Herd of Deer Running.mp4");

    // if not success, exit the program
    if (cap.isOpened() == false)
    {
        cout << "Cannot open the video file" << endl;
        cin.get(); //wait for any key press
        return -1;
    }

    //Define the names of windows
    String windowNameOfOriginalImage = "Original Video";
    String windowNameOfHistogramEqualized = "Histogram Equalized Video";

    // Create windows with the above names
    namedWindow(windowNameOfOriginalImage, WINDOW_NORMAL);
    namedWindow(windowNameOfHistogramEqualized, WINDOW_NORMAL);

    while (true)
    {
        Mat frame;
        bool bSuccess = cap.read(frame);
        if (bSuccess == false)
        {
            cout << "Found the end of the video" << endl;
            break;
        }

        Mat hist_equalized_image;
        cvtColor(frame, hist_equalized_image, COLOR_BGR2YCrCb);

        vector<Mat> vec_channels;
        split(hist_equalized_image, vec_channels);

        equalizeHist(vec_channels[0], vec_channels[0]);
        
        merge(vec_channels, hist_equalized_image);

        cvtColor(hist_equalized_image, hist_equalized_image, COLOR_YCrCb2BGR);

        imshow(windowNameOfOriginalImage, frame);
        imshow(windowNameOfHistogramEqualized, hist_equalized_image);

        //Wait for 10 ms until any key is pressed.  
        //If the 'Esc' key is pressed, break the while loop.
        //If the any other key is pressed, continue the loop 
        //If any key is not pressed within 10 ms, continue the loop
        if (waitKey(5) == 27)
        {
            cout << "Esc key is pressed by the user. Stopping the video" << endl;
            break;
        }
    }
    destroyAllWindows(); //Destroy all opened windows

    return 0;

}