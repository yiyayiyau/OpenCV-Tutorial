// Histogram Euqalization YCrCb

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    // Read the image file
    Mat image = imread("D:/My OpenCV Website/fly-agaric.jpg");

    // Check for failure
    if (image.empty())
    {
        cout << "Could not open or find the image" << endl;
        cin.get(); //wait for any key press
        return -1;
    }

    Mat hist_equlized_image;
    cvtColor(image, hist_equlized_image, COLOR_BGR2YCrCb);

    vector<Mat> vec_channels;
    split(hist_equlized_image, vec_channels);

    equalizeHist(vec_channels[0], vec_channels[0]);

    merge(vec_channels, hist_equlized_image);

    cvtColor(hist_equlized_image, hist_equlized_image, COLORYCrCb2BGR);

    String windowNameOfOriginalImage = "Original Image"; 
    String windowNameOfHistogramEqualized = "Histogram Equalized Color Image";

    // Create windows with the above names
    namedWindow(windowNameOfOriginalImage, WINDOW_NORMAL);
    namedWindow(windowNameOfHistogramEqualized, WINDOW_NORMAL);

    // Show images inside the created windows.
    imshow(windowNameOfOriginalImage, image);
    imshow(windowNameOfHistogramEqualized, hist_equalized_image);

    waitKey(0); // Wait for any keystroke in any one of the windows

    destroyAllWindows(); //Destroy all opened windows

    return 0;
}    