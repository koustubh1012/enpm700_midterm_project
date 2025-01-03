// Include the necessary header files and dependencies
#include "DepthMapApp.hpp"

#include <iostream>
#include <opencv2/opencv.hpp>

// Constructor for the DepthMapApp class
DepthCalculator::DepthCalculator(float focal_length, float rw_height)
    : focal_length(focal_length), rw_height(rw_height) {}

float DepthCalculator::calculateDepth(float h) const {
  // Check if h is less than or equal to zero, if so return -1.0f
  if (h <= 0) {
    std::cerr << "Error: h must be greater than zero to calculate depth."
              << std::endl;
    return -1.0f;
  }

  // Calculate the depth using the formula: Depth = (focal_length * rw_height) /
  // h
  return (focal_length * rw_height) / h;
}

// Function to display depth on the frame
void DepthCalculator::displayDepth(cv::Mat &frame, float depth,
                                   const cv::Rect &bounding_box) const {
  // Draw a rectangle around the object
  cv::rectangle(frame, bounding_box, cv::Scalar(0, 255, 0), 2);

  // Display the depth on the frame
  std::string depth_text = "Depth (Z): " + std::to_string(depth) + " meters";

  // Display the depth on the frame
  cv::putText(frame, depth_text, cv::Point(100, 90), cv::FONT_HERSHEY_SIMPLEX,
              0.6, cv::Scalar(255, 0, 0), 2);
  // cv::imshow("Webcam", frame);
}
