//create trackbar

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat src;

void MyCallbackForBrightness(int iValueForBrightness, void* userData)
{
    Mat dst;
    int iValueForContrast = *(static_cast<int*> (userData));

    int iBrightness = iValueForBrightness - 50;
    double dContrast = iValueForContrast / 50.0;

    cout << "MyCallbackForBrightness: Contrast = " << dContrast <<", Brightness = " << iBrightness << endl;

    src.convertTo(dst, -1, dContrast, iBrightness);
    imshow("My Window", dst);
}

void MyCallbackForContrast(int iValueForContrast, void* userData)
{
    Mat dst;
    int iValueForBrightness = *(static_cast<int*>(userData));

    int iBrightness = iValueForBrightness - 50;
    double dContrast = iValueForContrast / 50.0;

    cout << "MyCallbackForBrightness: Contrast = " << dContrast <<", Brightness = " << iBrightness << endl;

    src.convertTo(dst, -1, dContrast, iBrightness);

    imshow("My Window", dst);
}

int main(int argc, char** argv)
{
    src = imread("me.jpg");
    if (src.data == false)
    {
        cout << "Error loading the image" << endl;
        return -1; 
    }
    namedWindow("My Window", 1);
    int iValueForBrightness = 50;
    int iValueForContrast = 50;

    createTrackbar("Brightness", "My Window", &iValueForBrightness, 100, MyCallbackForBrightness, &iValueForContrast);
    createTrackbar("Contrast", "My Window", &iValueForContrast, 100, MyCallbackForContrast, &iValueForBrightness);

    imshow("My Window", src);
    waitKey(0);
    return 0;
}