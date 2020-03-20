//save images

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
  Mat image = imread("C:/me.jpg");
  if (image.empty())
  {
    cout << "Could not open or find the image" <<endl;
    cin.get();
    return -1;
  }
/* Make changes to the image as necessary
1. Change brightness/contrast of the image
2. Smooth/Blur image
3. Crop the image
4. Rotate the image
5. Draw shapes on the image
*/

bool isSuccess = imwrite("C:/me2.jpg", image);
if (isSuccess == false)
{
  cout << "Failed to save the image" << endl;
  cin.get();
  return -1;
}

cout << "Image is succusfully saved to a file"<< endl;

String windowName = "The saved image";
namedWindow(windowname, WINDOW_NORMAL);
imshow(windowname, image);

waitKey(0);

destroyWindow(windowName);

return 0;

}