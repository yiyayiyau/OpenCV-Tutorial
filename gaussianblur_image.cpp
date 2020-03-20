//Gaussian blur/smoothing is the most commonly used smoothing technique to eliminate noises in images and videos.

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    // Read the image file
    Mat image = imread("D:/My OpenCV Website/Lotus.jpeg");

    // Check for failure
    if (image.empty())
    {
        cout << "Could not open or find the image" << endl;
        cin.get(); //wait for any key press
        return -1;
    }

    Mat image_blurred_with_3x3_kernel;
    GaussianBlur(image, image_blurred_with_3x3_kernel, Size(3, 3), 0);

    Mat image_blurred_with_5x5_kernel;
    GaussianBlur(image, image_blurred_with_5x5_kernel, Size(5, 5), 0);

    String window_name = "Lotus";
    String window_name_blurred_with_3x3_kernel = "Lotus Blurred with 3x3 Gaussian Kernel";
    String window_name_blurred_with_5x5_kernel = "Lotus Blurred wiht 5x5 Gaussian Kernel";

    namedWindow(window_name);
    namedWindow(window_name_blurred_with_3x3_kernel);
    namedWindow(window_name_blurred_with_5x5_kernel);

    imshow(window_name, image);
    imshow(window_name_blurred_with_3x3_kernel, image_blurred_with_3x3_kernel);
    imshow(window_name_blurred_with_5x5_kernel, image_blurred_with_5x5_kernel);

    waitKey(0);
    destoryAllWindows();

    return 0;

}
