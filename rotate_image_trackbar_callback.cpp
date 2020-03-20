// rotate image

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
int iAngle = 180;
int iScale = 50;
int iBorderMode = 0;

Mat img;
int iImageCenterX = 0;
int iImageCenterY = 0;
const char* window_name_rotated_image = "Rotated image";

void CallbackForTrackbar(int, void*)
{
    Mat matRotation = getRotationMatrix2D( Point(iImageCenterX, iImageCenterY), (iAngle -180), iScale/50.0 );

    Mat imgRotated;
    warpAffine(img, imgRotated, matRotation, img.size(), INTER_LINEAR, iBorderMode, Scalar());

    imshow(window_name_rotated_image, imgRotated);
}

int main(int argc, char** argv)
{
    img = imread("me.jpg", 1);
    iImageCenterX = img.rows/2;
    iImageCenterY = img.cols/2;

    const char* window_name_original_image = "Original Image";
    namedWindow(img, CV_WINDOW_AUTOSIZE);
    imshow(window_name_original_image, img);

    namedWindow(window_name_rotated_image, CV_WINDOW_AUTOSIZE);
    createTrackbar("Angle",window_name_rotated_image, &iAngle, 360, CallbackForTrackbar);
    createTrackbar("Scale", window_name_rotated_image, &iScale, 100, CallbackForTrackbar);
    createTrackbar("Border Mode", window_name_rotated_image, &iBorderMode, 5, CallbackForTrackbar);

    int iDummy = 0;
    CallbackForTrackbar(iDummy, &iDummy);
    waitKey(0);

    return 0;
}