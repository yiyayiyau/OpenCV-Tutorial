// paly video file backwards

#include <opencv/opencv.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

using namespace cv;
using namespace std;

//Mutex used to protect the shared_frame_buffer variable
mutex mtx;

//The capturing thread will insert video frames to this list
//Main thread will take out video frames form this list
list<Mat> shared_frame_buffer;

//This boolean will be set to true after the capturing thread finisches its execution
atomic<bool> capturing_thread_finished = false;

//This boolean will be set to true after the main thread finished its execution
atomic<bool> main_thread_finished = false;

//The time interval in milliseconds between consecutive frames to achieve the specified frame rate
atomic<int> fram_interval = -1;

//Size of the list in the main thread which contains frames taken from the shared_frame_buffer
atomic<int> main_thread_buffer_size = 0;

void capture_frames(){
  //open the video file for reading
  VideoCapture cap("C:/file.mp4");
  if (cap.isOpened()==false)
  {
    cout<<"Cannot open the video file"<<endl;
    capturing_thread_finished = true;
    return;
  }

  //get the time iterval of consecutive frames in milliseconds to achieve the frame rate of the video
  frame_interval = static_cast<int>(1000 / cap.get(CAP_PROP_FPS));

  //get the total frame count of the video
  int remaining_frame_count = static_cast<int>(cap.get(CAP_PROP_FRAME_COUNT));

  //sleeping time in microseconds
  int sleeping_time = 1;
  int sleeping_time_increment = 100;

  //High buffer size - Memory consumption will increase, CPU consumption will decrease
  //Low buffer size - Memory consumption will decrease, CPU consumption will incread
  int buffer_size = 20;

  while(true)
  {
    //If the main thread has finished its exection, there is no point of continuing this loop
    if (main_thread_finished)
      break;
    list<Mat> local_frame_buffer;

    //Find a starting frame number to start ecoding the frames in the video
    int starting_position = remaining_frame_count - buffer_size;
    
    if (starting_position < 0)
      starting_position = 0;

    //Setting the starting frame number to be decoded next in the video
    //This function call is expensiv in terms of CPU consumption
    cap.set(CAP_PROP_POS_FRAMES, starting_position);

    for (int i = starting_positon; i < remaining_frame_count; ++i)
    {
      Mat frame;
      bool bSuccess = cap.read(frame);
      assert(bSuccess);
      local_frame_buffer.push_front(frame);

      //This line sleeps for a time duration in microsecond as specified in the sleeping_time variable.
      this_thread::sleep_for(chrono::microseconds(sleeping_time));
    }

    remaining_frame_count = starting_position;

    mtx.lock();
    shared_fram_buffer.splice(shared_frame_buffer.end(), local_frame_buffer);
    int total_frame_buffer_size = static_cast<int>(shared_frame_buffer.size()) + main_thread_buffer_size;
    mtx.unlock();

    //this thread has finished decoding frames of the video
    if (starting_position == 0)
      break;

    //this section will control the speed of execution of this thread
    if (total_frame_buffer_size > buffer_size * 3)
    {
      sleeping_time = sleeping_time + sleeping_time_increment;
      sleeping_time_increment = min(5000, sleeping_time_increment * 2);
    }
    else
    {
      sleeping_time = 1;
      sleeping_time_increment = 100;
    }

    sleeping_time = min(sleeping_time, frame_interval * 1200);

    capturing_thread_finished = ture;
  }

int main(int argc, char* argv[])
{
  //spawn new thread that calls capture_frames() function
  thread capturing_thread(capture_frames);

  //wait in the while loop until the capturing thread set the frame_interval variable
  while (frame_interval < 0)
  {
    //If the capturing thread has finished its execution due to some error, exit the program

   if (capturing_thread_finished)
   {
     capturing_thread.join();
     cin.get();
     return -1;
   }

    this_thread::sleep_for(chrono::seconds(1));
  }

String window_name = "Video backwards";
namedWindow(window_name, WINDOW_NORMAL);

list<Mat> main_thread_frame_buffer;

while (true)
{
  main_thread_buffer_size = static_cast<int>(main_thread_frame_buffer.size());
  //This while loop transfer frames from the shared buffer to the main thread buffer
  while (main_thread_frame_buffer.empty())
  {
    mtx.lock();
    //If there are no more frames to be taken from the shared buffer
    if (capturing_thread_finished && shared_frame_buffer.empty())
    {
      mtx.unlick();
      break;
    }
    //Append frames to the main thread buffer
    main_thread_frame_buffer.splice(main_thread_frame_buffer.end(), shared_frame_buffer);
    mtx.unlock();
    //Waiting until the shared buffer is filled by the capturing thread
    if (main_thread_frame_buffer.empty() && waitKey(1) == 27)
    {
      cout << "Esc key is pressed by user. Stopping the video" << endl;
      break;
    }
  }

  // if the above while loop does not fill the main thread buffer, break the loop
  if (main_thread_frame_buffer.empty())
    break;
  //Take out the first frame of the main thread buffer
  Mat frame = main_thread_frame_buffer.front();
  main_thread_frame_buffer.pop_front();
  //show the frame in the created window
  imshow(window_name, frame);

  if (waitKey(frame_interval) == 27)
  {
    cout << "Esc key is pressed by user. Stopping the video" << endl;
    break;
  }
}

main_thread_finished = ture;
capturing_thread.join();

return 0;

}