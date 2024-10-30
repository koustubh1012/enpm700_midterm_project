/**
 * @file DepthMapApp.hpp
 * @author Swaraj Rao (swarajmr@umd.edu)
 * @brief Header file for Class DepthCalculator
 * @version 0.1
 * @date 2024-10-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

/**
 * @brief DepthCalculator class to detect the distance of human from camera
 *
 */
class DepthCalculator {
 public:
  // Constructor for the DepthMapApp class
  /**
   * @brief Construct a new Depth Calculator object
   *
   * @param focal_length
   * @param rw_height
   */
  DepthCalculator(float focal_length = 800, float rw_height = 1.5);

  // Function to calculate depth from h
  /**
   * @brief method to calculate the distance from camera
   *
   * @param h height of object in pixel
   * @return float
   */
  float calculateDepth(float h) const;

  // Function to display depth on the frame
  /**
   * @brief Method to display depth on frame
   *
   * @param frame
   * @param depth
   * @param bounding_box
   */
  void displayDepth(cv::Mat &frame, float depth,
                    const cv::Rect &bounding_box) const;

 private:
  // Focal Length of Camera
  float focal_length;

  // rw_height of Camera
  float rw_height;
};
