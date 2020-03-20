//Rotate image

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main(int argc, char** argv)
{
    Mat img = imread("me.jpg", 1);
    if (img.data == false)
    {
        cout << "Error loading the image" << endl;
        return -1; 
    }

    const char* window_name_Original_Image = "Original Image";
    namedWindow(window_name_Original_Image, CV_WINDOW_AUTOSIZE);
    imshow(window_name_Original_Image, img);

    const char* window_name_Rotate_Image = "Rotated Image";
    namedWindow(window_name_Rotate_Image, CV_WINDOW_AUTOSIZE);

    int iAngle = 180;
    createTrackbar("Angle", window_name_Rotate_Image, &iAngle, 360);
    
    int iImageHeight = img.rows/2;
    int iImageWidth = img.cols/2;
    while(true)
    {
        Mat matRotation = getRotationMatrix2D(Point(iImageHeight,iImageWidth),(iAngle -180), 1);

        Mat imgRotated;
        warpAffine(img, imgRotated, matRotation, img.size());

        imshow(window_name_Rotate_Image, imgRotated);

        int iRet = waitKey(30);
        if(iRet == 27)
        {
            break;
        }
    }

    return 0;
}