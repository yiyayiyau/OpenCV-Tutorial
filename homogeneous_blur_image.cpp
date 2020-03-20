// Homogeneous Blur on Images

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    // Read the image file
    Mat image = imread("D:/My OpenCV Website/Lady with a Guitar.jpg");

    // Check for failure
    if (image.empty())
    {
        cout << "Could not open or find the image" << endl;
        cin.get(); //wait for any key press
        return -1;
    }

    Mat image_blurred_with_3x3_kernel;
    blur(image, image_blurred_with_3x3_kernel, Size(3, 3));

    Mat image_blurred_with_5x5_kernel;
    blur(image, image_blurred_with_5x5_kernel, Size(5, 5));

    String window_name = "The Guitar";
    String window_name_blurred_with_3x3_kernel = "The Guitar Blurred with 3x3 Kernel";
    String window_name_blurred_with_5x5_kernel = "The Guitar Blurred with 5x5 Kernel";

    namedWindow(window_name);
    namedWindow(window_name_blurred_with_3x3_kernel);
    namedWindow(window_name_blurred_with_5x5_kernel);

    imshow(window_name);
    imshow(window_name_blurred_with_3x3_kernel);
    imshow(window_name_blurred_with_5x5_kernel);

    waitKey(0);
    destoryAllWindows();
    return 0;
    
}