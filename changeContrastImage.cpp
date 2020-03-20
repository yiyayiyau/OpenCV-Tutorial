//change contrast image
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat image = imread("C:/me.jpg");
    if (image.empty())
    {
        cout << "Could not open or find the image" << endl;
        cin.get();
        return -1;
    }

    Mat imageContrastHigh2;
    image.convertTo(imageContrastHigh2, -1, 2, 0);

    Mat imageContrastHigh4;
    image.convertTo(imageContrastHigh4, -1, 4, 0);

    Mat imageContrastLow0_5;
    image.convertTo(imageContrastLow0_5, -1, 0.5, 0);

    String WindowNameOriginalImage = "Original Image";
    namedWindow(WindowNameOriginalImage, WINDOW_NORMAL);

    String WindowNameContrastHigh2 = "Contrast Increased by 2";
    namedWindow(WindowNameContrastHigh2, WINDOW_NORMAL);

    String WindowNameContrastHigh4 = "Contrast Increased by 4";
    namedWindow(WindowNameContrastHigh4, WINDOW_NORMAL);

    String WindowNameContrastLow0_5 = "Contrast Decreased by 0.5";
    namedWindow(WindowNameContrastLow0_5, WINDOW_NORMAL);

    imshow(WindowNameOriginalImage, image);
    imshow(WindowNameContrastHigh2, imageContrastHigh2);
    imshow(WindowNameContrastHigh4, imageContrastHigh4);
    imshow(WindowNameContrastLow0_5, imageContrastLow0_5);

    WaitKey(0);

    destoryAllWindow();

    return 0;


}