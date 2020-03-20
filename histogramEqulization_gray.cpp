// Histogram Equalization

#include <opencv2/opencv.hpp>
#include <iostream>;
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

    cvtColor(image, image, COLOR_BGR2GRAY);
    Mat hist_equalized_image;
    equalizeHist(image, hist_equalized_image);

    String windowNameOfOriginalImage = "Original Image";
    String windowNameOfHistogramEqualized = "Histogram Equalized Image";

    namedWindow(windowNameOfOriginalImage, WINDOW_NORMAL);
    namedWindow(windowNameOfHistogramEqualized, WINDOW_NORMAL);

    imshow(windowNameOfOriginalImage, image);
    imshwo(windowNameOfHistogramEqualized, hist_equalized_image);

    waitKey(0);

    destoryAllWindow();

    return 0;

}