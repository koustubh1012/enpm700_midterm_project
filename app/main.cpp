#include <iostream>            // C++ standard library header
#include <opencv2/opencv.hpp>  // Other library header
#include <random>              // C++ standard library header
#include <unordered_map>       // C++ standard library header
#include <vector>              // C++ standard library header

#include "humanposeestimator.hpp"  // Project-specific header

int main() {
  HumanPoseEstimator pose_estimator_obj;

  std::unordered_map<int, std::vector<float>> human_poses;

  // Open video capture (0 for webcam, or replace with a video file path)
  cv::VideoCapture cap(0, cv::CAP_V4L2);
  if (!cap.isOpened()) {
    std::cerr << "Error: Couldn't open video capture" << std::endl;
    return -1;
  }

  cv::Mat frame;
  while (cap.read(frame)) {
    human_poses = pose_estimator_obj.poseEstimator(frame);
    // Show the result
    cv::imshow("Human Detection with Depth", frame);
    // Break if the user presses 'q'
    if (cv::waitKey(1) == 'q') {
      break;
    }
    frame.release();
  }
  cap.release();
  cv::destroyAllWindows();
  return 0;
}
