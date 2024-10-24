#include "humandetector.hpp"

int main() {
  HumanDetector detector_object;

  std::unordered_map<int, std::vector<int>> detectedhumans;

  // Open video capture (0 for webcam, or replace with a video file path)
  cv::VideoCapture cap(0, cv::CAP_V4L2);
  if (!cap.isOpened()) {
    std::cout << "Error: Couldn't open video capture" << std::endl;
    return -1;
  }
  cv::Mat frame;
  while (cap.read(frame)) {

    detectedhumans = detector_object.detectHuman(frame);
    for (const auto &pair : detectedhumans) {
      std::cout << "Human ID: " << pair.first << " -> Bounding Box: ";
      for (int coord : pair.second) {
        std::cout << coord << " ";
      }
      std::cout << std::endl;
    }
    // Show the result
    imshow("Human Detection", frame);

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